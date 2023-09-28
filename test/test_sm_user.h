#ifndef TEST_SM_USER_H
#define TEST_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hsm.h"

// Stated identifiers
enum Test_SM_states
{
    STATE_ROOT,
    STATE_INITIAL,
    STATE_IDLE,
    STATE_COMPOSITE,
    STATE_COMPOSITE_SUB1,
    STATE_COMPOSITE_SUB2,
    STATE_DEEP_SUB3,
    STATE_DEEP_SUB4,
    STATE_COMPOSITE_SUB3,
    STATE_MAX
};

// User state machine events
enum Test_SM_events
{
    HSM_EVENT_ID_RESERVED = HSM_EVENT_ID_USER,
    HSM_EVENT_ID_TEST_SM_START,
    HSM_EVENT_ID_TEST_SM_GO_COMPOSITE_HISTORY,
    HSM_EVENT_ID_TEST_SM_SWITCH_TO_IDLE,
    HSM_EVENT_ID_TEST_SM_GO_SUB2,
    HSM_EVENT_ID_TEST_SM_GO_SUB3,
    HSM_EVENT_ID_TEST_SM_TRIGGER_REGULAR_SELF_TRANS,
    HSM_EVENT_ID_TEST_SM_TRIGGER_SELF_TRANS,
    HSM_EVENT_ID_TEST_SM_SWITCH_TO_INITIAL,
    HSM_EVENT_ID_TEST_SM_ON_TIMER,
    HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL,
    HSM_EVENT_ID_TEST_SM_GO_TO_SUB2_DIRECT,
    HSM_EVENT_ID_TEST_SM_GO_TO_SUB1_DIRECT,
    HSM_EVENT_ID_TEST_SM_MAX
};

// State machine root object
extern struct hsm_state_t state_Test_SM;

// HSM instance object
extern struct hsm_instance_t Test_SM_instance;

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TEST_SM_USER_H