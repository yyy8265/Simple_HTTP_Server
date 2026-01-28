#pragma once
#include<mutex>
#include<map>
#include<cstring>

extern std::mutex log_mtx;

struct  httpRequest
{
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string,std::string> headers;
};

httpRequest parseHttpRequest(const std::string& request);

void handle_client(int client_fd);


