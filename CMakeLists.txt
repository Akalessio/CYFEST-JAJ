cmake_minimum_required(VERSION 3.26)
project(CYFEST C)

set(CMAKE_C_STANDARD 11)

add_executable(CYFEST include/main.c
        include/salle.c
        include/salle.h
        include/fonx.c
        include/fonx.h)
