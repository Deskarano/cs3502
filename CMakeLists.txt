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
        pcb/pcb_node.h
        pcb/pcb.cpp
        pcb/pcb.h

        disk/disk.cpp
        disk/disk.h

        ram/ram.cpp
        ram/ram.h

        scheduler/short/shortterm.cpp
        scheduler/short/shortterm.h
        scheduler/long/longterm.cpp
        scheduler/long/longterm.h

        utils/base_conversions.h
        utils/queue.cpp
        utils/queue.h
        utils/memcpy.cpp
        utils/memcpy.h

        log/log_status.cpp
        log/log_status.h
        log/log_error.cpp
        log/log_error.h)
add_executable(cs3502 ${SOURCE_FILES_MAIN})