#pragma once
#include<cstdint>
#include"static/StaticFileHandler.h"

class HttpServer
{
public:
    explicit HttpServer(uint16_t port,std::string rootDir);
    void start();

private:
    int server_fd;
    uint16_t port;
    StaticFileHandler staticService;

    void handleClinet(int clinet_fd);

};
