/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_utils.h"
#include "sort.h"
#define MAX_ALGORITHM_COUNT 24      // Increase value if more than 24 algorithms to test

// Prototype helper functions
double test_mergesort(int[], int[], int);
double test_quicksort(int[], int[], int);
double test_counting_sort(int[], int[], int);
double test_radix_sort(int[], int[], int);
double test_qr_sort(int[], int[], int);
double test_qr_sort_d(int[], int[], int);
double test_qr_sort_min_value_zero(int[], int[], int);
double test_qr_sort_power_2(int[], int[], int);
double test_qr_sort_power_2_min_value_zero(int[], int[], int);
void add_sort_method(char*, double (*)(int[], int[], int));


// Create global variables accessible anywhere in main.c
double (*sorting_testers[MAX_ALGORITHM_COUNT])(int[], int[], int);   // Create array of test methods for each algorithm
double algorithm_times[MAX_ALGORITHM_COUNT] = {0};  // Initialize each measured time to zero
char csv_column_str[1024] = "Array Length";         // The csv column string. Appended each time an algorithm is added. Buffer overflows are not checked.
int algorithm_count = 0;                            // The number of algorithms to be tested. Incremented each time an algorithm is added


int main() {
    srand(0);

    // START - ARGUMENTS THAT USER-TESTER CAN CHANGE

    int num_trials = 30;            // The number of trials per array length

    int initial_length   = 10000;         // The initial (smallest) array size to be tested
    int length_increment = 10000;         // After the trial sessions are complete, increment the next array size by this value
    int max_length       = 1000000;    // The maximum array size to be tested

    int min_number = 0, max_number = 500000;   // The minimum and maximum values in the arrays

    // Add new test method for each sorting algorithm
    add_sort_method("Merge Sort", test_mergesort);
    add_sort_method("Quicksort", test_quicksort);
    add_sort_method("Counting Sort", test_counting_sort);
    add_sort_method("Radix Sort", test_radix_sort);
    add_sort_method("QR Sort", test_qr_sort);

    // Go to test methods to specific power and divisor values
    /*
    add_sort_method("QR Sort Set Divisor", test_qr_sort_d);
    add_sort_method("QR Sort Min Value Zero", test_qr_sort_min_value_zero);
    add_sort_method("QR Sort Power 2", test_qr_sort_power_2);
    add_sort_method("QR Sort Power 2 Min Value Zero", test_qr_sort_power_2_min_value_zero);
     */


    // END - ARGUMENTS THAT USER-TESTER CAN CHANGE

    printf("sep=,\n");     // Prints the column headers to std_output
    printf("%s\n", csv_column_str);     // Prints the column headers to std_output

    int i, j;
    int *arr = malloc(max_length * sizeof (int));        // The array of ints to be copied
    int *copy_arr = malloc(max_length * sizeof (int));   // This array references (copies) the int values in arr at each new trial
    for(int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        lin_space(arr, arr_length, min_number, max_number);     // Populate arr with linearly spaced values between min_number and max_number

        // Each algorithm sorts the same array sequence on each trial; after each trial, the array is shuffled
        for (i = 0; i < num_trials; ++i) {
            shuffle(arr, arr_length);   // Array is shuffled for each trial
            for (j = 0; j < algorithm_count; ++j)
                algorithm_times[j] += (*sorting_testers[j])(arr, copy_arr, arr_length);
        }

        // Print the average time for each algorithm trial
        printf("%d", arr_length);
        for (i = 0; i < algorithm_count; ++i) {
            printf(", %f", 1000 * algorithm_times[i] / num_trials);
            algorithm_times[i] = 0.0;   // Reset algorithm time after print
        }
        printf("\n");
    }

    free(arr);
    free(copy_arr);
    return 0;
}

/**
 * Adds a sorting algorithm and algorithm name to the tester.
 * @param algorithm_name the algorithm name to be displayed in the output
 * @param sort_function a pointer to the sorting algorithm test function where the first arguments represents the
 * original array, the second represents an array to store and copy the contents of the original array, and the third
 * represents the array length
 */
void add_sort_method(char *algorithm_name, double (*sort_function)(int[], int[], int)) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, algorithm_name);
    sorting_testers[algorithm_count++] = sort_function;
}


// Boilerplate test functions. Each returns the amount of time in milliseconds taken to sort with the respective algorithm.

double test_mergesort(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) merge_sort(copy_arr, arr_length);
}

double test_quicksort(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) quicksort(copy_arr, arr_length);
}

double test_counting_sort(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) counting_sort(copy_arr, arr_length);
}

double test_radix_sort(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return radix_sort(copy_arr, arr_length);
}

double test_qr_sort(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort_divisor_n(copy_arr, arr_length);
}

double test_qr_sort_d(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort(copy_arr, arr_length, 1 << 16);
}

double test_qr_sort_min_value_zero(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort_min_value_zero(copy_arr, arr_length, 1 << 16);
}

double test_qr_sort_power_2(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort_power_2(copy_arr, arr_length, 16);
}

double test_qr_sort_power_2_min_value_zero(int arr[], int copy_arr[], int arr_length) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort_power_2_min_value_zero(copy_arr, arr_length, 16);
}
