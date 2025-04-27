cmake_minimum_required(VERSION 3.30)
project(SSC)

set(CMAKE_CXX_STANDARD 20)

add_executable(SSC main.cpp
        NFA.cpp
        NFA.h
        DFA.cpp
        DFA.h
        Types.cpp
        Types.h)
