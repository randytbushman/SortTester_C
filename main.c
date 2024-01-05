/**
 * @author: Randolph Bushman
 * @date: 01/04/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"
#include "sort.h"
#define MAX_ALGORITHM_COUNT 24      // Increase value if more than 24 algorithms to test

typedef struct {
    int radix;  // Used in Radix Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length.
    int divisor;  // Used in QR Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length
    int min_value_zero;  // Flag indicating if the minimum value in the array is zero, optimizing Radix Sort and QR Sort.
    int use_bitwise_ops;  // Flag indicating if bitwise operations should be used, optimizing Radix Sort and QR Sort.
} SortArgs;

typedef double (*SortFunc)(int copy_arr[], int arr_length, SortArgs args);

// Create global variables accessible anywhere in main.c
SortFunc sorting_testers[MAX_ALGORITHM_COUNT];   // Create array of test methods for each algorithm
SortArgs sorting_args[MAX_ALGORITHM_COUNT];  //
double algorithm_times[MAX_ALGORITHM_COUNT] = {0};  // Initialize each measured time to zero
char csv_column_str[1024] = "Array Length";         // The csv column string. Appended each time an algorithm is added. Buffer overflows are not checked.
int algorithm_count = 0;  // The number of algorithms to be tested. Incremented each time an algorithm is added

/**
 * A wrapper SortFunc for Merge Sort, returning the number of executed instructions.
 * @param arr the array to sort.
 * @param arr_length the length of the array to sort
 * @param args boilerplate arguments not used by Merge Sort
 * @return the number of instructions executed by Merge Sort
 */
double test_mergesort(int arr[], int arr_length, SortArgs args) {
    return (double) merge_sort(arr, arr_length);
}

/**
 * A wrapper SortFunc for Quicksort, returning the number of executed instructions.
 * @param arr the array to sort.
 * @param arr_length the length of the array to sort
 * @param args boilerplate arguments not used by Quicksort
 * @return the number of instructions executed by Quicksort
 */
double test_quicksort(int arr[], int arr_length, SortArgs args) {
    return (double) quicksort(arr, arr_length);
}

/**
 * A wrapper SortFunc for Counting Sort, returning the number of executed instructions.
 * @param arr the array to sort.
 * @param arr_length the length of the array to sort
 * @param args arguments utilized by Counting Sort to optimize performance which include: min_value_zero
 * @return the number of instructions executed by Counting Sort
 */
double test_counting_sort(int arr[], int arr_length, SortArgs args) {
    return (double) counting_sort(arr, arr_length, args.min_value_zero);
}

/**
 * A wrapper SortFunc for Radix Sort, returning the number of executed instructions.
 * @param arr the array to sort.
 * @param arr_length the length of the array to sort
 * @param args arguments utilized by Radix Sort to optimize performance which include: radix, min_value_zero, and use_bitwise_ops
 * @return the number of instructions executed by Radix Sort
 */
double test_radix_sort(int arr[], int arr_length, SortArgs args) {
    return (double) radix_sort(arr, arr_length, args.radix, args.min_value_zero, args.use_bitwise_ops);
}

/**
 * A wrapper SortFunc for QR Sort, returning the number of executed instructions.
 * @param arr the array to sort
 * @param arr_length the length of the array to sort
 * @param args arguments utilized by QR Sort to optimize performance which include: divisor, min_value_zero, and use_bitwise_ops
 * @return the number of instructions executed by QR Sort
 */
double test_qr_sort(int arr[], int arr_length, SortArgs args) {
    return (double) qr_sort(arr, arr_length, args.divisor, args.min_value_zero, args.use_bitwise_ops);
}

/**
 * Adds a sorting algorithm to be tested.
 * @param name the string name of the sorting algorithm
 * @param func the SortFunc (sorting algorithm function) to invoke the sorting algorithm
 * @param args the arguments that algorithm takes in
 */
void add_sorting_method(const char* name, SortFunc func, SortArgs args) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, name);
    sorting_args[algorithm_count] = args;
    sorting_testers[algorithm_count++] = func;
}


int main() {
    srand(0);

    // Trial parameters
    int num_trials = 30;  // The number of trials per array length
    int initial_length   = 1000;  // The initial (smallest) array size to be tested
    int length_increment = 1000;  // After the trial sessions are complete, increment the next array size by this value
    int max_length       = 10000;  // The maximum array size to be tested
    int min_arr_value = 0, max_arr_value = 5009679;  // The minimum and maximum values in the arrays

    // Define arguments for each sorting algorithm
    SortArgs default_sort_args = {0};
    SortArgs counting_sort_args = {.min_value_zero = 0};
    SortArgs radix_sort_args = {.use_bitwise_ops = 0, .min_value_zero = 0, .radix = 0};
    SortArgs qr_sort_args = {.use_bitwise_ops = 0, .min_value_zero = 0, .divisor = 0};

    // QR Sort optimizations
    int divisor = 16;
    SortArgs qr_sort_set_divisor_args = {.divisor = divisor, .use_bitwise_ops = 1, .min_value_zero = 1};
    SortArgs qr_sort_min_value_zero_args = {.divisor = divisor, .use_bitwise_ops = 1, .min_value_zero = 1};
    SortArgs qr_sort_bitwise_args = {.divisor = divisor, .use_bitwise_ops = 1, .min_value_zero = 1};
    SortArgs qr_sort_bitwise_min_value_zero_args = {.divisor = divisor, .use_bitwise_ops = 1, .min_value_zero = 1};

    // Add new test method for each sorting algorithm
    add_sorting_method("Merge Sort", test_mergesort, default_sort_args);
    add_sorting_method("Quicksort", test_quicksort, default_sort_args);
    add_sorting_method("Counting Sort", test_counting_sort, counting_sort_args);
    add_sorting_method("Radix Sort", test_radix_sort, radix_sort_args);
    add_sorting_method("QR Sort", test_qr_sort, qr_sort_args);
    /*
    add_sorting_method("QR Sort Set Divisor", test_qr_sort, qr_sort_set_divisor_args);
    add_sorting_method("QR Sort Min Value Zero", test_qr_sort, qr_sort_min_value_zero_args);
    add_sorting_method("QR Sort Power 2", test_qr_sort, qr_sort_bitwise_args);
    add_sorting_method("QR Sort Power 2 Min Value Zero", test_qr_sort, qr_sort_bitwise_min_value_zero_args);
    */

    // Print csv column headers
    printf("sep=,\n");
    printf("%s\n", csv_column_str);

    // Run Sorting Evaluator
    int *arr = malloc(max_length * sizeof (int));  // The int array to reference for sorting
    int *copy_arr = malloc(max_length * sizeof (int));  // The int array that copies arr, then gets sorted
    for(int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        lin_space(arr, arr_length, min_arr_value, max_arr_value);  // Populate arr with linearly spaced values between min_arr_value and max_arr_value

        // Each algorithm sorts the same array sequence on each trial; after each trial, the array is shuffled
        for (int i = 0; i < num_trials; ++i) {
            shuffle(arr, arr_length);  // Array is shuffled for each trial
            for (int j = 0; j < algorithm_count; ++j) {
                clone_array(arr, copy_arr, arr_length);
                algorithm_times[j] += (*sorting_testers[j])(copy_arr, arr_length, sorting_args[j]);
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
