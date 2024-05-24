cmake_minimum_required(VERSION 3.23)
project(nowclaire C)

set(CMAKE_C_STANDARD 23)

set(SOURCES
    src/main.c)

add_executable(nowclaire ${SOURCES})