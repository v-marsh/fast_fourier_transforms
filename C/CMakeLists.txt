project(fft_investigation)
cmake_minimum_required(VERSION 3.16.3)

find_package(OpenMP)
find_package(MPI)

add_library(fft_iterative SHARED fft_iterative.c fft_iterative.h)
target_link_libraries(fft_iterative
    m
)

enable_testing()
add_subdirectory(test)