cmake_minimum_required(VERSION 3.6)
project(ROStrojan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c system_info.h file_mng.h)
add_executable(ROStrojan ${SOURCE_FILES})