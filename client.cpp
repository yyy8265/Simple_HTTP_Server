#include <iostream>
#include <thread>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include <vector>
#include <mutex>
#include <arpa/inet.h>

void clinet_task(int id)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("sock");
        return ;
    }

    sockaddr_in server{};
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);

    if(connect(sock,(sockaddr*)&server,sizeof(server))<0)
    {   
        perror("connect");
        close(sock);
        return;
    }

    std::string msg="hello from client"+std::to_string(id);
    send(sock,msg.c_str(),msg.size(),0);

    char buf[1024]{};
    int n=recv(sock,buf,sizeof(buf)-1,0);
    if(n>0)
    {
        std::cout << "[client " << id << "] recv: " << buf << std::endl;
    }

    close(sock);
}

int main()
{
    const int CLIENT_NUM=10;
    std::vector<std::thread> clients;

    for(int i=0;i<CLIENT_NUM;++i)
    {
        clients.emplace_back(clinet_task,i);
    }

    for(auto& t:clients)
    {
        t.join();
    }

    return 0;
}