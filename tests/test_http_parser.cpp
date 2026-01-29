#include "http/HttpParser.h"
#include <cassert>
#include <iostream>

void test_basic_request()
{
    std::string raw =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";

    HttpRequest req = HttpParser::parse(raw);

    assert(req.method == "GET");
    assert(req.url == "/index.html");
    assert(req.version == "HTTP/1.1");
    assert(req.headers["Host"] == "localhost");
    assert(req.headers["Connection"] == "close");
}

void test_no_headers()
{
    std::string raw =
        "GET / HTTP/1.1\r\n"
        "\r\n";

    HttpRequest req = HttpParser::parse(raw);

    assert(req.method == "GET");
    assert(req.url == "/");
    assert(req.headers.empty());
}

int main()
{
    test_basic_request();
    test_no_headers();

    std::cout << "[PASS] HttpParser tests\n";
    return 0;
}
