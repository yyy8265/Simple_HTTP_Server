#pragma once
#include"HttpRequest.h"
#include<string>

class HttpParser
{
public:
    static HttpRequest parse(const std::string& raw);
    
};