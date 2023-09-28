#include <stddef.h>
#include "hsm.h"
#include "Test_SM_config_user.h"
#include "Test_SM_user.h"


static const struct hsm_trans_t tran_Initial_ev_start_Composite;
static const struct hsm_trans_t tran_Initial_ev_go_composite_history___history_Composite;
static const struct hsm_trans_t tran_Initial_ev_switch_to_idle_Idle;
static const struct hsm_trans_t tran_Initial_ev_go_sub2_Composite_Sub2;
static const struct hsm_trans_t tran_Initial_ev_go_sub3_Composite_Sub3;
static const struct hsm_trans_t tran_Initial_ev_trigger_regular_self_trans_Initial;
static const struct hsm_trans_t tran_Initial_ev_trigger_self_trans___self;
static const struct hsm_trans_t tran_Idle_ev_switch_to_initial_Initial;
static const struct hsm_trans_t tran_Composite_Sub1_ev_on_timer_Composite_Sub2;
static const struct hsm_trans_t tran_Composite_Sub1_ev_go_to_initial_Initial;
static const struct hsm_trans_t tran_Composite_Sub2_ev_go_to_initial_Initial;
static const struct hsm_trans_t tran_Deep_Sub3_ev_go_to_initial_Initial;
static const struct hsm_trans_t tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2;
static const struct hsm_trans_t tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1;
static const struct hsm_trans_t tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2;
static const struct hsm_trans_t tran_Composite_Sub3_ev_go_to_initial_Initial;


static const p_hsm_trans_t trans_Initial[] =
{
    &tran_Initial_ev_start_Composite,
    &tran_Initial_ev_go_composite_history___history_Composite,
    &tran_Initial_ev_switch_to_idle_Idle,
    &tran_Initial_ev_go_sub2_Composite_Sub2,
    &tran_Initial_ev_go_sub3_Composite_Sub3,
    &tran_Initial_ev_trigger_regular_self_trans_Initial,
    &tran_Initial_ev_trigger_self_trans___self,
    NULL
};

static const p_hsm_trans_t trans_Idle[] =
{
    &tran_Idle_ev_switch_to_initial_Initial,
    NULL
};


static const p_hsm_trans_t trans_Composite_Sub1[] =
{
    &tran_Composite_Sub1_ev_on_timer_Composite_Sub2,
    &tran_Composite_Sub1_ev_go_to_initial_Initial,
    NULL
};

static const p_hsm_trans_t trans_Composite_Sub2[] =
{
    &tran_Composite_Sub2_ev_go_to_initial_Initial,
    NULL
};

static const p_hsm_trans_t trans_Deep_Sub3[] =
{
    &tran_Deep_Sub3_ev_go_to_initial_Initial,
    &tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2,
    NULL
};

static const p_hsm_trans_t trans_Deep_Sub4[] =
{
    &tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1,
    NULL
};

static const p_hsm_trans_t trans_Composite_Sub3[] =
{
    &tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2,
    &tran_Composite_Sub3_ev_go_to_initial_Initial,
    NULL
};


// Test_SM states forward declarations
static struct hsm_state_t state_Initial;
static struct hsm_state_t state_Idle;
static struct hsm_state_t state_Composite;
static struct hsm_state_t state_Composite_Sub1;
static struct hsm_state_t state_Composite_Sub2;
static struct hsm_state_t state_Deep_Sub3;
static struct hsm_state_t state_Deep_Sub4;
static struct hsm_state_t state_Composite_Sub3;

// Test_SM root state definition
struct hsm_state_t state_Test_SM =
{
    {
        // name
        "state_Test_SM",
        // id
        STATE_ROOT,
        // p_trans_list
        NULL,
        // p_parent_state
        NULL,
        // p_initial_state,
        &state_Initial,
        // p_entry
        NULL,
        // p_exit
        NULL
    },
    // p_history_state
    &state_Initial,
    // p_active_state
    &state_Test_SM
};
static struct hsm_state_t state_Initial =
{
    // ROM config
    {
        // name
        "state_Initial",
        // id
        STATE_INITIAL,
        // pTransitionList
        trans_Initial,
        // pParent
        &state_Test_SM,
        // p_initial_state,
        &state_Initial,
        // onEntryFunc
        &Test_SM_on_entry_Initial,
        // onExitFunc
        &Test_SM_on_exit_Initial,
    },
    // pHistoryState
    &state_Initial,
    // pActiveState
    &state_Initial
};

