project(fft_investigation)
cmake_minimum_required(VERSION 3.16.3)

set(SRC src)

find_package(OpenMP)
find_package(MPI)

add_library(tools SHARED 
    ${SRC}/tools.c
    ${SRC}/tools.h)
target_link_libraries(tools
    m)

add_library(fft_iterative SHARED 
    ${SRC}/fft_iterative.c
    ${SRC}/fft_iterative.h
    ${SRC}/tools.h)
target_link_libraries(fft_iterative
    m
    tools)

enable_testing()
add_subdirectory(test)