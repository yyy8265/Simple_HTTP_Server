#include"server/HttpServer.h"
#include"http/HttpParser.h"
#include"http/HttpResponse.h"
#include"http/HttpRequest.h"
#include"util/Logger.h"

#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<thread>

HttpServer::HttpServer(uint16_t p,std::string rootDir):port(p),staticService(std::move(rootDir)){}

void HttpServer::start()
{
    serverFd=socket(AF_INET,SOCK_STREAM,0);
    if(serverFd<0)
    {
        Logger::instance().error("Failed to create socket");
        return;
    }

    int opt=1;
    setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);

    if(bind(serverFd,(sockaddr *)&addr,sizeof(addr))<0)
    {
        Logger::instance().error("Bind failed");
        return;
    }

    listen(serverFd,5);
    Logger::instance().info("HTTP server listening on port "+std::to_string(port));

    while(true)
    {
        int clientFd=accept(serverFd,nullptr,nullptr);
        if(clientFd<0)
        {
            Logger::instance().warn("Failed to accept client connection");
            continue;
        }

        std::thread(&HttpServer::handleClient,this,clientFd).detach();
    }
}

void HttpServer::handleClient(int clientFd)
{
    char buffer[4096];
    std::string raw;

    // 接收 HTTP 请求
    while(true)
    {
        int n=recv(clientFd,buffer,sizeof(buffer),0);
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
    send(clientFd, out.c_str(), out.size(), 0);
    close(clientFd);

}
