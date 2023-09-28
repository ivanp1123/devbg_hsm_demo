#include <stdio.h>
#include "unity.h"
#include "test_sm_user.h"
#include "test_env.h"

TEST_FILE("test.c")

#define HSM_TRIGGER_EVENT(ev)    hsm_push_event(&Test_SM_instance, (ev));

void trace(const char* msg, ...)
{
}

void setUp(void)
{
    test_env_init();
}

void tearDown(void)
{

}

static void check_state(hsm_state_id_t s_id)
{
    hsm_state_id_t id = hsm_get_state(&Test_SM_instance);

    TEST_ASSERT_MESSAGE(id == s_id, "Unexpected state");
}

void test_unhandled_invalid_events(void)
{
    TEST_MESSAGE("Test if an invalid event triggers an error");

    bool res = HSM_TRIGGER_EVENT(0xFFFF);
    TEST_ASSERT(false == res);
}

void test_trans_inital(void)
{
    TEST_MESSAGE("Testing transition to initial state when a reset event is sent to SM");

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);
}

void test_on_entry_action(void)
{
    TEST_MESSAGE("Testing whether state onEntry function gets executed upon successful transition");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    TEST_ASSERT_MESSAGE(1U == env.on_entry_Initial_cnt, "OnEntry for Initial state not called or called more than once");
}

void test_on_exit_action(void)
{
    TEST_MESSAGE("Testing whether state onExit function gets executed upon successful transition");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    // switch over to Composite state
    env.guard_start_conditions_met = true;
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

    check_state(STATE_COMPOSITE_SUB1);

    TEST_ASSERT_MESSAGE(1U == env.on_start_action_cnt, "Action function not called or called more than once");
}

void test_transition_same_level(void)
{
    TEST_MESSAGE("Testing whether state transitions at the same hierarchy level are correctly executed");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_SWITCH_TO_IDLE);

    check_state(STATE_IDLE);
}

void test_transition_substate(void)
{
    TEST_MESSAGE("Testing whether state transitions to composite substates are performed correctly");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    // switch over to Composite state
    env.guard_start_conditions_met = true;
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

    check_state(STATE_COMPOSITE_SUB1);
}

void test_transition_higherlevel(void)
{
    TEST_MESSAGE("Testing whether state transitions to to higher levels in the hieararchy are performed correctly");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    // switch over to Composite_Sub2
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_SUB2);
    check_state(STATE_COMPOSITE_SUB2);

    // now try to go back to Initial state which is at a higher level in the state hierarchy...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL);
    check_state(STATE_INITIAL);
}

void test_history_transition(void)
{
    TEST_MESSAGE("Check whether transitions to composite history states are performed correctly");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);

    // switch over to Composite state to update history state explicitly
    env.guard_start_conditions_met = true;
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);
    check_state(STATE_COMPOSITE_SUB1);

    env.guard_entry_to_sub2_allowed = true;
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_ON_TIMER);
    check_state(STATE_COMPOSITE_SUB2);

    // exit composite state and...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL);
    check_state(STATE_INITIAL);

    // ...return to history state which should be state_Composite_Sub2
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_COMPOSITE_HISTORY);
    check_state(STATE_COMPOSITE_SUB2);
}

void test_transition_action(void)
{
    TEST_MESSAGE("Check whether transition action functions get called");

    for (uint16_t i = 0; i < 20U; i++)
    {
        TEST_ASSERT_MESSAGE(i == env.on_start_action_cnt, "Transition action function not called as expected");

        HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

        check_state(STATE_INITIAL);

        env.guard_start_conditions_met = true;
        HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

        HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL);
    }
}

void test_transition_guards(void)
{
    TEST_MESSAGE("Check whether transition guard functions get called and are evaluated when deciding on a transition");

    for (uint16_t i = 0; i < 20U; i++)
    {
        TEST_ASSERT_MESSAGE(i == env.on_start_action_cnt, "Transition action function not called as expected");

        HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

        check_state(STATE_INITIAL);

        env.guard_start_conditions_met = false;
        HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

        // state remained the same because guard condition was not met
        check_state(STATE_INITIAL);

        // try again... this time with enabled guard condition...
        env.guard_start_conditions_met = true;
        HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

        // state shall now be changed to the initial substate of the Composite state
        check_state(STATE_COMPOSITE_SUB1);
    }
}

