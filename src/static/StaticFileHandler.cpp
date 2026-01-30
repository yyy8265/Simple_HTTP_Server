#include"static/StaticFileHandler.h"
#include"util/Logger.h"

#include<fstream>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<ostream>

bool StaticFileHandler::serve(const HttpRequest& req,HttpResponse& resp)
{
    if(req.method!="GET")
    {
        Logger::instance().warn("Unsupported method for static file: " + req.method);
        return false;
    }

    std::string path=rootDir+req.url;
    if(path.back()=='/')
    {
        path+="index.html";
    }

    std::ifstream file(path,std::ios::binary);
    if(!file)
    {
        resp.status=404;
        resp.statusText="Not Found";
        resp.body="404 Not Found";
        resp.headers["Content-Length"]=std::to_string(resp.body.size());

        Logger::instance().warn("Static file not found: " + path);
        return true;
    }

    std::ostringstream ss;
    ss<<file.rdbuf();
    resp.body=ss.str();
    resp.headers["Content-Type"]=getMimeType(path);
    resp.headers["Content-Length"]=std::to_string(resp.body.size());

    Logger::instance().info(
        "Serving static file: " + path +
        ", size=" + std::to_string(resp.body.size())
    );

    return true;
}

std::string StaticFileHandler::getMimeType(const std::string& path)
{
    static const std::unordered_map<std::string,std::string> mimeType={
        {".html", "text/html"},
        {".htm",  "text/html"},
        {".txt",  "text/plain"},
        {".css",  "text/css"},
        {".js",   "application/javascript"},
        {".json", "application/json"},
        {".png",  "image/png"},
        {".jpg",  "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif",  "image/gif"}
    };

    auto pos=path.find_last_of('.');
    if(pos==std::string::npos)
    {
        return "application/octet-stream";
    }

    std::string ext=path.substr(pos);
    auto it=mimeType.find(ext);
    if(it!=mimeType.end())
    {
        return it->second;
    }

    return "application/octet-stream";

}