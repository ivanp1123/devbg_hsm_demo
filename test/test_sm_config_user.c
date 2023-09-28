#include "hsm.h"
#include "Test_SM_config_user.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
#include "test_env.h"

// USER_CODE_END::@main@

// Entry/Exit functions

// GEN_OBJ_START::Test_SM_on_entry_Initial
void Test_SM_on_entry_Initial(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Initial

    env.on_entry_Initial_cnt++;

    // USER_CODE_END::onEntry_Initial
}
// GEN_OBJ_END::Test_SM_on_entry_Initial

// GEN_OBJ_START::Test_SM_on_exit_Initial
void Test_SM_on_exit_Initial(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Initial

    env.on_exit_Initial_cnt++;

    // USER_CODE_END::onExit_Initial
}
// GEN_OBJ_END::Test_SM_on_exit_Initial


// GEN_OBJ_START::Test_SM_on_entry_Idle
void Test_SM_on_entry_Idle(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Idle

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Idle
}
// GEN_OBJ_END::Test_SM_on_entry_Idle

// GEN_OBJ_START::Test_SM_on_exit_Idle
void Test_SM_on_exit_Idle(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Idle

    // Your implementation goes here...

    // USER_CODE_END::onExit_Idle
}
// GEN_OBJ_END::Test_SM_on_exit_Idle


// GEN_OBJ_START::Test_SM_on_entry_Composite
void Test_SM_on_entry_Composite(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Composite

    env.on_entry_composite_cnt++;

    // USER_CODE_END::onEntry_Composite
}
// GEN_OBJ_END::Test_SM_on_entry_Composite

// GEN_OBJ_START::Test_SM_on_exit_Composite
void Test_SM_on_exit_Composite(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Composite

    env.on_exit_composite_cnt++;

    // USER_CODE_END::onExit_Composite
}
// GEN_OBJ_END::Test_SM_on_exit_Composite


// GEN_OBJ_START::Test_SM_on_entry_Composite_Sub1
void Test_SM_on_entry_Composite_Sub1(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Composite_Sub1

    env.on_entry_composite_sub1_cnt++;

    // USER_CODE_END::onEntry_Composite_Sub1
}
// GEN_OBJ_END::Test_SM_on_entry_Composite_Sub1

// GEN_OBJ_START::Test_SM_on_exit_Composite_Sub1
void Test_SM_on_exit_Composite_Sub1(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Composite_Sub1

    env.on_exit_composite_sub1_cnt++;

    // USER_CODE_END::onExit_Composite_Sub1
}
// GEN_OBJ_END::Test_SM_on_exit_Composite_Sub1


// GEN_OBJ_START::Test_SM_on_entry_Composite_Sub2
void Test_SM_on_entry_Composite_Sub2(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Composite_Sub2

    env.on_entry_composite_sub2_cnt++;

    // USER_CODE_END::onEntry_Composite_Sub2
}
// GEN_OBJ_END::Test_SM_on_entry_Composite_Sub2

// GEN_OBJ_START::Test_SM_on_exit_Composite_Sub2
void Test_SM_on_exit_Composite_Sub2(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Composite_Sub2

    env.on_exit_composite_sub2_cnt++;

    // USER_CODE_END::onExit_Composite_Sub2
}
// GEN_OBJ_END::Test_SM_on_exit_Composite_Sub2


// GEN_OBJ_START::Test_SM_on_entry_Deep_Sub3
void Test_SM_on_entry_Deep_Sub3(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Deep_Sub3

    env.on_entry_deep_sub3_cnt++;

    // USER_CODE_END::onEntry_Deep_Sub3
}
// GEN_OBJ_END::Test_SM_on_entry_Deep_Sub3

// GEN_OBJ_START::Test_SM_on_exit_Deep_Sub3
void Test_SM_on_exit_Deep_Sub3(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Deep_Sub3

    env.on_exit_deep_sub3_cnt++;

    // USER_CODE_END::onExit_Deep_Sub3
}
// GEN_OBJ_END::Test_SM_on_exit_Deep_Sub3


// GEN_OBJ_START::Test_SM_on_entry_Deep_Sub4
void Test_SM_on_entry_Deep_Sub4(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Deep_Sub4

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Deep_Sub4
}
// GEN_OBJ_END::Test_SM_on_entry_Deep_Sub4