void test_unhandled_valid_events(void)
{
    TEST_MESSAGE("Check that unhandled events do not change state");

    bool res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);
    TEST_ASSERT_MESSAGE(true == res, "Reset event not handled by the hsm lib");

    for (uint16_t i = 0; i < 20U; i++)
    {
        // periodic event is not supported in this state so we do not expect a state change
        res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_ON_TIMER);

        check_state(STATE_INITIAL);
        TEST_ASSERT_MESSAGE(false == res, "Periodic event should not be supported in the Initial state");

        res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_SUB2);
        check_state(STATE_COMPOSITE_SUB2);
        TEST_ASSERT_MESSAGE(true == res, "go_sub2 event should be supported in the Initial state");

        // periodic event is not supported in this state so we do not expect a state change
        res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_ON_TIMER);

        check_state(STATE_COMPOSITE_SUB2);
        TEST_ASSERT_MESSAGE(false == res, "Periodic event should not be supported in the Composite_Sub2 state");

        res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL);
        TEST_ASSERT_MESSAGE(true == res, "go_to_initial event should be supported in the Composite_Sub2 state");
    }
}

void test_composite_on_entry_exit(void)
{
    TEST_MESSAGE("Check whether onEntry/onExit actions are called on parent composite states when a substate is transitioned to");

    bool res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);
    TEST_ASSERT(true == res);

    // enter a substate of Composite state
    res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_SUB2);
    check_state(STATE_COMPOSITE_SUB2);
    TEST_ASSERT_MESSAGE(true == res, "go_sub2 event should be supported in the Initial state");

    // check if both parent and substate on_entry function was called
    TEST_ASSERT(1U == env.on_entry_composite_cnt);
    TEST_ASSERT(1U == env.on_entry_composite_sub2_cnt);

    res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL);
    check_state(STATE_INITIAL);

    // check if both parent and substate on_exit function was called
    TEST_ASSERT(1U == env.on_exit_composite_cnt);
    TEST_ASSERT(1U == env.on_exit_composite_sub2_cnt);
}

void test_composite_on_entry_exit_samelevel(void)
{
    TEST_MESSAGE("Check whether onEntry/onExit actions are called only on composite substates if transition is internal to the composite state");

    bool res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);
    TEST_ASSERT(true == res);

    check_state(STATE_INITIAL);

    // switch over to Composite state
    env.guard_start_conditions_met = true;
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_START);

    check_state(STATE_COMPOSITE_SUB1);

    // check if both parent and substate on_entry function was called
    TEST_ASSERT(1U == env.on_entry_composite_cnt);
    TEST_ASSERT(1U == env.on_entry_composite_sub1_cnt);

    // enter another substate in the same Composite state
    env.guard_entry_to_sub2_allowed = true;
    res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_ON_TIMER);
    check_state(STATE_COMPOSITE_SUB2);
    TEST_ASSERT(true == res);

    // check if Composite on_entry was not called (e.g. remained the same) and only
    // new substate on_entry was called
    TEST_ASSERT(1U == env.on_entry_composite_cnt);
    TEST_ASSERT(1U == env.on_entry_composite_sub1_cnt);
    TEST_ASSERT(1U == env.on_entry_composite_sub2_cnt);
}

void test_hierarchical_event_handling(void)
{
    TEST_MESSAGE("Check whether transitions from substates to outside their parent state are possible if a transition is specified for the parent state only");

    bool res = HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);
    TEST_ASSERT(true == res);

    check_state(STATE_INITIAL);

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_SUB3);

    check_state(STATE_DEEP_SUB3);

    TEST_ASSERT(0U == env.on_exit_deep_sub3_cnt);
    TEST_ASSERT(0U == env.on_exit_composite_sub3_cnt);

    // go_sub2 event is not supported by the Deep_Sub3 state but is supported by its parent
    // Composite_Sub3 and shall trigger a transition Composite_Sub2
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_SUB2_DIRECT);

    check_state(STATE_COMPOSITE_SUB2);
    // check if on_exit functions in the hieararchy get called
    TEST_ASSERT(1U == env.on_exit_deep_sub3_cnt);
    TEST_ASSERT(1U == env.on_exit_composite_sub3_cnt);
}

