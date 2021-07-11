#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"
#include "event_hndl.h"

int8 *FSM_STATE[] = 
{
    (int8 *)"IDLE",
    (int8 *)"ACTIVE",
    (int8 *)"WAIT_RESP",
    (int8 *)"TIMER_EXPIRE",
    (int8 *)"MAX_STATE"
};
int8 *FSM_EVENT[] = 
{
    (int8 *)"INITIATE",
    (int8 *)"SEND_EV",
    (int8 *)"RECEIVE_EV",
    (int8 *)"TIMER_EXPIREY_EV",
    (int8 *)"MAX_EVENT",
};


static fp_action_routine  STATE_MACHINE[MAX_STATE][MAX_EVENT] = 
{
    /*IDLE*/
    {
        unexpected_msg,  /*INITIATE*/
        unexpected_msg,  
        unexpected_msg,
        unexpected_msg
    },
    /*ACTIVE*/
    {
        send_msg,
        unexpected_msg,
        unexpected_msg,
        unexpected_msg
    },
    /*WAIT_RESP*/
    {
        unexpected_msg,
        unexpected_msg,
        unexpected_msg,
        unexpected_msg
    },
    /*TIMER_EXPIRE*/
    {
        unexpected_msg,
        unexpected_msg,
        unexpected_msg,
        unexpected_msg
    },
};

int fsm_entry_func
(
 int16 API,
 int8  *p_msg,
 fsm_context_t *p_gb_fsm_ctxt
)
{

    state_et  state = MAX_STATE;
    event_et  event = MAX_EVENT;

    state = (state_et)p_gb_fsm_ctxt->tcp_sm_ctxt.current_state;
    event = (event_et)API;

    if ((state < MAX_STATE) && (event < MAX_EVENT))
    {
        fprintf(stderr,"Processing STATE[%s] and EVENT[%s]",
                FSM_STATE[state],FSM_EVENT[event]);

        STATE_MACHINE[state][event]((int8 *)p_msg,p_gb_fsm_ctxt);

        fprintf(stderr,"Changing state from STATE[%s] to  STATE[%s]",
                FSM_STATE[state],FSM_STATE[state]);
    }
    else
    {
        fprintf(stderr,"Invalid State or event\n");
    }
    return 0;
}


