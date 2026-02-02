#include"static/StaticFileHandler.h"
#include"util/Logger.h"

#include<fstream>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<ostream>
#include<filesystem>

namespace fs=std::filesystem;

bool StaticFileHandler::serve(const HttpRequest& req,HttpResponse& resp)
{
    if(req.method!="GET")
    {
        Logger::instance().warn("Unsupported method for static file: " + req.method);
        return false;
    }

    try
    {
        fs::path root=fs::canonical(rootDir);
        fs::path requested=fs::path(req.url).relative_path();

        if(requested.empty()||requested.filename()=="/")
        {
            requested/="index.html";
        }

        fs::path fullPath=fs::canonical(root/requested);

        if(fullPath.string().find(root.string())!=0)
        {
            Logger::instance().warn("Path traversal attempt: " + req.url);

            resp.status=403;
            resp.statusText="Forbidden";
            resp.body="403 Forbidden";
            resp.headers["Content-Length"]=std::to_string(resp.body.size());

            return true;
        }

        std::ifstream file(fullPath,std::ios::binary);
        if(!file)
        {
            throw std::runtime_error("File not found");
        }

        std::ostringstream ss;
        ss<<file.rdbuf();

        resp.body=ss.str();
        resp.headers["Content-Type"]=getMimeType(fullPath.string());
        resp.headers["Content-Length"]=std::to_string(resp.body.size());

        Logger::instance().info(
            "Serving static file: " + fullPath.string() +
            ", size=" + std::to_string(resp.body.size())
        );

        return true;
    }
    catch(const std::exception& e)
    {
        Logger::instance().warn("Static file error: " + std::string(e.what()));

        resp.status=404;
        resp.statusText="Not Found";
        resp.body = "404 Not Found";
        resp.headers["Content-Length"]=std::to_string(resp.body.size());

        return true;
    }
    
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

    std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);

    auto it=mimeType.find(ext);
    if(it!=mimeType.end())
    {
        return it->second;
    }

    return "application/octet-stream";

}