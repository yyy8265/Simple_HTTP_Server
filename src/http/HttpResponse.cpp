#include"http/HttpResponse.h"

std::string HttpResponse::toString()const
{
    std::string statusLine="HTTP/1.1 200 OK\r\n";
    std::string headerStr;

    for(const auto&[k,v]:headers)
    {
        headerStr=k+": "+v+"\r\n";
    }

    return statusLine+headerStr+"\r\n"+body;

}