cmake_minimum_required(VERSION 3.3)

project(mcdk CXX)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++14)
endif()

if (CMAKE_COMPILER_IS_MSVC)
    add_definitions( /std:c++14 )
endif()

include_directories(.)
include_directories( ../boost )

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmark)
