#include "hsm.h"
#include "hsm_user.h"
#include "time_bomb_config_user.h"

// USER_CODE_START::@main@
#include "time_bomb_user_types.h"
// USER_CODE_END::@main@

// Entry/Exit functions

// GEN_OBJ_START::time_bomb_on_entry_Unarmed
void time_bomb_on_entry_Unarmed(void *const p_sm_data)
{
    hsm_trace("=> [ENTRY] onEntry_Unarmed\n");
    // USER_CODE_START::onEntry_Unarmed

    // Your implementation goes here...
    TB_USER_DATA(p_sm_data)->timer_cntr = 0;

    // USER_CODE_END::onEntry_Unarmed
}
// GEN_OBJ_END::time_bomb_on_entry_Unarmed

// GEN_OBJ_START::time_bomb_on_exit_Unarmed
void time_bomb_on_exit_Unarmed(void *const p_sm_data)
{
    hsm_trace("<= [EXIT] onExit_Unarmed\n");

    // USER_CODE_START::onExit_Unarmed

    // Your implementation goes here...

    // USER_CODE_END::onExit_Unarmed
}
// GEN_OBJ_END::time_bomb_on_exit_Unarmed


// GEN_OBJ_START::time_bomb_on_entry_Armed
void time_bomb_on_entry_Armed(void *const p_sm_data)
{
    hsm_trace("=> [ENTRY] onEntry_Armed\n");
    // USER_CODE_START::onEntry_Armed

    // Your implementation goes here...
    TB_USER_DATA(p_sm_data)->timer_cntr = 10;

    // USER_CODE_END::onEntry_Armed
}
// GEN_OBJ_END::time_bomb_on_entry_Armed

// GEN_OBJ_START::time_bomb_on_exit_Armed
void time_bomb_on_exit_Armed(void *const p_sm_data)
{
    hsm_trace("<= [EXIT] onExit_Armed\n");

    // USER_CODE_START::onExit_Armed

    // Your implementation goes here...

    // USER_CODE_END::onExit_Armed
}
// GEN_OBJ_END::time_bomb_on_exit_Armed


// GEN_OBJ_START::time_bomb_on_entry_Wait_For_Trigger
void time_bomb_on_entry_Wait_For_Trigger(void *const p_sm_data)
{
    hsm_trace("=> [ENTRY] onEntry_Wait_For_Trigger\n");
    // USER_CODE_START::onEntry_Wait_For_Trigger

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Wait_For_Trigger
}
// GEN_OBJ_END::time_bomb_on_entry_Wait_For_Trigger

// GEN_OBJ_START::time_bomb_on_exit_Wait_For_Trigger
void time_bomb_on_exit_Wait_For_Trigger(void *const p_sm_data)
{
    hsm_trace("<= [EXIT] onExit_Wait_For_Trigger\n");

    // USER_CODE_START::onExit_Wait_For_Trigger

    // Your implementation goes here...

    // USER_CODE_END::onExit_Wait_For_Trigger
}
// GEN_OBJ_END::time_bomb_on_exit_Wait_For_Trigger


// GEN_OBJ_START::time_bomb_on_entry_Final_Countdown
void time_bomb_on_entry_Final_Countdown(void *const p_sm_data)
{
    hsm_trace("=> [ENTRY] onEntry_Final_Countdown\n");
    // USER_CODE_START::onEntry_Final_Countdown

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Final_Countdown
}
// GEN_OBJ_END::time_bomb_on_entry_Final_Countdown

// GEN_OBJ_START::time_bomb_on_exit_Final_Countdown
void time_bomb_on_exit_Final_Countdown(void *const p_sm_data)
{
    hsm_trace("<= [EXIT] onExit_Final_Countdown\n");

    // USER_CODE_START::onExit_Final_Countdown

    // Your implementation goes here...

    // USER_CODE_END::onExit_Final_Countdown
}
// GEN_OBJ_END::time_bomb_on_exit_Final_Countdown


// GEN_OBJ_START::time_bomb_on_entry_Boom
void time_bomb_on_entry_Boom(void *const p_sm_data)
{
    hsm_trace("=> [ENTRY] onEntry_Boom\n");
    // USER_CODE_START::onEntry_Boom

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Boom
}
// GEN_OBJ_END::time_bomb_on_entry_Boom

// GEN_OBJ_START::time_bomb_on_exit_Boom
void time_bomb_on_exit_Boom(void *const p_sm_data)
{
    hsm_trace("<= [EXIT] onExit_Boom\n");

    // USER_CODE_START::onExit_Boom

    // Your implementation goes here...

    // USER_CODE_END::onExit_Boom
}
// GEN_OBJ_END::time_bomb_on_exit_Boom



// Guard condition functions
// GEN_OBJ_START::time_bomb_guard_is_red_wire
bool time_bomb_guard_is_red_wire(void *const p_sm_data)
{
    bool guard_res = false;

    // USER_CODE_START::guard_is_red_wire

    // Your implementation goes here...

    // USER_CODE_END::guard_is_red_wire

    hsm_trace("\t[GUARD CHECK] time_bomb_guard_is_red_wire => %s\n", (guard_res) ? "TRUE" : "FALSE");
    
    return guard_res;

}
// GEN_OBJ_END::time_bomb_guard_is_red_wire

