cmake_minimum_required(VERSION 3.6)

project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.c
        src/shm_mng.c
        src/shm_mng.h
        )

set(LIB_FILES

        )

add_executable(Server ${SOURCE_FILES} ${LIB_FILES})