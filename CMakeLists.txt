cmake_minimum_required(VERSION 3.4)

project(mcdk CXX)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++14)
endif

include_directories(boost)
add_subdirectory(tests)
add_subdirectory(benchmark)
