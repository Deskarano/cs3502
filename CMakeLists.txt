cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lpthread")

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

        pcb/page_table/page_table.cpp
        pcb/page_table/page_table.h
        pcb/page_table/page_table_entry.cpp
        pcb/page_table/page_table_entry.h

        storage/disk/disk.cpp
        storage/disk/disk.h
        storage/ram/ram.cpp
        storage/ram/ram.h

        storage/page_frame.h
        storage/page_manager.cpp
        storage/page_manager.h

        sched/short/shortterm.cpp
        sched/short/shortterm.h
        sched/long/longterm.cpp
        sched/long/longterm.h
        sched/sched_control.cpp
        sched/sched_control.h
        sched/sched_types.h

        utils/base_conversions.h
        utils/memcpy.cpp
        utils/memcpy.h
        utils/lock.cpp
        utils/lock.h

        log/log_status.cpp
        log/log_status.h
        log/log_error.cpp
        log/log_error.h )

add_executable(cs3502 ${SOURCE_FILES_MAIN})
