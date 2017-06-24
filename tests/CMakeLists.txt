cmake_minimum_required(VERSION 3.3)
project(mcdk_tests CXX)

set (CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++14)
add_definitions(-std=c++14)
include_directories( .. )

add_executable( util.base64.get_encoder_test.exe util/base64/get_encoder_test.cc)