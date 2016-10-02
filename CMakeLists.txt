cmake_minimum_required(VERSION 3.6)
project(ROStrojan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.c src/system_info.h src/system_info.c src/file_mng.h src/file_mng.c)
add_executable(ROStrojan ${SOURCE_FILES})