// GEN_OBJ_START::Test_SM_on_exit_Deep_Sub4
void Test_SM_on_exit_Deep_Sub4(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Deep_Sub4

    // Your implementation goes here...

    // USER_CODE_END::onExit_Deep_Sub4
}
// GEN_OBJ_END::Test_SM_on_exit_Deep_Sub4


// GEN_OBJ_START::Test_SM_on_entry_Composite_Sub3
void Test_SM_on_entry_Composite_Sub3(void *const p_sm_data)
{
    // USER_CODE_START::onEntry_Composite_Sub3

    env.on_entry_composite_sub3_cnt++;

    // USER_CODE_END::onEntry_Composite_Sub3
}
// GEN_OBJ_END::Test_SM_on_entry_Composite_Sub3

// GEN_OBJ_START::Test_SM_on_exit_Composite_Sub3
void Test_SM_on_exit_Composite_Sub3(void *const p_sm_data)
{
    // USER_CODE_START::onExit_Composite_Sub3

    env.on_exit_composite_sub3_cnt++;

    // USER_CODE_END::onExit_Composite_Sub3
}
// GEN_OBJ_END::Test_SM_on_exit_Composite_Sub3



// Guard condition functions
// GEN_OBJ_START::Test_SM_guard_start_conditions_met
bool Test_SM_guard_start_conditions_met(void *const p_sm_data)
{
    // USER_CODE_START::guard_start_conditions_met

    // Your implementation goes here...
    return env.guard_start_conditions_met;

    // USER_CODE_END::guard_start_conditions_met
}
// GEN_OBJ_END::Test_SM_guard_start_conditions_met

// GEN_OBJ_START::Test_SM_guard_initial_cond_met
bool Test_SM_guard_initial_cond_met(void *const p_sm_data)
{
    // USER_CODE_START::guard_initial_cond_met

    // Your implementation goes here...
    return false;

    // USER_CODE_END::guard_initial_cond_met
}
// GEN_OBJ_END::Test_SM_guard_initial_cond_met

// GEN_OBJ_START::Test_SM_guard_entry_to_sub2_allowed
bool Test_SM_guard_entry_to_sub2_allowed(void *const p_sm_data)
{
    // USER_CODE_START::guard_entry_to_sub2_allowed

    // Your implementation goes here...
    return env.guard_entry_to_sub2_allowed;

    // USER_CODE_END::guard_entry_to_sub2_allowed
}
// GEN_OBJ_END::Test_SM_guard_entry_to_sub2_allowed


// Action handlers
// GEN_OBJ_START::Test_SM_action_on_start_action
void Test_SM_action_on_start_action(void *const p_sm_data)
{
    // USER_CODE_START::action_on_start_action

    env.on_start_action_cnt++;

    // USER_CODE_END::action_on_start_action
}
// GEN_OBJ_END::Test_SM_action_on_start_action

// GEN_OBJ_START::Test_SM_action_on_regular_self_action
void Test_SM_action_on_regular_self_action(void *const p_sm_data)
{
    // USER_CODE_START::action_on_regular_self_action

    env.on_regular_safe_action_cnt++;

    // USER_CODE_END::action_on_regular_self_action
}
// GEN_OBJ_END::Test_SM_action_on_regular_self_action

// GEN_OBJ_START::Test_SM_action_on_self_action
void Test_SM_action_on_self_action(void *const p_sm_data)
{
    // USER_CODE_START::action_on_self_action

    env.on_safe_action_cnt++;

    // USER_CODE_END::action_on_self_action
}
// GEN_OBJ_END::Test_SM_action_on_self_action

// GEN_OBJ_START::Test_SM_action_on_initial_switch_action
void Test_SM_action_on_initial_switch_action(void *const p_sm_data)
{
    // USER_CODE_START::action_on_initial_switch_action

    // Your implementation goes here...

    // USER_CODE_END::action_on_initial_switch_action
}
// GEN_OBJ_END::Test_SM_action_on_initial_switch_action

// GEN_OBJ_START::Test_SM_action_composite_sub2_action
void Test_SM_action_composite_sub2_action(void *const p_sm_data)
{
    // USER_CODE_START::action_composite_sub2_action

    // Your implementation goes here...

    // USER_CODE_END::action_composite_sub2_action
}
// GEN_OBJ_END::Test_SM_action_composite_sub2_action
