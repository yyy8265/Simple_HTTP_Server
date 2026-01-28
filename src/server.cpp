#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<atomic>
#include<algorithm>
#include<sstream>
#include "server.h"

std::atomic<int> client_count{0};
std::mutex count_mtx;
std::mutex log_mtx;


void handle_client(int client_fd)
{
    char buffer[4096]{0};
    std::string request;
    httpRequest req;
    while (true)
    {
        int n=recv(client_fd,buffer,sizeof(buffer)-1,0);
        if(n<=0)
            break;
        request.append(buffer,n);
        if(request.find("\r\n\r\n")!=std::string::npos)
            break;
    }

    req=parseHttpRequest(request);
    std::cout << "Method: " << req.method << "\n";
    std::cout << "URI: " << req.url << "\n";
    std::cout << "Version: " << req.version << "\n";

    for(auto &[k,v]: req.headers)
    {
        std::cout<<k<<" : "<<v<<std::endl;
    }

    std::cout << "======= HTTP REQUEST BEGIN =======" << std::endl;
    std::cout << request << std::endl;
    std::cout << "======= HTTP REQUEST END =======" << std::endl;

    int cur=client_count.fetch_add(1)+1;
    {
        std::lock_guard<std::mutex> lock(log_mtx);
        std::cout<<"count= "<<cur<<std::endl;
    }
    std::string body="<h1>hello world</h1>";
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: "+std::to_string(body.size())+"\r\n"
        "Connection: close\r\n"
        "\r\n"+
        body
        ;

    send(client_fd,response.c_str(),response.size(),0);

    close(client_fd);
}


httpRequest parseHttpRequest(const std::string &request)
{
    httpRequest req;
    std::istringstream stream(request);
    std::string line;

    if(std::getline(stream,line))
    {
        std::istringstream lineStream(line);
        lineStream>>req.method>>req.url>>req.version;
    }
    

    while(std::getline(stream,line))
    {
        if(!line.empty()&&line.back()=='\r')
            line.pop_back();

        auto pos =line.find(": ");
        if(pos!=std::string::npos)
        {
            std::string key=line.substr(0,pos);
            std::string value=line.substr(pos+2);
            req.headers[key]=value;
        }

    }

    return req;
}