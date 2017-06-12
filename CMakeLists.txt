cmake_minimum_required(VERSION 3.4)

project(concurrency CXX)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++14)
endif
