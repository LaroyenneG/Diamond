# cmake_minimum_required(VERSION <specify CMake version here>)
project(Algo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    diamond.c
    diamond.h
    game.c
    queue.c
    queue.h
    sublimeterm.c
    sublimeterm.h)

add_executable(Algo ${SOURCE_FILES})