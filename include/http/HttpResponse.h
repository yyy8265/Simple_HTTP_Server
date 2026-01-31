#pragma once

#include<string>
#include<map>

// HTTP 响应对象
class HttpResponse
{
public:
    int status=200;
    std::string statusText="OK";
    std::string body;
    std::map<std::string,std::string> headers;

    std::string toString() const;
};