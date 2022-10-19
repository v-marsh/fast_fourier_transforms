project(fft_investigation)
cmake_minimum_required(VERSION 3.16.3)

find_package(OpenMP)
find_package(MPI)

add_executable(fft_iterative fft_iterative.c fft_iterative.h)