void test_on_entry_exit_for_self_transition(void)
{
    TEST_MESSAGE("Testing whether state onEntry/onExit functions do not get executed upon successful transition to the same state via a 'self' transition");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);

    uint16_t on_entry_prev = env.on_entry_Initial_cnt;
    uint16_t on_exit_prev = env.on_exit_Initial_cnt;

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_TRIGGER_SELF_TRANS);

    // the entry/exit count shall remain unchanged after triggering a transition to self
    TEST_ASSERT(on_entry_prev == env.on_entry_Initial_cnt);
    TEST_ASSERT(on_exit_prev == env.on_exit_Initial_cnt);
    TEST_ASSERT(1U == env.on_safe_action_cnt);
}

void test_on_entry_exit_same_state_transitions(void)
{
    TEST_MESSAGE("Testing whether state onEntry/onExit functions get executed upon successful transition to the same state (not a 'self' transition)");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);

    uint16_t on_entry_prev = env.on_entry_Initial_cnt;
    uint16_t on_exit_prev = env.on_exit_Initial_cnt;

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_TRIGGER_REGULAR_SELF_TRANS);

    // the entry/exit count shall remain unchanged after triggering a transition to self
    TEST_ASSERT((on_entry_prev + 1U) == env.on_entry_Initial_cnt);
    TEST_ASSERT((on_exit_prev + 1U) == env.on_exit_Initial_cnt);
    TEST_ASSERT(1U == env.on_regular_safe_action_cnt);
}

void test_on_exit_calls_for_more_than_1_nesting_levels(void)
{
    TEST_MESSAGE("DH-46: Exit actions not properly called for HSMs with more than 1 nesting level");

    // ensure we start from the initial state...
    HSM_TRIGGER_EVENT(HSM_EVENT_ID_RESET);

    check_state(STATE_INITIAL);

    TEST_ASSERT(0U == env.on_exit_composite_cnt);

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_SUB3);

    check_state(STATE_DEEP_SUB3);

    TEST_ASSERT(0U == env.on_exit_composite_cnt);

    TEST_ASSERT(1U == env.on_entry_composite_cnt);
    TEST_ASSERT(1U == env.on_entry_composite_sub3_cnt);
    TEST_ASSERT(1U == env.on_entry_deep_sub3_cnt);

    HSM_TRIGGER_EVENT(HSM_EVENT_ID_TEST_SM_GO_TO_SUB2_DIRECT);

    check_state(STATE_COMPOSITE_SUB2);

    TEST_ASSERT(1U == env.on_exit_composite_sub3_cnt);
    TEST_ASSERT(1U == env.on_exit_deep_sub3_cnt);

    // this is actually the issue found in the defect => the exit handler for the parent state of the target state gets called when it shouldn't
    TEST_ASSERT(0U == env.on_exit_composite_cnt);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_unhandled_invalid_events);
    RUN_TEST(test_trans_inital);
    RUN_TEST(test_on_entry_action);
    RUN_TEST(test_on_exit_action);
    RUN_TEST(test_transition_same_level);
    RUN_TEST(test_transition_substate);
    RUN_TEST(test_transition_higherlevel);
    RUN_TEST(test_history_transition);
    RUN_TEST(test_transition_action);
    RUN_TEST(test_transition_guards);
    RUN_TEST(test_unhandled_valid_events);
    RUN_TEST(test_composite_on_entry_exit);
    RUN_TEST(test_composite_on_entry_exit_samelevel);
    RUN_TEST(test_hierarchical_event_handling);
    RUN_TEST(test_on_entry_exit_same_state_transitions);
    RUN_TEST(test_on_exit_calls_for_more_than_1_nesting_levels);
    RUN_TEST(test_on_entry_exit_for_self_transition);

    return UNITY_END();
}
