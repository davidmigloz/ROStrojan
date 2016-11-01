cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.c src/shm_mng.c src/shm_mng.h)
add_executable(server ${SOURCE_FILES})