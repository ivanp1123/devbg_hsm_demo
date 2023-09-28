#ifndef TEST_SM_CONFIG_USER_H
#define TEST_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions
void Test_SM_on_entry_Initial(void *const p_sm_data);
void Test_SM_on_exit_Initial(void *const p_sm_data);
void Test_SM_on_entry_Idle(void *const p_sm_data);
void Test_SM_on_exit_Idle(void *const p_sm_data);
void Test_SM_on_entry_Composite(void *const p_sm_data);
void Test_SM_on_exit_Composite(void *const p_sm_data);
void Test_SM_on_entry_Composite_Sub1(void *const p_sm_data);
void Test_SM_on_exit_Composite_Sub1(void *const p_sm_data);
void Test_SM_on_entry_Composite_Sub2(void *const p_sm_data);
void Test_SM_on_exit_Composite_Sub2(void *const p_sm_data);
void Test_SM_on_entry_Deep_Sub3(void *const p_sm_data);
void Test_SM_on_exit_Deep_Sub3(void *const p_sm_data);
void Test_SM_on_entry_Deep_Sub4(void *const p_sm_data);
void Test_SM_on_exit_Deep_Sub4(void *const p_sm_data);
void Test_SM_on_entry_Composite_Sub3(void *const p_sm_data);
void Test_SM_on_exit_Composite_Sub3(void *const p_sm_data);

// Guard condition functions
bool Test_SM_guard_start_conditions_met(void *const p_sm_data);
bool Test_SM_guard_initial_cond_met(void *const p_sm_data);
bool Test_SM_guard_entry_to_sub2_allowed(void *const p_sm_data);

// Action handlers
void Test_SM_action_on_start_action(void *const p_sm_data);
void Test_SM_action_on_regular_self_action(void *const p_sm_data);
void Test_SM_action_on_self_action(void *const p_sm_data);
void Test_SM_action_on_initial_switch_action(void *const p_sm_data);
void Test_SM_action_composite_sub2_action(void *const p_sm_data);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TEST_SM_CONFIG_USER_H