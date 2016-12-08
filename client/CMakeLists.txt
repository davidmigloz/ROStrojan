cmake_minimum_required(VERSION 3.6)

project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.c
        src/main_process.c
        src/main_process.h
        src/sender_process.c
        src/sender_process.h)

set(LIB_FILES
        ../lib/file_mng.c
        ../lib/file_mng.h
        ../lib/system_info.c
        ../lib/system_info.h
        ../lib/env_mng.c
        ../lib/env_mng.h
        ../lib/sig_mng.c
        ../lib/sig_mng.h
        )

add_executable(Client ${SOURCE_FILES} ${LIB_FILES})
