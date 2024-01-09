cmake_minimum_required(VERSION 3.23)
project(sort_tester C)

set(CMAKE_C_STANDARD 99)

add_executable(sort_tester main.c quicksort.c countingsort.c qr_sort.c radixsort.c mergesort.c sort_utils.c sort.h)
