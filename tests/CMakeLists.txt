cmake_minimum_required(VERSION 3.3)
project(mcdk_tests CXX)

set (CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++14)
add_definitions(-std=c++14)

include_directories( .. )
link_directories(../src)

add_executable( util.base64.get_encoder_test.exe util/base64/get_encoder_test.cc)
add_dependencies(util.base64.get_encoder_test.exe mcdk)
target_link_libraries(util.base64.get_encoder_test.exe mcdk)
