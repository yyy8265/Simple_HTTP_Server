#pragma once
#include<map>
#include<string>

struct HttpRequest
{
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string,std::string> headers;

};
