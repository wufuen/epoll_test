#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include "epoll_test.h"


void print_usage(void)
{
    printf("epoll_test listen_port\n");
}
int cs_set[1024];

int main(int argc,void * argv[])
{
    if(argc < 2)
    print_usage();

    int port = atoi(argv[1]);
    int ss,cs;
    
    struct sockaddr_in ss_addr, peer_addr;
    socklen_t peer_addr_size;
    
    int cs_num = 0;
    memset(cs_set,0,sizeof(cs_set));

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss == -1)
    perror("socket");

    memset(&ss_addr, 0, sizeof(struct sockaddr_in));
    /*  init addr */
    ss_addr.sin_family = AF_INET;
    ss_addr.sin_port  = htons(port);
    ss_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    

    if (bind(ss, (struct sockaddr *) &ss_addr,sizeof(struct sockaddr)) == -1)
    perror("bind");

    if (listen(ss, 1024) == -1)
    perror("listen");

    /* Now we can accept incoming connections one
       at a time using accept(2) */

    peer_addr_size = sizeof(struct sockaddr_in);
    do{
        cs = accept(ss, (struct sockaddr *) &peer_addr,&peer_addr_size);
        if (cs == -1)
        {
            perror("accept");
            break;
        }
        cs_set[cs_num] = cs;
        cs_num++;

    }while(1);

    for(int i = 0;i<cs_num;i++)
    {
        close(cs_set[i]);
    }

    
    close(ss);
    return 0;
}
