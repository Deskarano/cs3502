cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_MAIN
        driver.cpp

        cpu/types/cpu_types.h
        cpu/types/instr_types.h
        cpu/types/pcb_types.h

        cpu/cpu.cpp
        cpu/cpu.h
        cpu/pcb.cpp
        cpu/pcb.h

        cpu/cpu_control.cpp
        cpu/cpu_control.h

        pcb/pcb_types.h
        pcb/pcb.cpp
        pcb/pcb.h
        pcb/pcb_control.cpp
        pcb/pcb_control.h

        disk/disk.cpp
        disk/disk.h

        scheduler/loader.cpp
        scheduler/short-term.cpp
        scheduler/dispatch.cpp
        scheduler/dispatch.h scheduler/short-term.h
        ram/ram.cpp
        ram/ram.h

        scheduler/short-term.cpp

        utils/base_conversions.h )
add_executable(cs3502 ${SOURCE_FILES_MAIN})