
#include "fsm.h"
#include "event_hndl.h"

int unexpected_msg(void * API,fsm_context_t *p_gb_fsm_ctxt)
{
    fprintf(stderr,"Unexpected message received\n");
    return 0;
}

