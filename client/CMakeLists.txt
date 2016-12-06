cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.c src/main_process.c src/main_process.h src/sender_process.c src/sender_process.h)
add_executable(client ${SOURCE_FILES})