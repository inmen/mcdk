cmake_minimum_required(VERSION 3.3)

project(mcdk CXX)

set (CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++14)
add_definitions(-std=c++14)

include_directories(boost)
include_directories(.)
add_subdirectory(tests)
add_subdirectory(benchmark)
