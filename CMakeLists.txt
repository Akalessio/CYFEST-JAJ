cmake_minimum_required(VERSION 3.26)
project(CYFEST C)

set(CMAKE_C_STANDARD 11)

include_directories(include/)

add_executable(CYFEST main.c
        salle.c
        include/salle.h
        fonx.c
        include/fonx.h)
