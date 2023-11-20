cmake_minimum_required(VERSION 3.26.4)
project(MATAM2 C)

set(CMAKE_C_STANDARD 99)



add_executable(MATAM2 RLEList.c
        RLEList.h
        AsciiArtTool.h
        AsciiArtTool.c
        main.c)
