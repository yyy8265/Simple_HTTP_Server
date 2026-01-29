#include"http/HttpParser.h"
#include<sstream>

HttpRequest HttpParser::parse(const std::string& raw)
{
    HttpRequest req;
    std::istringstream stream(raw);
    std::string line;

    // 请求行
    if(std::getline(stream,line))
    {
        if(!line.empty()&&line.back()=='\r')
            line.pop_back();

        std::istringstream ls(line);
        ls>>req.method>>req.url>>req.version;
    }

    while(std::getline(stream,line))
    {
        if(line=="\r"||line.empty())
            break;

        if(!line.empty()&&line.back()=='\r')
            line.pop_back();
        
        auto pos=line.find(":");
        if(pos!=std::string::npos)
        {
            req.headers[line.substr(0,pos)]=line.substr(pos+2);
        }
    }

    return req;
}