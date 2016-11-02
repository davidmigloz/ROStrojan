cmake_minimum_required(VERSION 3.6)

project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.c
        )

set(LIB_FILES
        src/shm_mng.c src/shm_mng.h
        src/sem_mng.c src/sem_mng.h)

add_executable(Server ${SOURCE_FILES} ${LIB_FILES})