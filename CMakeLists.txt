cmake_minimum_required(VERSION 3.8)
project(Diamond)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/diamond.c
        src/diamond.h
        src/game.c
        lib/queue.c
        lib/queue.h
        lib/sublimeterm.c
        lib/sublimeterm.h)

add_executable(Diamond ${SOURCE_FILES})