cmake_minimum_required(VERSION 3.17)
project(program_06_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        program_06_client
        main.cpp
        Kid.cpp
        Kid.h
        Socket.cpp
        Socket.h
        tools.cpp
        tools.hpp
)