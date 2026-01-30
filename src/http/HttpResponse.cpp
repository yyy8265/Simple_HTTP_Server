#include"http/HttpResponse.h"
#include"util/Logger.h"

#include<ostream>
#include<sstream>

std::string HttpResponse::toString()const
{
    std::ostringstream oss;
    oss << "HTTP/1.1 " << status << " " << statusText << "\r\n";
    for(auto& [k,v]:headers)
    {
        oss<<k<<": "<<v<<"\r\n";
    }

    oss<<"\r\n"<<body;

    Logger::instance().info(
        "Response built: status=" + std::to_string(status) +
        ", body_size=" + std::to_string(body.size())
    );

    return oss.str();
}