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

set(STATIC_SOURCES
    src/static/StaticFileHandler.cpp
)

set(UTIL_SOURCES
    src/util/ConfigReader.cpp
    src/util/Logger.cpp
    src/util/ThreadPool.cpp
)



find_package(Threads REQUIRED)

# ===== 核心库 =====
add_library(core
    ${HTTP_SOURCES}
    ${SERVER_SOURCES}
    ${STATIC_SOURCES}
    ${UTIL_SOURCES}
)

target_link_libraries(core PRIVATE Threads::Threads)

# ===== 主程序 =====
add_executable(http_server  main.cpp)
target_link_libraries(http_server PRIVATE core)

# 拷贝静态文件到 build 目录
add_custom_command(TARGET http_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/www
    $<TARGET_FILE_DIR:http_server>/www
)
