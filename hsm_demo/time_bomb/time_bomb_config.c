#include <stddef.h>
#include "hsm.h"
#include "time_bomb_config_user.h"
#include "time_bomb_user.h"


static const struct hsm_trans_t tran_Unarmed_ev_arm_button_press_Armed;
static const struct hsm_trans_t tran_Armed_ev_wire_cut_event_Unarmed;
static const struct hsm_trans_t tran_Armed_ev_wire_cut_event_Boom;
static const struct hsm_trans_t tran_Wait_For_Trigger_ev_phone_call_received_Final_Countdown;
static const struct hsm_trans_t tran_Final_Countdown_ev_on_timer___self;
static const struct hsm_trans_t tran_Final_Countdown_ev_on_timer_Boom;
static const struct hsm_trans_t tran_Boom_ev_on_timer___self;


static const p_hsm_trans_t trans_Unarmed[] =
{
    &tran_Unarmed_ev_arm_button_press_Armed,
    NULL
};

static const p_hsm_trans_t trans_Armed[] =
{
    &tran_Armed_ev_wire_cut_event_Unarmed,
    &tran_Armed_ev_wire_cut_event_Boom,
    NULL
};

static const p_hsm_trans_t trans_Wait_For_Trigger[] =
{
    &tran_Wait_For_Trigger_ev_phone_call_received_Final_Countdown,
    NULL
};

static const p_hsm_trans_t trans_Final_Countdown[] =
{
    &tran_Final_Countdown_ev_on_timer___self,
    &tran_Final_Countdown_ev_on_timer_Boom,
    NULL
};

static const p_hsm_trans_t trans_Boom[] =
{
    &tran_Boom_ev_on_timer___self,
    NULL
};


// time_bomb states forward declarations
static struct hsm_state_t state_Unarmed;
static struct hsm_state_t state_Armed;
static struct hsm_state_t state_Wait_For_Trigger;
static struct hsm_state_t state_Final_Countdown;
static struct hsm_state_t state_Boom;

// time_bomb root state definition
struct hsm_state_t state_time_bomb =
{
    {
        // name
        "state_time_bomb",
        // id
        STATE_ROOT,
        // p_trans_list
        NULL,
        // p_parent_state
        NULL,
        // p_initial_state,
        &state_Unarmed,
        // p_entry
        NULL,
        // p_exit
        NULL
    },
    // p_history_state
    &state_Unarmed,
    // p_active_state
    &state_time_bomb
};
static struct hsm_state_t state_Unarmed =
{
    // ROM config
    {
        // name
        "state_Unarmed",
        // id
        STATE_UNARMED,
        // pTransitionList
        trans_Unarmed,
        // pParent
        &state_time_bomb,
        // p_initial_state,
        &state_Unarmed,
        // onEntryFunc
        &time_bomb_on_entry_Unarmed,
        // onExitFunc
        &time_bomb_on_exit_Unarmed,
    },
    // pHistoryState
    &state_Unarmed,
    // pActiveState
    &state_Unarmed
};

static struct hsm_state_t state_Armed =
{
    // ROM config
    {
        // name
        "state_Armed",
        // id
        STATE_ARMED,
        // pTransitionList
        trans_Armed,
        // pParent
        &state_time_bomb,
        // p_initial_state,
        &state_Wait_For_Trigger,
        // onEntryFunc
        &time_bomb_on_entry_Armed,
        // onExitFunc
        &time_bomb_on_exit_Armed,
    },
    // pHistoryState
    &state_Wait_For_Trigger,
    // pActiveState
    &state_Armed
};

static struct hsm_state_t state_Wait_For_Trigger =
{
    // ROM config
    {
        // name
        "state_Wait_For_Trigger",
        // id
        STATE_WAIT_FOR_TRIGGER,
        // pTransitionList
        trans_Wait_For_Trigger,
        // pParent
        &state_Armed,
        // p_initial_state,
        &state_Wait_For_Trigger,
        // onEntryFunc
        &time_bomb_on_entry_Wait_For_Trigger,
        // onExitFunc
        &time_bomb_on_exit_Wait_For_Trigger,
    },
    // pHistoryState
    &state_Wait_For_Trigger,
    // pActiveState
    &state_Wait_For_Trigger
};

