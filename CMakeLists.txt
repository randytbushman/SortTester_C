cmake_minimum_required(VERSION 3.23)
project(sort_tester C)

set(CMAKE_C_STANDARD 99)

add_executable(sort_tester main.c quicksort.c quicksort.h countingsort.h countingsort.c qr_sort.c qr_sort.h radixsort.c radixsort.h mergesort.c mergesort.h)
