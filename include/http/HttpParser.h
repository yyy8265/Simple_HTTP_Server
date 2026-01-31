#pragma once

#include"HttpRequest.h"

#include<string>

// 负责将原始 HTTP 请求字符串解析为 HttpRequest 结构体。
class HttpParser
{
public:
    static HttpRequest parse(const std::string& raw);
    
};