cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_MAIN
        driver.cpp

        cpu/cpu.cpp
        cpu/cpu.h
        cpu/pcb.cpp
        cpu/pcb.h

        ram/ram.cpp
        ram/ram.h

        disk/disk.cpp
        disk/disk.h

        scheduler/short-term.cpp)
add_executable(cs3502 ${SOURCE_FILES_MAIN})