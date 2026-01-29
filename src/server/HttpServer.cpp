#include"http/HttpParser.h"
#include"http/HttpResponse.h"
#include"http/HttpRequest.h"
#include"server/HttpServer.h"

#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<thread>
#include<iostream>

HttpServer::HttpServer(uint16_t p):port(p){}

void HttpServer::start()
{
    server_fd=socket(AF_INET,SOCK_STREAM,0);

    int opt=1;
    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);

    bind(server_fd,(sockaddr *)&addr,sizeof(addr));
    listen(server_fd,5);

    std::cout << "HTTP server listening on " << port << std::endl;

    while(true)
    {
        int client_fd=accept(server_fd,nullptr,nullptr);
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

    std::cout << req.method << " " << req.url << std::endl;

    HttpResponse resp;
    resp.body="<h1>Hello World</h1>";
    resp.headers["Content-Type"]="text/html";
    resp.headers["Content-Length"] = std::to_string(resp.body.size());
    resp.headers["Connection"] = "close";

    std::string out=resp.toString();

    send(client_fd, out.c_str(), out.size(), 0);
    close(client_fd);

}