// GEN_OBJ_START::time_bomb_guard_is_pink_wire
bool time_bomb_guard_is_pink_wire(void *const p_sm_data)
{
    bool guard_res = false;

    // USER_CODE_START::guard_is_pink_wire

    // Your implementation goes here...
    return false;

    // USER_CODE_END::guard_is_pink_wire

    hsm_trace("\t[GUARD CHECK] time_bomb_guard_is_pink_wire => %s\n", (guard_res) ? "TRUE" : "FALSE");
    
    return guard_res;

}
// GEN_OBJ_END::time_bomb_guard_is_pink_wire

// GEN_OBJ_START::time_bomb_guard_is_intended_caller
bool time_bomb_guard_is_intended_caller(void *const p_sm_data)
{
    bool guard_res = false;

    // USER_CODE_START::guard_is_intended_caller

    // Your implementation goes here...
    guard_res = true;

    // USER_CODE_END::guard_is_intended_caller

    hsm_trace("\t[GUARD CHECK] time_bomb_guard_is_intended_caller => %s\n", (guard_res) ? "TRUE" : "FALSE");
    
    return guard_res;

}
// GEN_OBJ_END::time_bomb_guard_is_intended_caller

// GEN_OBJ_START::time_bomb_guard_still_counting
bool time_bomb_guard_still_counting(void *const p_sm_data)
{
    bool guard_res = false;

    // USER_CODE_START::guard_still_counting

    // Your implementation goes here...
    guard_res = (TB_USER_DATA(p_sm_data)->timer_cntr > 0);

    // USER_CODE_END::guard_still_counting

    hsm_trace("\t[GUARD CHECK] time_bomb_guard_still_counting => %s\n", (guard_res) ? "TRUE" : "FALSE");
    
    return guard_res;

}
// GEN_OBJ_END::time_bomb_guard_still_counting

// GEN_OBJ_START::time_bomb_guard_is_count_zero
bool time_bomb_guard_is_count_zero(void *const p_sm_data)
{
    bool guard_res = false;

    // USER_CODE_START::guard_is_count_zero

    // Your implementation goes here...
    guard_res = (TB_USER_DATA(p_sm_data)->timer_cntr == 0);

    // USER_CODE_END::guard_is_count_zero

    hsm_trace("\t[GUARD CHECK] time_bomb_guard_is_count_zero => %s\n", (guard_res) ? "TRUE" : "FALSE");
    
    return guard_res;

}
// GEN_OBJ_END::time_bomb_guard_is_count_zero


// Action handlers
// GEN_OBJ_START::time_bomb_action_turn_on_green_led
void time_bomb_action_turn_on_green_led(void *const p_sm_data)
{
    hsm_trace("\t[ACTION] time_bomb_action_turn_on_green_led\n");
    // USER_CODE_START::action_turn_on_green_led

    // Your implementation goes here...

    // USER_CODE_END::action_turn_on_green_led
}
// GEN_OBJ_END::time_bomb_action_turn_on_green_led

// GEN_OBJ_START::time_bomb_action_turn_on_red_led
void time_bomb_action_turn_on_red_led(void *const p_sm_data)
{
    hsm_trace("\t[ACTION] time_bomb_action_turn_on_red_led\n");
    // USER_CODE_START::action_turn_on_red_led

    // Your implementation goes here...

    // USER_CODE_END::action_turn_on_red_led
}
// GEN_OBJ_END::time_bomb_action_turn_on_red_led

// GEN_OBJ_START::time_bomb_action_turn_on_blinking_orange_led
void time_bomb_action_turn_on_blinking_orange_led(void *const p_sm_data)
{
    hsm_trace("\t[ACTION] time_bomb_action_turn_on_blinking_orange_led\n");
    // USER_CODE_START::action_turn_on_blinking_orange_led

    // Your implementation goes here...

    // USER_CODE_END::action_turn_on_blinking_orange_led
}
// GEN_OBJ_END::time_bomb_action_turn_on_blinking_orange_led

// GEN_OBJ_START::time_bomb_action_decrease_counter
void time_bomb_action_decrease_counter(void *const p_sm_data)
{
    hsm_trace("\t[ACTION] time_bomb_action_decrease_counter\n");
    // USER_CODE_START::action_decrease_counter

    // Your implementation goes here...
    if (TB_USER_DATA(p_sm_data)->timer_cntr > 0)
    {
        TB_USER_DATA(p_sm_data)->timer_cntr--;
        hsm_trace("... timer_cntr [%d]\n", TB_USER_DATA(p_sm_data)->timer_cntr);
    }

    // USER_CODE_END::action_decrease_counter
}
// GEN_OBJ_END::time_bomb_action_decrease_counter

// GEN_OBJ_START::time_bomb_action_express_pitty_on_cutting_the_wrong_wire
void time_bomb_action_express_pitty_on_cutting_the_wrong_wire(void *const p_sm_data)
{
    hsm_trace("\t[ACTION] time_bomb_action_express_pitty_on_cutting_the_wrong_wire\n");
    // USER_CODE_START::action_express_pitty_on_cutting_the_wrong_wire

    // Your implementation goes here...
    printf(">>> NEVER BEEN SO DEAD! <<<\n");
    // USER_CODE_END::action_express_pitty_on_cutting_the_wrong_wire
}
// GEN_OBJ_END::time_bomb_action_express_pitty_on_cutting_the_wrong_wire
