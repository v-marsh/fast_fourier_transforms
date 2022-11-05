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

add_library(fft_threaded SHARED
    ${SRC}/fft_threaded.c
    ${SRC}/fft_threaded.h
    ${SRC}/tools.h)
target_link_libraries(fft_threaded
    m
    tools
    OpenMP::OpenMP_C)

add_library(avxtools SHARED
    ${SRC}/avxtools.c
    ${SRC}/avxtools.h)
target_compile_options(avxtools PRIVATE "-mavx2")

add_library(mpi_tools SHARED
    ${SRC}/mpi_tools.c
    ${SRC}/mpi_tools.h)
target_link_libraries(mpi_tools
    MPI::MPI_C
)

add_library(fft_distributed
    ${SRC}/fft_distributed.c
    ${SRC}/fft_distributed.h
    ${SRC}/mpi_tools.h)
target_link_libraries(fft_distributed
    MPI::MPI_C
    fft_iterative
    mpi_tools)

    enable_testing()
add_subdirectory(test)