#include<stdio.h>
#include<stdlib.h>
#include"myString.h"
#include"fsm.h"
#include"event_hndl.h"

#ifndef _MESSAGE_
#define _MESSAGE_

typedef enum
{
    INITIATE_LINK,
    SEND
}header_et;

typedef struct
{
    header_et header;
    String    message;
}Message_t;

char pack(Message_t *p_msg,int idx);
Message_t *Unpack(char buffer[sizeof(Message_t)]);

typedef struct
{
    Message_t     msg;
    fsm_context_t fsm_ctxt;
}Global_context;
#endif
