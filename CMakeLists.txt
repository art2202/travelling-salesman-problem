cmake_minimum_required(VERSION 3.25)
project(travelling_salesman_problem C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(travelling_salesman_problem genetic.c cromossomo.h)

target_link_libraries(travelling_salesman_problem PRIVATE MPI::MPI_C)

#target_compile_options(travelling_salesman_problem PRIVATE -O3)
