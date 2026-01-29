#pragma once
#include<string>
#include<map>

class HttpResponse
{
public:
    int status=200;
    std::string body;
    std::map<std::string,std::string> headers;

    std::string toString() const;
};