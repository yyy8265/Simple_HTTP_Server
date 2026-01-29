#pragma once
#include<cstdint>

class HttpServer
{
public:
    explicit HttpServer(uint16_t port);
    void start();

private:
    int server_fd;
    uint16_t port;

    void handleClinet(int clinet_fd);

};