static struct hsm_state_t state_Idle =
{
    // ROM config
    {
        // name
        "state_Idle",
        // id
        STATE_IDLE,
        // pTransitionList
        trans_Idle,
        // pParent
        &state_Test_SM,
        // p_initial_state,
        &state_Idle,
        // onEntryFunc
        &Test_SM_on_entry_Idle,
        // onExitFunc
        &Test_SM_on_exit_Idle,
    },
    // pHistoryState
    &state_Idle,
    // pActiveState
    &state_Idle
};

static struct hsm_state_t state_Composite =
{
    // ROM config
    {
        // name
        "state_Composite",
        // id
        STATE_COMPOSITE,
        // pTransitionList
        NULL,
        // pParent
        &state_Test_SM,
        // p_initial_state,
        &state_Composite_Sub1,
        // onEntryFunc
        &Test_SM_on_entry_Composite,
        // onExitFunc
        &Test_SM_on_exit_Composite,
    },
    // pHistoryState
    &state_Composite_Sub1,
    // pActiveState
    &state_Composite
};

static struct hsm_state_t state_Composite_Sub1 =
{
    // ROM config
    {
        // name
        "state_Composite_Sub1",
        // id
        STATE_COMPOSITE_SUB1,
        // pTransitionList
        trans_Composite_Sub1,
        // pParent
        &state_Composite,
        // p_initial_state,
        &state_Composite_Sub1,
        // onEntryFunc
        &Test_SM_on_entry_Composite_Sub1,
        // onExitFunc
        &Test_SM_on_exit_Composite_Sub1,
    },
    // pHistoryState
    &state_Composite_Sub1,
    // pActiveState
    &state_Composite_Sub1
};

static struct hsm_state_t state_Composite_Sub2 =
{
    // ROM config
    {
        // name
        "state_Composite_Sub2",
        // id
        STATE_COMPOSITE_SUB2,
        // pTransitionList
        trans_Composite_Sub2,
        // pParent
        &state_Composite,
        // p_initial_state,
        &state_Composite_Sub2,
        // onEntryFunc
        &Test_SM_on_entry_Composite_Sub2,
        // onExitFunc
        &Test_SM_on_exit_Composite_Sub2,
    },
    // pHistoryState
    &state_Composite_Sub2,
    // pActiveState
    &state_Composite_Sub2
};

static struct hsm_state_t state_Deep_Sub3 =
{
    // ROM config
    {
        // name
        "state_Deep_Sub3",
        // id
        STATE_DEEP_SUB3,
        // pTransitionList
        trans_Deep_Sub3,
        // pParent
        &state_Composite_Sub3,
        // p_initial_state,
        &state_Deep_Sub3,
        // onEntryFunc
        &Test_SM_on_entry_Deep_Sub3,
        // onExitFunc
        &Test_SM_on_exit_Deep_Sub3,
    },
    // pHistoryState
    &state_Deep_Sub3,
    // pActiveState
    &state_Deep_Sub3
};

static struct hsm_state_t state_Deep_Sub4 =
{
    // ROM config
    {
        // name
        "state_Deep_Sub4",
        // id
        STATE_DEEP_SUB4,
        // pTransitionList
        trans_Deep_Sub4,
        // pParent
        &state_Composite_Sub3,
        // p_initial_state,
        &state_Deep_Sub4,
        // onEntryFunc
        &Test_SM_on_entry_Deep_Sub4,
        // onExitFunc
        &Test_SM_on_exit_Deep_Sub4,
    },
    // pHistoryState
    &state_Deep_Sub4,
    // pActiveState
    &state_Deep_Sub4
};

