cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES driver.cpp cpu/cpu.cpp cpu/cpu.h ram/ram.cpp ram/ram.h disk/disk.cpp disk/disk.h justtrying/whatever.cpp justtrying/whatever.h)
add_executable(cs3502 ${SOURCE_FILES})