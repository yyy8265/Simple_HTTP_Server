#pragma once

#include"static/StaticFileHandler.h"
#include"util/ThreadPool.h"

#include<cstdint>

// 简单的 HTTP 服务器
class HttpServer
{
public:
    explicit HttpServer(uint16_t port,std::string rootDir);

    ~HttpServer();

    void start();

private:
    int serverFd;      // 监听 socket
    uint16_t port;
    StaticFileHandler staticService;

    ThreadPool pool{4};

    // 处理单个客户端连接
    void handleClient(int clinetFd);

};
