/**
 * @author: Randolph Bushman
 * @date: 01/04/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "sort_utils.h"
#include "sort.h"
#define MAX_ALGORITHM_COUNT 24      // Increase value if more than 24 algorithms to test

// Create global variables accessible anywhere in main.c
SortFunc sorting_algorithms[MAX_ALGORITHM_COUNT];   // Make array of test functions for each algorithm
SortArgs sorting_args[MAX_ALGORITHM_COUNT];  // Make array of arguments to pass into each algorithm
double algorithm_times[MAX_ALGORITHM_COUNT] = {0};  // Initialize each measured time to zero
char csv_column_str[1024] = "Array Length";  // The csv column (header) string; appended each time an algorithm is added
int algorithm_count = 0;  // The current number of algorithms to be tested; incremented each time an algorithm is added

/**
 * Adds a sorting algorithm to be tested.
 * @param name the string name of the sorting algorithm
 * @param func the SortFunc (sorting algorithm function) to invoke the sorting algorithm
 * @param args the arguments that algorithm takes in
 */
void add_sorting_method(const char* name, SortFunc func, SortArgs args) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, name);
    sorting_args[algorithm_count] = args;
    sorting_algorithms[algorithm_count++] = func;
}

int main() {
    srand(0);

    // Trial parameters
    int num_trials = 1;  // The number of trials per array length
    int initial_length = 10000;  // The initial (smallest) array size to be tested
    int length_increment = 10000;  // After the trial sessions are complete, increment the next array size by this value
    int max_length = 1000000;  // The maximum array size to be tested
    int min_arr_value = 0, max_arr_value = 5009679;  // The minimum and maximum values in the arrays

    // Add new sorting algorithms
    add_sorting_method("Merge Sort", merge_sort, (SortArgs) {});
    add_sorting_method("Quicksort", quicksort, (SortArgs) {});
    add_sorting_method("Counting Sort", counting_sort, (SortArgs) {});
    add_sorting_method("Radix Sort", radix_sort, (SortArgs) {});
    add_sorting_method("QR Sort", qr_sort, (SortArgs) {});

    // QR Sort optimization algorithms
    int divisor = 16;  // Common divisor to test in QR Sort optimizations (ensure is power of 2)
    add_sorting_method("QR Sort Set Divisor", qr_sort, (SortArgs) {.divisor = divisor});
    add_sorting_method("QR Sort Min Value Zero", qr_sort, (SortArgs) {.divisor = divisor, .min_value_zero = 1});
    add_sorting_method("QR Sort Power 2", qr_sort, (SortArgs) {.divisor = divisor, .bitwise_ops = 1});
    add_sorting_method("QR Sort Power 2 Min Value Zero", qr_sort, (SortArgs) {.divisor = divisor, .bitwise_ops = 1, .min_value_zero = 1});

    // Print csv column headers
    printf("sep=,\n");
    printf("%s\n", csv_column_str);

    // Allocate arrays and run sorting tester
    int *arr = malloc(max_length * sizeof (int));  // The array to sort
    int *copy_arr = malloc(max_length * sizeof (int));  // A copy of the array to sort
    for(int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        // Populate arr with linearly spaced values between min_arr_value and max_arr_value
        lin_space(arr, arr_length, min_arr_value, max_arr_value);

        // Each algorithm sorts the same array sequence on each trial; after each trial, the array is shuffled
        for (int i = 0; i < num_trials; ++i) {
            shuffle(arr, arr_length);  // Array is shuffled for each trial
            for (int j = 0; j < algorithm_count; ++j) {
                clone_array(arr, copy_arr, arr_length);
                algorithm_times[j] += (*sorting_algorithms[j])(copy_arr, arr_length, sorting_args[j]);
            }
        }

        // Print the average time for each algorithm trial in csv format
        printf("%d", arr_length);
        for (int i = 0; i < algorithm_count; ++i) {
            printf(", %f", 1000 * algorithm_times[i] / num_trials);
            algorithm_times[i] = 0.0;  // Reset algorithm time after print
        }
        printf("\n");
    }

    free(arr);
    free(copy_arr);
    return 0;
}
