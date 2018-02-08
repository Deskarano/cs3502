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

set(SOURCE_FILES_CPU_TEST
        cpu/test/cpu_test_main.cpp
        cpu/test/cpu_test_ram.cpp
        cpu/test/cpu_test_ram.h

        cpu/test/programfile

        cpu/cpu.cpp
        cpu/cpu.h
        cpu/pcb.cpp
        cpu/pcb.h)
add_executable(cs3502_cpu_test ${SOURCE_FILES_CPU_TEST})