#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_utils.h"
#include "countingsort.h"
#include "mergesort.h"
#include "qr_sort.h"
#include "quicksort.h"
#include "radixsort.h"

// https://forums.codeguru.com/showthread.php?534679-Generating-big-random-numbers-in-C

double test_mergesort(int *, int *, int);
double test_quicksort(int *, int *, int);
double test_counting_sort(int *, int *, int);
double test_radix_sort(int *, int *, int);
double test_qr_sort(int *, int *, int);


int main() {
    srand(0);

    int num_trials = 50;

    int initial_length   = 50000;
    int max_length       = 1000000;
    int length_increment = 10000;

    int min_number = 0, max_number = 5000000;
    int *arr = NULL;
    int *shadow_arr = NULL;

    double mergesort_time;
    double quicksort_time;
    double counting_sort_time;
    double radix_sort_time;
    double qr_sort_time;

    printf("Array Length, Merge Sort Avg, Quicksort Avg, Counting Sort Avg, Radix Sort Avg, QR Sort Avg\n");

    for(int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        mergesort_time = 0.0;
        quicksort_time = 0.0;
        counting_sort_time = 0.0;
        radix_sort_time = 0.0;
        qr_sort_time = 0.0;

        arr = malloc(arr_length * sizeof (int));
        shadow_arr = malloc(arr_length * sizeof (int));
        lin_space(arr, arr_length, min_number, max_number);
        shuffle(arr, arr_length);

        for (int j = 0; j < num_trials; ++j) {
            mergesort_time += test_mergesort(arr, shadow_arr, arr_length);
            quicksort_time += test_quicksort(arr, shadow_arr, arr_length);
            counting_sort_time += test_counting_sort(arr, shadow_arr, arr_length);
            radix_sort_time += test_radix_sort(arr, shadow_arr, arr_length);
            qr_sort_time += test_qr_sort(arr, shadow_arr, arr_length);
        }

        mergesort_time /= num_trials;
        quicksort_time /= num_trials;
        counting_sort_time /= num_trials;
        radix_sort_time /= num_trials;
        qr_sort_time /= num_trials;

        printf("%d, %f, %f, %f, %f, %f\n", arr_length, mergesort_time, quicksort_time, counting_sort_time, radix_sort_time,
               qr_sort_time);

        free(arr);
        free(shadow_arr);
    }

    return 0;
}

double test_mergesort(int *arr, int *shadow_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, shadow_arr, arr_length);
    merge_sort(shadow_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_quicksort(int *arr, int *shadow_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, shadow_arr, arr_length);
    quicksort(shadow_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_counting_sort(int *arr, int *shadow_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, shadow_arr, arr_length);
    counting_sort(shadow_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_radix_sort(int *arr, int *shadow_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, shadow_arr, arr_length);
    radix_sort(shadow_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_qr_sort(int *arr, int *shadow_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, shadow_arr, arr_length);
    qr_sort_divisor_n(shadow_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}
