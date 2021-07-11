#include <stdlib.h>
#include <stdio.h>

#ifndef _FSM_FRAMEWORK_
#define _FSM_FRAMEWORK_

#define MAX_MSG_LEN     1460 
typedef unsigned char   int8;
typedef unsigned short  int16;
typedef unsigned int    int32;



typedef enum
{
    IDLE,
    ACTIVE,
    WAIT_RESP,
    TIMER_EXPIRE,
    MAX_STATE
}state_et;

typedef enum
{
    INITIATE,
    SEND_EV,
    RECEIVE_EV,
    TIMER_EXPIREY_EV,
    MAX_EVENT
}event_et;


typedef struct
{
    int32 current_state;
    int8  msg_buff[MAX_MSG_LEN];
    int16 msg_len;
}TCP_socket_sm_ctx_t;

typedef struct
{
    TCP_socket_sm_ctx_t tcp_sm_ctxt;
}fsm_context_t;

typedef int (*fp_action_routine)
(
 void  *p_msg,
 fsm_context_t *p_gb_fsm_ctxt
);


int fsm_entry_func
(
 int16 API,
 int8  *p_msg,
 fsm_context_t *p_gb_fsm_ctxt
);

#endif
