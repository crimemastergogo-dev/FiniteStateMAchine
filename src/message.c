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

char pack(Message_t *p,int idx)
{
    typedef union
    {
        Message_t temp2;
        char str[sizeof(Message_t)];
    }dump;

    dump D;
    D.temp2.header = p->header;
    memcpy(&D.temp2.message,&p->message,sizeof(String));

    return D.str[idx];
}

Message_t *Unpack(char buffer[sizeof(Message_t)])
{
    Message_t *p_msg   = NULL;
    int idx = 0;
    typedef union
    {
        Message_t temp;
        char str[sizeof(Message_t)];
    }Expand;

    Expand E;
    p_msg = (Message_t *)malloc(sizeof(Message_t));
    if (NULL == p_msg)
    {
        printf("Memory Allocation Failed ...!!!\n");
        exit(1);
    }
    memset(p_msg,0,sizeof(Message_t));

    for (idx = 0 ; idx < sizeof(Message_t); idx++)
        E.str[idx] = buffer[idx];

    p_msg->header = E.temp.header;
    memcpy(&p_msg->message,&E.temp.message,(sizeof(String)));

    return p_msg;
}

int TCP_server(struct sockaddr_in Server_Address,String *p_current_IP)
{
    int     server = 0;

    server = socket(AF_INET,SOCK_STREAM,0);

    Server_Address.sin_addr.s_addr = inet_addr(p_current_IP->chr);
    Server_Address.sin_family      = AF_INET;
    Server_Address.sin_port        = htons(5555);

    bind(server,(struct sockaddr *)&Server_Address,sizeof(Server_Address));
    listen(server,0);
    fprintf(stderr,"Listning at  IP[%s]\n",DisplayString(p_current_IP));
    return server;
}

int TCP_Client(struct sockaddr_in Client_Address,String *p_peer_IP)
{
    int     client = 0;

    client = socket(AF_INET,SOCK_STREAM,0);

    fprintf(stderr,"Connecting to IP[%s]\n",DisplayString(p_peer_IP));
    Client_Address.sin_addr.s_addr = inet_addr(p_peer_IP->chr);
    Client_Address.sin_family      = AF_INET;
    Client_Address.sin_port        = htons(5555);

    connect(client,(struct sockaddr *)&Client_Address,sizeof(Client_Address));
    return client;
}

int main()
{
    Global_context *p_gb_context = NULL;
    String         p_peer_IP;
    String         p_current_IP;
    struct sockaddr_in Server_Address;
    struct sockaddr_in Client_Address;
    int     client = 0;
    int     server = 0;
    int     choice = 0;

    p_gb_context = (Global_context *)malloc(sizeof(Global_context));
    memset(p_gb_context,0,sizeof(Global_context));

    fprintf(stderr,"Enter current IP address \n");
    getString(&p_current_IP);
    server = TCP_server(Server_Address,&p_current_IP);
    if (0 > server)
    {
        fprintf(stderr,"Server Creation failed %d",server);
    }

    do
    {
        fprintf(stderr,"1.INITIATE\n2.SEND\n3.EXIT\n");
        fprintf(stderr,"Enter Choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                fprintf(stderr,"Enter peer IP address \n");
                getString(&p_peer_IP);
                client = TCP_Client(Client_Address,&p_peer_IP);
                if (0 > client)
                {
                    fprintf(stderr,"Connection to server failed Creation failed %d",server);
                }
                p_gb_context->fsm_ctxt.tcp_sm_ctxt.client = client;

                INITIATE_CONNECTION(p_gb_context);
                break;
            }
            case 2:
            {
                break;
            }
            default : printf("Wrong choice...Try again\n");
        }
    }while(1);

    return 0;
}
