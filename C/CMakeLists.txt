project(fft_investigation)
cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_STANDARD_REQUIRED C11)

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
    ${SRC}/fft_iterative.h)
target_link_libraries(fft_iterative
    m
    tools)

add_library(fft_threaded
    ${SRC}/fft_threaded.c
    ${SRC}/fft_threaded.h
    ${SRC}/tools.h)
target_link_libraries(fft_threaded
    m
    tools
    OpenMP::OpenMP_C)

    enable_testing()
add_subdirectory(test)