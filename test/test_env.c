#include "test_env.h"

test_env_t env;

void test_assert(bool cond)
{
    if (!cond)
    {
        env.assert_cnt++;
    }
}

void test_trace(const char* msg, ...)
{

}

void test_env_init(void)
{
    env.on_entry_Initial_cnt = 0U;
    env.on_exit_Initial_cnt = 0U;
    env.guard_start_conditions_met = false;
    env.on_start_action_cnt = 0U;
    env.guard_entry_to_sub2_allowed = false;
    env.on_entry_composite_cnt = 0U;
    env.on_exit_composite_cnt = 0U;
    env.on_entry_composite_sub1_cnt = 0U;
    env.on_exit_composite_sub1_cnt = 0U;
    env.on_entry_composite_sub2_cnt = 0U;
    env.on_exit_composite_sub2_cnt = 0U;
    env.on_entry_deep_sub3_cnt = 0U;
    env.on_exit_deep_sub3_cnt = 0U;
    env.on_entry_composite_sub3_cnt = 0U;
    env.on_exit_composite_sub3_cnt = 0U;
    env.assert_cnt = 0U;
    env.on_regular_safe_action_cnt = 0U;
    env.on_safe_action_cnt = 0U;
}