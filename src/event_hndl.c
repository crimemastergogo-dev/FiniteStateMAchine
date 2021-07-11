#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "event_hndl.h"
#include "fsm.h"
#include "message.h"
#include "myString.h"
#include <sys/socket.h>       
#include <sys/types.h>       
#include <netinet/in.h>        
#include <arpa/inet.h>          
#include <unistd.h>           
#include <errno.h>      


int unexpected_msg(void * API,fsm_context_t *p_gb_fsm_ctxt)
{
    fprintf(stderr,"Unexpected message received\n");
    return 0;
}
int send_msg(void * API,fsm_context_t *p_gb_fsm_ctxt)
{
     send(p_gb_fsm_ctxt->tcp_sm_ctxt.client,
             p_gb_fsm_ctxt->tcp_sm_ctxt.msg_buff,
             p_gb_fsm_ctxt->tcp_sm_ctxt.msg_len,0);

     return 0;
}


void INITIATE_CONNECTION(Global_context *p_gb_ctxt)
{
    char Encode[sizeof(Message_t)];
    int idx = 0;

    fprintf(stderr,"In INITIATE_CONNECTION: \n");
    p_gb_ctxt->msg.header = INITIATE_LINK; 
    fprintf(stderr,"Enter Initiating message: \n");
    getString(&p_gb_ctxt->msg.message);
    p_gb_ctxt->fsm_ctxt.tcp_sm_ctxt.current_state = ACTIVE; 

    for (idx = 0 ; idx < sizeof(Message_t);idx ++)
        Encode[idx] = pack(&p_gb_ctxt->msg,idx);

    p_gb_ctxt->fsm_ctxt.tcp_sm_ctxt.msg_len = strlen(Encode);
    memcpy(p_gb_ctxt->fsm_ctxt.tcp_sm_ctxt.msg_buff,
            Encode,
            p_gb_ctxt->fsm_ctxt.tcp_sm_ctxt.msg_len);

    fsm_entry_func(INITIATE,
            NULL,&p_gb_ctxt->fsm_ctxt);

    return;
}
