#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include "hello.h"

void say_hello() {
    std::cout << "Hello CMake C++ Linux" << std::endl;
}

void another_hello()
{
std::cout<<"hello in the new branch"<<std::endl;
}

void handle_client(int client_fd)
{
    char buf[1024];

    while(true)
    {
        ssize_t n =recv(client_fd,buf,sizeof(buf),0);
        if(n<=0)    break;

        send(client_fd,buf,n,0);
    }

    close(client_fd);
}
