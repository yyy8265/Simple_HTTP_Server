#include "http/HttpResponse.h"
#include <cassert>
#include <iostream>

void test_basic_response()
{
    HttpResponse resp;
    resp.body = "<h1>OK</h1>";
    resp.headers["Content-Type"] = "text/html";
    resp.headers["Content-Length"] = "11";

    std::string out = resp.toString();

    assert(out.find("HTTP/1.1 200 OK\r\n") == 0);
    assert(out.find("Content-Type: text/html\r\n") != std::string::npos);
    assert(out.find("\r\n\r\n<h1>OK</h1>") != std::string::npos);
}

int main()
{
    test_basic_response();
    std::cout << "[PASS] HttpResponse tests\n";
    return 0;
}
