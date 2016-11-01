cmake_minimum_required(VERSION 3.6)
project(ROStrojan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lib/system_info.h lib/system_info.c lib/file_mng.h lib/file_mng.c lib/env_mng.h lib/env_mng.c)
add_executable(ROStrojan ${SOURCE_FILES})