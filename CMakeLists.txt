cmake_minimum_required(VERSION 3.25)
project(travelling_salesman_problem C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fopenmp")
set(CMAKE_C_STANDARD 11)
add_executable(travelling_salesman_problem genetic.c cromossomo.h)
target_compile_options(travelling_salesman_problem PRIVATE -Ofast)
