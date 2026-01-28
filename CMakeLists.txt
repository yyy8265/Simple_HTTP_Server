cmake_minimum_required(VERSION 3.10)

project(my_learn_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    src/main.cpp
    src/server.cpp
)

target_include_directories(main
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
