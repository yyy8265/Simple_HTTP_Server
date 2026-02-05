#include"http/HttpParser.h"
#include"util/Logger.h"

#include<sstream>
#include<algorithm>

HttpRequest HttpParser::parse(const std::string& raw)
{
    HttpRequest req;
    std::istringstream stream(raw);
    std::string line;

    // 解析请求行
    if(std::getline(stream,line))
    {
        if(!line.empty()&&line.back()=='\r')
            line.pop_back();

        std::istringstream ls(line);

        if(!(ls>>req.method>>req.url>>req.version))
	{
		throw std::runtime_error("Invalid HTTP request line");
	}

	if(req.version.substr(0,5)!="HTTP/")
	{
		throw std::runtime_error("Invalid HTTP version");
	}

        Logger::instance().info(
            "Parsed request line: " + req.method + " " + req.url + " " + req.version
        );
    }
    else
    {
        Logger::instance().warn("Empty HTTP request");
        return req;
    }

    // 解析请求头
    while(std::getline(stream,line))
    {
        if(line=="\r"||line.empty())
            break;

        if(!line.empty()&&line.back()=='\r')
            line.pop_back();
        
        auto pos=line.find(":");
        if(pos!=std::string::npos)
        {
            std::string key=line.substr(0,pos);
            std::string value=line.substr(pos+1);

            // 去掉前后空格
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);

            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // 统一 key 小写
            std::transform(key.begin(),key.end(),key.begin(),::tolower);

            req.headers[key]=value;
            
            Logger::instance().info(
                "Header parsed: " + key + " = " + value
            );

        }
    }

    return req;
}
