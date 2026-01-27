#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<atomic>
#include "hello.h"

std::atomic<int> client_count{0};
std::mutex count_mtx;
std::mutex log_mtx;


void handle_client(int client_fd)
{
    char buf[1024];
    int cur=client_count.fetch_add(1)+1;
    {
        std::lock_guard<std::mutex> lock(log_mtx);
        std::cout<<"count= "<<cur<<std::endl;
    }


    while(true)
    {

        ssize_t n =recv(client_fd,buf,sizeof(buf),0);
        if(n<=0)    break;

        send(client_fd,buf,n,0);
    }

    close(client_fd);
}
