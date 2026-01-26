#include "hello.h"
#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<thread>

int main()
{
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0)
    {
        perror("server");
        return 1;
    }

    int opt=1;
    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("bind");
        return 1;
    }

    listen(server_fd,5);
    std::cout<<"echo server listening on 8080 ...."<<std::endl;

    sockaddr_in clientaddr{};
    socklen_t len=sizeof(clientaddr);

    while(true)
    {
        int client_fd=accept(server_fd,nullptr,nullptr);
        if(client_fd<0)
        {
            perror("accpet");
            continue;
        }

        std::cout<<"client connected"<<std::endl;

        std::thread t(handle_client,client_fd);
        t.detach();
        
    }

    close(server_fd);
}

