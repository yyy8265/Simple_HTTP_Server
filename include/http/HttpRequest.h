#pragma once

#include<map>
#include<string>

// 表示一个 HTTP 请求
struct HttpRequest
{
    std::string method;     // 请求方法，如 GET
    std::string url;        // 请求路径
    std::string version;    // HTTP 版本
    std::map<std::string,std::string> headers;  // 请求头

};
