cmake_minimum_required(VERSION 3.8)
project(cs3502)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES driver.cpp cpu/cpu.cpp cpu/cpu.h)
add_executable(cs3502 ${SOURCE_FILES})