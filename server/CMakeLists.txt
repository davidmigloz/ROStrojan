cmake_minimum_required(VERSION 3.6)

project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.c
        src/main_process.c
        src/main_process.h
        src/listener_process.c
        src/listener_process.h)

set(LIB_FILES
        src/shm_mng.c src/shm_mng.h
        src/sem_mng.c src/sem_mng.h src/shm_utils.c src/shm_utils.h)

add_executable(Server ${SOURCE_FILES} ${LIB_FILES})