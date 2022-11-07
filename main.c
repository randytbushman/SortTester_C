#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "countingsort.h"
#include "mergesort.h"
#include "qr_sort.h"
#include "quicksort.h"
#include "radixsort.h"

// https://forums.codeguru.com/showthread.php?534679-Generating-big-random-numbers-in-C

void print_int_array(int *, int);

int main() {
    srand(0);
    int n = 100000;
    int *random_arr = malloc(n * sizeof (int));
    int min_number = 0, max_number = 1000000000;
    int i;

    int random_number;
    for (i = 0; i < n; ++i) {
        random_number = ((((rand() & 255)<<8 | (rand() & 255))<<8 | (rand() & 255))<<7 | (rand() & 127)) % (max_number + 1 - min_number) + min_number;
        random_arr[i] = random_number;
    }

    clock_t begin = clock();
    radix_sort(random_arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // print_int_array(random_arr, n);

    printf("Time spent: %f", time_spent);

    return 0;
}

void print_int_array(int *arr, int n) {
    printf("[%d", arr[0]);
    for (int i = 1; i < n; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
}