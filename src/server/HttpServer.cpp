#include"http/HttpParser.h"
#include"http/HttpResponse.h"
#include"http/HttpRequest.h"
#include"server/HttpServer.h"
#include"util/Logger.h"

#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<thread>
#include<iostream>

HttpServer::HttpServer(uint16_t p,std::string rootDir):port(p),staticService(std::move(rootDir)){}

void HttpServer::start()
{
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0)
    {
        Logger::instance().error("Failed to create socket");
        return;
    }

    int opt=1;
    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);

    if(bind(server_fd,(sockaddr *)&addr,sizeof(addr))<0)
    {
        Logger::instance().error("Bind failed");
        return;
    }

    listen(server_fd,5);
    Logger::instance().info("HTTP server listening on port "+std::to_string(port));

    while(true)
    {
        int client_fd=accept(server_fd,nullptr,nullptr);
        if(client_fd<0)
        {
            Logger::instance().warn("Failed to accept client connection");
            continue;
        }

        std::thread(&HttpServer::handleClinet,this,client_fd).detach();
    }
}

void HttpServer::handleClinet(int client_fd)
{
    char buffer[4096];
    std::string raw;

    while(true)
    {
        int n=recv(client_fd,buffer,sizeof(buffer),0);
        if(n<=0)
            break;

        raw.append(buffer,n);
        if(raw.find("\r\n\r\n")!=std::string::npos)
        {
            break;
        }
    }

    HttpRequest req=HttpParser::parse(raw);

    Logger::instance().info(req.method+" "+req.url);

    HttpResponse resp;
    if(!staticService.serve(req,resp))
    {
        resp.status=400;
        resp.statusText="Bad Request";
        Logger::instance().warn("Bad request: " + req.url);
    }
    else
    {
        Logger::instance().info("Served: " + req.url);
    }


    std::string out=resp.toString();
    send(client_fd, out.c_str(), out.size(), 0);
    close(client_fd);

}
