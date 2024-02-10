cmake_minimum_required(VERSION 3.27)
project(learning_with_errors)

set(CMAKE_CXX_STANDARD 23)

add_executable(learning_with_errors main.cpp
        lwe.h)
