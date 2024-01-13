cmake_minimum_required(VERSION 3.23)
project(sort_tester C)

set(CMAKE_C_STANDARD 99)

add_executable(sort_tester main.c algorithms/quicksort.c algorithms/countingsort.c algorithms/qr_sort.c algorithms/radixsort.c algorithms/mergesort.c sort_utils.c sort.h)
