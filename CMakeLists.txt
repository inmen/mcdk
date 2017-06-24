cmake_minimum_required(VERSION 3.4)

project(concurrency CXX)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++14)
    add_compile_options(-std=c++14)
endif()

add_subdirectory(tests)
add_subdirectory(benchmark)
