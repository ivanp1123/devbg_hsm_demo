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

#ifndef HSM_H_
#define HSM_H_

/** @file hsm.h
 *  @brief Basic Hierarchical State Machine engine interface
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

#define HSM_EVENT_ID_NONE         ((uint32_t)0) /**< Reserved ID used when there is no valid event to process */
#define HSM_EVENT_ID_RESET        ((uint32_t)1) /**< Reserved ID for an HSM reset operation */
#define HSM_EVENT_ID_USER         ((uint32_t)2) /**< Reserved ID offset for user-defined events */

    /**
     * @brief Defines the different types of transitions to target states supported by the engine
     */
    typedef enum
    {
        HSM_STATE_TRANS_TYPE_REGULAR, /**< regular transition to a state */
        HSM_STATE_TRANS_TYPE_SELF,    /**< internal transition to the same state */
        HSM_STATE_TRANS_TYPE_HISTORY, /**< transition to the history state of another state  */
        HSM_STATE_TRANS_TYPE_MAX      /**< invalid attribute value used for initialization or range checking */
    } hsm_state_trans_type_t;

    /**
     * @brief The basic type used to represent HSM event identifiers (see HSM_EVENT_ID_* symbols)
     */
    typedef uint8_t hsm_event_id_t;

    /** @brief The basic type used to represent HSM state identifiers */
    typedef uint8_t hsm_state_id_t;

    /** @brief Defines the prototype of a transition guard function
     *
     * @param[in/out] p_sm_data User data provided to the SM upon initialization
     * @return True: the transition shall be executed
     *         False: the transition shall not be executed
     */
    typedef bool (*p_guard_func)(void *const p_sm_data);

    /** @brief Defines the prototype of a transition action function.
     * @param[in/out] p_sm_data User data provided to the SM upon initialization
     *
     */
    typedef void (*p_action_func)(void *const p_sm_data);

    /**
     * @brief Defines the prototype of the state entry function
     * @param[in/out] p_sm_data User data provided to the SM upon initialization
     */
    typedef void (*p_entry_func)(void *const p_sm_data);

    /**
     * @brief Defines the prototype of the state exit function
     * @param[in/out] p_sm_data User data provided to the SM upon initialization
     */
    typedef void (*p_exit_func)(void *const p_sm_data);

    /** @brief Forward declaration of the @ref hsm_state_t type */
    struct hsm_state_t;

    /** @brief Defines a pointer type to an HSM state */
    typedef struct hsm_state_t *p_hsm_state_t;

    /**
     * @brief Defines the state transition members
     */
    struct hsm_trans_t
    {
        char          *name;    /**< ASCII name of the event (used for debugging) */
        hsm_event_id_t id;      /**< hsm event which triggers the transition */
        p_guard_func   p_guard; /**< a pointer to the transition guard function (NULL -
                                   if not used) */
        p_action_func
            p_action; /**< a pointer to the action function which will be called if
                         the transition is executed (NULL - if not used) */
        p_hsm_state_t
                               p_target_state; /**< a pointer to the target state of the transition */
        hsm_state_trans_type_t type;           /**< transition type specifier */
    };

    /** @brief Defines a pointer type to an HSM transition */
    typedef struct hsm_trans_t *p_hsm_trans_t;

    struct hsm_config_t
    {
        char               *name;            /**< ASCII name of the state (used for debugging) */
        hsm_state_id_t      id;              /**< unique numeric identifier of the state used when checking the HSM state (to avoid string comparison with name) */
        struct hsm_trans_t *p_trans_list;    /**< list of outgoing transitions from this state */
        p_hsm_state_t       p_parent_state;  /**< parent state in case of a state hierarchy */
        p_hsm_state_t       p_initial_state; /**< a pointer to the initial state in case this is a nested state */
        p_entry_func        p_entry;         /**< a pointer to the entry function of the state (NULL - if not used) */
        p_exit_func         p_exit;          /**< a pointer to the exit function of the state (NULL - if not used) */
    };

    /**
     * @brief Describes the members of the HSM state class
     */
    struct hsm_state_t
    {
        const struct hsm_config_t config; /**< ROM HSM configuration data */
        // RAM runtime members follow
        p_hsm_state_t p_history_state; /**< a pointer to the last active state in case this is a nested state */
        p_hsm_state_t p_active_state;  /**< a pointer to the currently active state */
    };

    /**
     * @brief Describes the members of the HSM instance class.
     */
    struct hsm_instance_t
    {
        const p_hsm_state_t p_root;    /**< root state of the HSM instance */
        void               *p_sm_data; /**< SM user-specific instance data */
    };

    typedef struct hsm_instance_t *p_hsm_instance_t;

    /**
     * @brief Initializes the SM instance with user data
     *
     * @param p_inst a pointer to the SM instance object
     * @param p_sm_data a pointer to the user data to link to the SM
     * @note p_sm_data will be passed to all entry/exit and action handlers executed by
     *       the engine
     */
    void hsm_init(p_hsm_instance_t const p_inst, void *const p_sm_data);

    /** @brief A pointer type to an HSM instance object */
    typedef struct hsm_instance_t *p_hsm_instance_t;
    /**
     * @brief Pushes an event to the SM and executes it
     *
     * @param[in/out] p_inst a pointer to the SM instance object
     * @param[in] id identifier of the event to process
     * @return true: event handled; false: event not handled
     */
    bool hsm_push_event(p_hsm_instance_t const p_inst, const hsm_event_id_t id);

    /**
     * @brief Returns the currently active state of the SM
     *
     * @param p_inst SM instance object
     * @return hsm_state_id_t identifier of the currently active state
     */
    hsm_state_id_t hsm_get_state(p_hsm_instance_t const p_inst);

#ifdef __cplusplus
}
#endif

#endif // HSM_H_