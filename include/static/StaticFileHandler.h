#pragma once

#include"http/HttpRequest.h"
#include"http/HttpResponse.h"

#include<string>

// 静态文件请求处理器
class StaticFileHandler
{
public:
    StaticFileHandler(std::string root):rootDir(std::move(root)){}

    // 处理静态文件请求  true 表示请求已处理（成功或 404） false 表示请求不支持
    bool serve(const HttpRequest& req,HttpResponse& resp);

    std::string getMimeType(const std::string& path);
    
private:
    std::string rootDir;
};