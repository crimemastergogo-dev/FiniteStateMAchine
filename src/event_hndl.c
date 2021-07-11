#include "fsm.h"
#include "message.h"
#include "event_hndl.h"

int unexpected_msg(void * API,fsm_context_t *p_gb_fsm_ctxt)
{
    fprintf(stderr,"Unexpected message received\n");
    return 0;
}


void INITIATE_CONNECTION(Global_context *p_gb_ctxt)
{
    return;
}