static struct hsm_state_t state_Final_Countdown =
{
    // ROM config
    {
        // name
        "state_Final_Countdown",
        // id
        STATE_FINAL_COUNTDOWN,
        // pTransitionList
        trans_Final_Countdown,
        // pParent
        &state_Armed,
        // p_initial_state,
        &state_Final_Countdown,
        // onEntryFunc
        &time_bomb_on_entry_Final_Countdown,
        // onExitFunc
        &time_bomb_on_exit_Final_Countdown,
    },
    // pHistoryState
    &state_Final_Countdown,
    // pActiveState
    &state_Final_Countdown
};

static struct hsm_state_t state_Boom =
{
    // ROM config
    {
        // name
        "state_Boom",
        // id
        STATE_BOOM,
        // pTransitionList
        trans_Boom,
        // pParent
        &state_time_bomb,
        // p_initial_state,
        &state_Boom,
        // onEntryFunc
        &time_bomb_on_entry_Boom,
        // onExitFunc
        &time_bomb_on_exit_Boom,
    },
    // pHistoryState
    &state_Boom,
    // pActiveState
    &state_Boom
};

static const struct hsm_trans_t tran_Unarmed_ev_arm_button_press_Armed =
{
    // name
    "arm_button_press",
    // id
    HSM_EVENT_ID_TIME_BOMB_ARM_BUTTON_PRESS,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Armed,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Armed_ev_wire_cut_event_Unarmed =
{
    // name
    "wire_cut_event",
    // id
    HSM_EVENT_ID_TIME_BOMB_WIRE_CUT_EVENT,
    // guard
    &time_bomb_guard_is_red_wire,
    // action
    &time_bomb_action_turn_on_green_led,
    // target state
    &state_Unarmed,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Armed_ev_wire_cut_event_Boom =
{
    // name
    "wire_cut_event",
    // id
    HSM_EVENT_ID_TIME_BOMB_WIRE_CUT_EVENT,
    // guard
    &time_bomb_guard_is_pink_wire,
    // action
    &time_bomb_action_turn_on_red_led,
    // target state
    &state_Boom,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Wait_For_Trigger_ev_phone_call_received_Final_Countdown =
{
    // name
    "phone_call_received",
    // id
    HSM_EVENT_ID_TIME_BOMB_PHONE_CALL_RECEIVED,
    // guard
    &time_bomb_guard_is_intended_caller,
    // action
    &time_bomb_action_turn_on_blinking_orange_led,
    // target state
    &state_Final_Countdown,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Final_Countdown_ev_on_timer___self =
{
    // name
    "on_timer",
    // id
    HSM_EVENT_ID_TIME_BOMB_ON_TIMER,
    // guard
    &time_bomb_guard_still_counting,
    // action
    &time_bomb_action_decrease_counter,
    // target state
    &state_Final_Countdown,
    // transition type
    HSM_STATE_TRANS_TYPE_SELF,
};

static const struct hsm_trans_t tran_Final_Countdown_ev_on_timer_Boom =
{
    // name
    "on_timer",
    // id
    HSM_EVENT_ID_TIME_BOMB_ON_TIMER,
    // guard
    &time_bomb_guard_is_count_zero,
    // action
    NULL,
    // target state
    &state_Boom,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Boom_ev_on_timer___self =
{
    // name
    "on_timer",
    // id
    HSM_EVENT_ID_TIME_BOMB_ON_TIMER,
    // guard
    NULL,
    // action
    &time_bomb_action_express_pitty_on_cutting_the_wrong_wire,
    // target state
    &state_Boom,
    // transition type
    HSM_STATE_TRANS_TYPE_SELF,
};


struct hsm_instance_t time_bomb_instance =
{
    // root state
    &state_time_bomb,
    // user-data
    NULL
};