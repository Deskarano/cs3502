cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_MAIN
        driver.cpp

        cpu/types/cpu_types.h
        cpu/types/instr_types.h
        cpu/cpu.cpp
        cpu/cpu.h
        cpu/cpu_control.cpp
        cpu/cpu_control.h

        pcb/pcb_types.h
        pcb/pcb.cpp
        pcb/pcb.h
        pcb/pcb_control.cpp
        pcb/pcb_control.h

        disk/disk.cpp
        disk/disk.h

        scheduler/short/shortterm.cpp
        scheduler/short/shortterm.h

        ram/ram.cpp
        ram/ram.h

        utils/base_conversions.h
        utils/queue.cpp
        utils/queue.h

        dispatcher/dispatcher.cpp
        dispatcher/dispatcher.h scheduler/long/longterm.cpp scheduler/long/longterm.h)
add_executable(cs3502 ${SOURCE_FILES_MAIN})