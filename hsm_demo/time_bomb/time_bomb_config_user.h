#ifndef TIME_BOMB_CONFIG_USER_H
#define TIME_BOMB_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions
void time_bomb_on_entry_Unarmed(void *const p_sm_data);
void time_bomb_on_exit_Unarmed(void *const p_sm_data);
void time_bomb_on_entry_Armed(void *const p_sm_data);
void time_bomb_on_exit_Armed(void *const p_sm_data);
void time_bomb_on_entry_Wait_For_Trigger(void *const p_sm_data);
void time_bomb_on_exit_Wait_For_Trigger(void *const p_sm_data);
void time_bomb_on_entry_Final_Countdown(void *const p_sm_data);
void time_bomb_on_exit_Final_Countdown(void *const p_sm_data);
void time_bomb_on_entry_Boom(void *const p_sm_data);
void time_bomb_on_exit_Boom(void *const p_sm_data);

// Guard condition functions
bool time_bomb_guard_is_red_wire(void *const p_sm_data);
bool time_bomb_guard_is_pink_wire(void *const p_sm_data);
bool time_bomb_guard_is_intended_caller(void *const p_sm_data);
bool time_bomb_guard_still_counting(void *const p_sm_data);
bool time_bomb_guard_is_count_zero(void *const p_sm_data);

// Action handlers
void time_bomb_action_turn_on_green_led(void *const p_sm_data);
void time_bomb_action_turn_on_red_led(void *const p_sm_data);
void time_bomb_action_turn_on_blinking_orange_led(void *const p_sm_data);
void time_bomb_action_decrease_counter(void *const p_sm_data);
void time_bomb_action_express_pitty_on_cutting_the_wrong_wire(void *const p_sm_data);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TIME_BOMB_CONFIG_USER_H