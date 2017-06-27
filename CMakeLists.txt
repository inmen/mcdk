cmake_minimum_required(VERSION 3.3)

project(mcdk CXX)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-std=c++14)

include_directories(.)
include_directories( ../../source_code/boost_1_64_0 )

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmark)
