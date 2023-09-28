/*
BSD 3-Clause License

Copyright (c) 2023, Ivan Petrov

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "hsm.h"
#include "hsm_user.h"

/**
 * @brief The function attempts to find if an event id and a guard condition matches a transition of a state
 *
 * @param p_inst SM instance object
 * @param p_state a pointer to a state which receives the event
 * @param id event identifier to process
 * @return a pointer to the transition to execute or NULL - if the event is not processed
 *         by this state7
 */
static p_hsm_trans_t hsm_find_trans(p_hsm_instance_t const p_inst, p_hsm_state_t p_state, const hsm_event_id_t id)
{
    p_hsm_trans_t *p_current_trans = p_state->config.p_trans_list;

    while (NULL != p_current_trans)
    {
        if (NULL != *p_current_trans)
        {
            if ((*p_current_trans)->id == id)
            {
                if (NULL != (*p_current_trans)->p_guard)
                {
                    if ((*p_current_trans)->p_guard(p_inst->p_sm_data))
                    {
                        break;
                    }
                }
                else
                {
                    // no guard, but there is an event match, so we go this way
                    break;
                }
            }
        }
        else
        {
            break;
        }

        p_current_trans++;
    }

    return (NULL != p_current_trans) ? *p_current_trans : NULL;
}

/**
 * @brief Determines if a state is composite or simple
 *
 * @param p_state state to check
 * @return true: the state is composite (or nested)
 *         false: the state is simple
 */
static inline bool hsm_is_composite_state(p_hsm_state_t p_state)
{
    return (p_state->config.p_initial_state != p_state);
}

/**
 * @brief Returns the target state for the transition based on the transition type
 *
 * @param p_trans transition to execute
 * @return target state to go to
 */
static p_hsm_state_t hsm_get_target_state(p_hsm_trans_t p_trans)
{
    p_hsm_state_t p_target_state = NULL;

    hsm_assert(NULL != p_trans);

    switch (p_trans->type)
    {
        case HSM_STATE_TRANS_TYPE_HISTORY:
            {
                p_target_state = p_trans->p_target_state->p_history_state->config.p_initial_state;
                break;
            }

        case HSM_STATE_TRANS_TYPE_REGULAR:
        default:
            {
                p_hsm_state_t p_current_state = p_trans->p_target_state->config.p_initial_state;

                while (hsm_is_composite_state(p_current_state))
                {
                    p_current_state = p_current_state->config.p_initial_state;
                }

                p_target_state = p_current_state;

                break;
            }
    }

    return p_target_state;
}

/**
 * @brief Finds the Least Common Ancestor of two states in the hierarchy
 *
 * @param p_state_1
 * @param p_state_2
 * @return a pointer to the LCA state or NULL if match not found
 */
static p_hsm_state_t hsm_get_lca(p_hsm_state_t p_state_1, p_hsm_state_t p_state_2)
{
    p_hsm_state_t state_path[MAX_NEST_LEVEL] = { NULL };
    p_hsm_state_t p_state_iter               = p_state_1;
    p_hsm_state_t p_lca                      = NULL;
    uint8_t       nest_level                 = 0;
    bool          match_found                = false;

    // if we are making a self-transition, then just return the same state
    if (p_state_1 == p_state_2)
    {
        return p_state_1;
    }

    state_path[nest_level++] = p_state_iter;

    while (NULL != p_state_iter->config.p_parent_state)
    {
        hsm_assert(nest_level < MAX_NEST_LEVEL);

        state_path[nest_level++] = p_state_iter->config.p_parent_state;
        p_state_iter             = p_state_iter->config.p_parent_state;
    }

    p_state_iter = p_state_2;

    while ((NULL != p_state_iter->config.p_parent_state) && !match_found)
    {
        for (uint8_t idx = 0; idx < nest_level; idx++)
        {
            if (p_state_iter->config.p_parent_state == state_path[idx])
            {
                p_lca       = state_path[idx];
                match_found = true;
                break;
            }
        }

        p_state_iter = p_state_iter->config.p_parent_state;
    }

    return p_lca;
}

/**
 * @brief Executes entry actions between two different states in a hierarchy
 *
 * @param p_inst SM instance object
 * @param p_active_state currently active parent state
 * @param p_target_state target internal state to reach
 */
static void hsm_exec_entry_actions(p_hsm_instance_t p_inst, p_hsm_state_t p_active_state, p_hsm_state_t p_target_state)
{
    p_entry_func entry_act_stack[MAX_NEST_LEVEL] = { NULL };

    hsm_assert(NULL != p_inst);
    hsm_assert(NULL != p_active_state);
    hsm_assert(NULL != p_target_state);

    p_hsm_state_t p_iter     = p_target_state->config.p_parent_state;
    uint8_t       nest_level = 0;

    // build the entry function stack up to the parent state...
    while ((NULL != p_iter) && (p_iter != p_active_state))
    {
        hsm_assert(nest_level < MAX_NEST_LEVEL);

        if (NULL != p_iter->config.p_entry)
        {
            entry_act_stack[nest_level++] = p_iter->config.p_entry;
        }

        p_iter = p_iter->config.p_parent_state;
    }

    // ... now execute entry actions in reverse order
    while (nest_level > 0)
    {
        nest_level--;

        if (NULL != entry_act_stack[nest_level])
        {
            (*entry_act_stack[nest_level])(p_inst->p_sm_data);
        }
    }

    // call all subsequent entry actions if the target state happens to be a composite
    p_iter = p_target_state;
    while ((NULL != p_iter) && (hsm_is_composite_state(p_iter)))
    {
        if (NULL != p_iter->config.p_entry)
        {
            (*p_iter->config.p_entry)(p_inst->p_sm_data);
        }

        p_iter = p_iter->config.p_initial_state;
    }

    // ...call terminating state entry action after all other entry actions
    // have been called
    if ((NULL != p_iter) && (NULL != p_iter->config.p_entry))
    {
        (*p_iter->config.p_entry)(p_inst->p_sm_data);
    }
}

