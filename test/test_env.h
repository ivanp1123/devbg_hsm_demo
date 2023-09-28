#ifndef TEST_ENV_H
#define TEST_ENV_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

    typedef struct
    {
        uint16_t on_entry_Initial_cnt;
        uint16_t on_exit_Initial_cnt;
        bool     guard_start_conditions_met;
        bool     guard_entry_to_sub2_allowed;
        uint16_t on_start_action_cnt;
        uint16_t on_entry_composite_cnt;
        uint16_t on_exit_composite_cnt;
        uint16_t on_entry_composite_sub1_cnt;
        uint16_t on_exit_composite_sub1_cnt;
        uint16_t on_entry_composite_sub2_cnt;
        uint16_t on_exit_composite_sub2_cnt;
        uint16_t on_entry_deep_sub3_cnt;
        uint16_t on_exit_deep_sub3_cnt;
        uint16_t on_entry_composite_sub3_cnt;
        uint16_t on_exit_composite_sub3_cnt;
        uint16_t on_safe_action_cnt;
        uint16_t on_regular_safe_action_cnt;
        uint16_t assert_cnt;
    } test_env_t;

    extern test_env_t env;

#ifdef __cplusplus
};
#endif

void test_env_init(void);

#endif // #ifndef TEST_ENV_H
