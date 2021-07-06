#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"event_hndl"
#include"fsm.h"
#include"myString.h"
#include <sys/socket.h>       
#include <sys/types.h>       
#include <netinet/in.h>        
#include <arpa/inet.h>          
#include <unistd.h>           
#include <errno.h>      

int TCP_server(struct sockaddr_in Server_Address)
{
    int     server = 0;

    server = socket(AF_INET,SOCK_STREAM,0);

    Server_Address.sin_addr.s_addr = INADDR_ANY;
    Server_Address.sin_family      = AF_INET;
    Server_Address.sin_port        = htons(5555);

    bind(server,(struct sockaddr *)&Server_Address,sizeof(Server_Address));
    listen(server,0);
    return server;
}

int TCP_Client(struct sockaddr_in Client_Address)
{
    int     client = 0;

    client = socket(AF_INET,SOCK_STREAM,0);

    Client_Address.sin_addr.s_addr = inet_addr("127.0.0.1");
    Client_Address.sin_family      = AF_INET;
    Client_Address.sin_port        = htons(5555);

    connect(client,(struct sockaddr *)&Client_Address,sizeof(Client_Address));
    return client;
}

int main()
{
    struct sockaddr_in Server_Address;
    struct sockaddr_in Client_Address;
    int     client = 0;
    int     server = 0;

    server = TCP_server(Server_Address);
    if (0 > server)
    {
        fprintf(stderr,"Server Creation failed %d",server);
    }
    
    client = TCP_Client(Client_Address);
    if (0 > client)
    {
        fprintf(stderr,"Connection to server failed Creation failed %d",server);
    }

    do
    {
    }while(1);

    return 0;
}