/**
 * @brief Executes exit actions starting from one state up to a higher level in the state hierarchy
 *
 * @param p_inst SM instance object
 * @param p_active_state starting state
 * @param p_target_state target parent state
 */
static void hsm_exec_exit_actions(p_hsm_instance_t p_inst, p_hsm_state_t p_active_state, p_hsm_state_t p_target_state)
{
    hsm_assert(NULL != p_inst);
    hsm_assert(NULL != p_active_state);
    hsm_assert(NULL != p_target_state);

    p_hsm_state_t p_iter = p_active_state;

    do
    {
        // preserve history state
        if (NULL != p_iter->config.p_parent_state)
        {
            p_iter->config.p_parent_state->p_history_state = p_iter;
        }

        if (NULL != p_iter->config.p_exit)
        {
            (*p_iter->config.p_exit)(p_inst->p_sm_data);
        }

        p_iter = p_iter->config.p_parent_state;
    } while ((NULL != p_iter) && (p_iter != p_target_state));
}

/**
 * @brief The function executes a transition
 *
 * It takes care to execute the corresponding entry/exit actions as well.
 *
 * @param p_inst HSM instance object
 * @param p_active_state currently active state
 * @param p_trans transition to execute
 * @return final state reached
 */
static p_hsm_state_t hsm_exec_trans(p_hsm_instance_t p_inst, p_hsm_state_t p_active_state, p_hsm_trans_t p_trans)
{
    p_hsm_state_t p_target_state = hsm_get_target_state(p_trans);
    p_hsm_state_t p_lca          = hsm_get_lca(p_active_state, p_target_state);

    if (HSM_STATE_TRANS_TYPE_SELF != p_trans->type)
    {
        hsm_exec_exit_actions(p_inst, p_active_state, p_lca);
    }

    if (NULL != p_trans->p_action)
    {
        (*p_trans->p_action)(p_inst->p_sm_data);
    }

    if (HSM_STATE_TRANS_TYPE_SELF != p_trans->type)
    {
        hsm_exec_entry_actions(p_inst, p_lca, p_target_state);
    }

    return p_target_state;
}

/**
 * @brief The function tries to handle a given SM event at the currently active state or upper in its hierarchy.
 *
 * @param p_inst SM instance object
 * @param p_state state at which to try handling the event
 * @param id event identifier
 * @return a pointer to the finally reached state or NULL if the event was not handled by any state in the hierarchy
 */
static p_hsm_state_t hsm_push_event_internal(p_hsm_instance_t const p_inst, p_hsm_state_t p_state, const hsm_event_id_t id)
{
    p_hsm_state_t p_final_state = NULL;
    uint8_t nest_level = 0;

    if ((NULL != p_inst) && (NULL != p_state))
    {
        switch (id)
        {
            case HSM_EVENT_ID_RESET:
                {
                    hsm_exec_exit_actions(p_inst, p_inst->p_root->p_active_state, p_inst->p_root);

                    hsm_exec_entry_actions(p_inst, p_inst->p_root, p_inst->p_root->config.p_initial_state);

                    p_inst->p_root->p_active_state = p_inst->p_root->config.p_initial_state;
                    p_inst->p_root->p_history_state = p_inst->p_root->p_active_state;

                    p_final_state = p_inst->p_root->p_active_state;

                    break;
                }

            default:
                {
                    p_hsm_trans_t p_target_trans = hsm_find_trans(p_inst, p_state->p_active_state, id);

                    if (NULL != p_target_trans)
                    {
                        p_final_state = hsm_exec_trans(p_inst, p_state->p_active_state, p_target_trans);
                        hsm_trace("[HSM]: '%s' == %s ==> '%s'\n", p_state->p_active_state->config.name, p_target_trans->name, p_target_trans->p_target_state->config.name);
                    }
                    else
                    {
                        // is this top of hierarchy?
                        if ((NULL != p_state->config.p_parent_state) && (nest_level <= MAX_NEST_LEVEL))
                        {
                            nest_level++;
                            // the current state cannot handle the transition, push to parent...
                            p_final_state = hsm_push_event_internal(p_inst, p_state->p_active_state->config.p_parent_state, id);
                        }
                        else
                        {
                            // just a protection in case the configuration is corrupted and we never reach a top-level state
                            hsm_assert(nest_level == MAX_NEST_LEVEL);
                        }
                    }

                    break;
                }
        }
    }

    if (NULL != p_final_state)
    {
        p_inst->p_root->p_active_state = p_final_state;
    }

    return p_final_state;
}

void hsm_init(p_hsm_instance_t const p_inst, void *const p_sm_data)
{
    if (NULL != p_inst)
    {
        p_inst->p_sm_data = p_sm_data;
    }
}

bool hsm_push_event(p_hsm_instance_t const p_inst, const hsm_event_id_t id)
{
    p_hsm_state_t p_final_state = hsm_push_event_internal(p_inst, p_inst->p_root->p_active_state, id);

    return (NULL != p_final_state);
}

hsm_state_id_t hsm_get_state(p_hsm_instance_t const p_inst)
{
    if (NULL != p_inst)
    {
        return p_inst->p_root->p_active_state->config.id;
    }
    else
    {
        hsm_assert(false);
    }
}