static struct hsm_state_t state_Composite_Sub3 =
{
    // ROM config
    {
        // name
        "state_Composite_Sub3",
        // id
        STATE_COMPOSITE_SUB3,
        // pTransitionList
        trans_Composite_Sub3,
        // pParent
        &state_Composite,
        // p_initial_state,
        &state_Deep_Sub3,
        // onEntryFunc
        &Test_SM_on_entry_Composite_Sub3,
        // onExitFunc
        &Test_SM_on_exit_Composite_Sub3,
    },
    // pHistoryState
    &state_Deep_Sub3,
    // pActiveState
    &state_Composite_Sub3
};

static const struct hsm_trans_t tran_Initial_ev_start_Composite =
{
    // name
    "start",
    // id
    HSM_EVENT_ID_TEST_SM_START,
    // guard
    &Test_SM_guard_start_conditions_met,
    // action
    &Test_SM_action_on_start_action,
    // target state
    &state_Composite,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Initial_ev_go_composite_history___history_Composite =
{
    // name
    "go_composite_history",
    // id
    HSM_EVENT_ID_TEST_SM_GO_COMPOSITE_HISTORY,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite,
    // transition type
    HSM_STATE_TRANS_TYPE_HISTORY
};

static const struct hsm_trans_t tran_Initial_ev_switch_to_idle_Idle =
{
    // name
    "switch_to_idle",
    // id
    HSM_EVENT_ID_TEST_SM_SWITCH_TO_IDLE,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Idle,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Initial_ev_go_sub2_Composite_Sub2 =
{
    // name
    "go_sub2",
    // id
    HSM_EVENT_ID_TEST_SM_GO_SUB2,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite_Sub2,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Initial_ev_go_sub3_Composite_Sub3 =
{
    // name
    "go_sub3",
    // id
    HSM_EVENT_ID_TEST_SM_GO_SUB3,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite_Sub3,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Initial_ev_trigger_regular_self_trans_Initial =
{
    // name
    "trigger_regular_self_trans",
    // id
    HSM_EVENT_ID_TEST_SM_TRIGGER_REGULAR_SELF_TRANS,
    // guard
    NULL,
    // action
    &Test_SM_action_on_regular_self_action,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Initial_ev_trigger_self_trans___self =
{
    // name
    "trigger_self_trans",
    // id
    HSM_EVENT_ID_TEST_SM_TRIGGER_SELF_TRANS,
    // guard
    NULL,
    // action
    &Test_SM_action_on_self_action,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_SELF,
};

static const struct hsm_trans_t tran_Idle_ev_switch_to_initial_Initial =
{
    // name
    "switch_to_initial",
    // id
    HSM_EVENT_ID_TEST_SM_SWITCH_TO_INITIAL,
    // guard
    &Test_SM_guard_initial_cond_met,
    // action
    &Test_SM_action_on_initial_switch_action,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Composite_Sub1_ev_on_timer_Composite_Sub2 =
{
    // name
    "on_timer",
    // id
    HSM_EVENT_ID_TEST_SM_ON_TIMER,
    // guard
    &Test_SM_guard_entry_to_sub2_allowed,
    // action
    &Test_SM_action_composite_sub2_action,
    // target state
    &state_Composite_Sub2,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Composite_Sub1_ev_go_to_initial_Initial =
{
    // name
    "go_to_initial",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Composite_Sub2_ev_go_to_initial_Initial =
{
    // name
    "go_to_initial",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Deep_Sub3_ev_go_to_initial_Initial =
{
    // name
    "go_to_initial",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2 =
{
    // name
    "go_to_sub2_direct",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_SUB2_DIRECT,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite_Sub2,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1 =
{
    // name
    "go_to_sub1_direct",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_SUB1_DIRECT,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite_Sub1,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2 =
{
    // name
    "go_to_sub2_direct",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_SUB2_DIRECT,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Composite_Sub2,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};

static const struct hsm_trans_t tran_Composite_Sub3_ev_go_to_initial_Initial =
{
    // name
    "go_to_initial",
    // id
    HSM_EVENT_ID_TEST_SM_GO_TO_INITIAL,
    // guard
    NULL,
    // action
    NULL,
    // target state
    &state_Initial,
    // transition type
    HSM_STATE_TRANS_TYPE_REGULAR
};


struct hsm_instance_t Test_SM_instance =
{
    // root state
    &state_Test_SM,
    // user-data
    NULL
};