#ifndef TIME_BOMB_USER_H
#define TIME_BOMB_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hsm.h"

// Stated identifiers
enum time_bomb_states
{
    STATE_ROOT,
    STATE_UNARMED,
    STATE_ARMED,
    STATE_WAIT_FOR_TRIGGER,
    STATE_FINAL_COUNTDOWN,
    STATE_BOOM,
    STATE_MAX
};

// User state machine events
enum time_bomb_events
{
    HSM_EVENT_ID_RESERVED = HSM_EVENT_ID_USER,
    HSM_EVENT_ID_TIME_BOMB_ARM_BUTTON_PRESS,
    HSM_EVENT_ID_TIME_BOMB_WIRE_CUT_EVENT,
    HSM_EVENT_ID_TIME_BOMB_PHONE_CALL_RECEIVED,
    HSM_EVENT_ID_TIME_BOMB_ON_TIMER,
    HSM_EVENT_ID_TIME_BOMB_MAX
};

// HSM instance object
extern struct hsm_instance_t time_bomb_instance;

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TIME_BOMB_USER_H