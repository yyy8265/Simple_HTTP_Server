cmake_minimum_required(VERSION 3.10)

project(my_learn_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(HTTP_SOURCES
    src/http/HttpParser.cpp
    src/http/HttpResponse.cpp
)

set(SERVER_SOURCES
    src/server/HttpServer.cpp
)

add_executable(http_server
    main.cpp
    ${HTTP_SOURCES}
    ${SERVER_SOURCES}
)   

find_package(Threads REQUIRED)
target_link_libraries(http_server PRIVATE Threads::Threads)

add_executable(test_http_parser
    tests/test_http_parser.cpp
    src/http/HttpParser.cpp
)

target_link_libraries(test_http_parser PRIVATE Threads::Threads)


add_executable(test_http_response
    tests/test_http_response.cpp
    src/http/HttpResponse.cpp
)

target_link_libraries(test_http_response PRIVATE Threads::Threads)