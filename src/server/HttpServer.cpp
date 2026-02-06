#include"server/HttpServer.h"
#include"http/HttpParser.h"
#include"http/HttpResponse.h"
#include"http/HttpRequest.h"
#include"util/Logger.h"

#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<thread>
#include<signal.h>
#include<cstring>
#include<cerrno>

constexpr size_t MAX_HEADER_SIZE=8*1024;


HttpServer::HttpServer(uint16_t p,std::string rootDir):port(p),staticService(std::move(rootDir)){}

void HttpServer::start()
{
    signal(SIGPIPE,SIG_IGN);
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

        pool.enqueue([this,clientFd]{
            try
            {
                handleClient(clientFd);
            }
            catch(const std::exception& e)
            {
                Logger::instance().error("Exception in client thread: " + std::string(e.what()));
                close(clientFd);
            }
            catch(...)
            {
                Logger::instance().error("Unknown exception in client thread");
                close(clientFd);
            }  
        });
    }
}

void HttpServer::handleClient(int clientFd)
{
    struct timeval timeout{};
    timeout.tv_sec=5;   // 5秒超时
    timeout.tv_usec=0;

    setsockopt(clientFd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
    setsockopt(clientFd,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));

    char buffer[4096];
    std::string raw;
    raw.reserve(2048);

    // 接收 HTTP 请求
    while(true)
    {
        ssize_t n=recv(clientFd,buffer,sizeof(buffer),0);
        if(n<=0)
        {
            if(n<0&&(errno==EAGAIN||errno==EWOULDBLOCK))
            {
                Logger::instance().warn("Request timeout on fd: " + std::to_string(clientFd));
            }
            close(clientFd);
            return;
        }  

        raw.append(buffer,n);
        
        if(raw.size()>MAX_HEADER_SIZE)
        {
            Logger::instance().error("Request header too large");
            close(clientFd);
            return;
        }

        auto pos=raw.find("\r\n\r\n");
        if(pos!=std::string::npos)
        {
            raw=raw.substr(0,pos+4);
            break;
        }
    }

    HttpRequest req;
    try
    {
        req=HttpParser::parse(raw);
    }
    catch(const std::exception& e)
    {
        Logger::instance().warn(std::string("Failed to parse request: ") + e.what());
        close(clientFd);
        return;
    }

    Logger::instance().info(req.method+" "+req.url);

    if(req.hasBody())
    {
        Logger::instance().warn(
            "Request declares a body (Content-Length=" +
            std::to_string(req.contentLength()) +
            "), but server only supports GET without body. Body will be ignored."
        );
    }

    HttpResponse resp;
    if(req.method!="GET")
    {
        // 方法不被支持
        resp.status=405;
        resp.statusText="Method Not Allowed";

        resp.headers["Allow"]="GET";

        resp.body="405 Method Not Allowed";
        resp.headers["Content-Length"]=std::to_string(resp.body.size());

        Logger::instance().warn("Method not allowed: "+req.method);
    }
    else
    {
        if(!staticService.serve(req,resp))
        {
            resp.status=404;
            resp.statusText="Not Found";
            resp.body="404 Not Found";
            resp.headers["Content-Length"]=std::to_string(resp.body.size());

            Logger::instance().warn("Static file not found: " + req.url);
        }
        else
        {
            Logger::instance().info("Served: " + req.url);
        }
    }


    std::string out=resp.toString();
    ssize_t sent = send(clientFd, out.c_str(), out.size(), 0);
    if(sent<0)
    {
        Logger::instance().warn("Failed to send response: " + std::string(strerror(errno)));
    }
    close(clientFd);

}
