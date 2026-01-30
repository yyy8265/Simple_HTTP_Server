#pragma once
#include<string>
#include"http/HttpRequest.h"
#include"http/HttpResponse.h"

class StaticFileHandler
{
public:
    StaticFileHandler(std::string root):rootDir(std::move(root)){}

    bool serve(const HttpRequest& req,HttpResponse& resp);

    std::string getMimeType(const std::string& path);
    
private:
    std::string rootDir;
};