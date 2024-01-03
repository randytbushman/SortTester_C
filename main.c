/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"
#include "sort.h"
#define MAX_ALGORITHM_COUNT 24      // Increase value if more than 24 algorithms to test

typedef struct {
    int radix;           // Used in Radix Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length.
    int divisor;         // Used in QR Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length
    int min_value_zero;  // Flag indicating if the minimum value in the array is zero, optimizing QR Sort.
    int use_bitwise_ops; // Flag indicating if bitwise operations should be used, optimizing QR Sort.
} SortArgs;

typedef double (*SortFunc)(int arr[], int copy_arr[], int arr_length, SortArgs args);

// Prototype helper functions
double test_mergesort(int[], int[], int, SortArgs);
double test_quicksort(int[], int[], int, SortArgs);
double test_counting_sort(int[], int[], int, SortArgs);
double test_radix_sort(int[], int[], int, SortArgs);
double test_qr_sort(int[], int[], int, SortArgs);

// Create global variables accessible anywhere in main.c
SortFunc sorting_testers[MAX_ALGORITHM_COUNT];   // Create array of test methods for each algorithm
SortArgs sorting_args[MAX_ALGORITHM_COUNT];  //
double algorithm_times[MAX_ALGORITHM_COUNT] = {0};  // Initialize each measured time to zero
char csv_column_str[1024] = "Array Length";         // The csv column string. Appended each time an algorithm is added. Buffer overflows are not checked.
int algorithm_count = 0;  // The number of algorithms to be tested. Incremented each time an algorithm is added

/**
 * TODO - Add OOB checks
 * Adds a sorting algorithm and algorithm name to the tester.
 * @param name the name of the sorting algorithm
 * @param func the function to call on to execute the sorting algorithm
 * @param args the arguments that algorithm takes in
 */
void add_sorting_method(const char* name, SortFunc func, SortArgs args) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, name);
    sorting_args[algorithm_count] = args;
    sorting_testers[algorithm_count++] = func;
}


int main() {
    srand(0);

    int num_trials = 30;            // The number of trials per array length
    int initial_length   = 10;         // The initial (smallest) array size to be tested
    int length_increment = 10;         // After the trial sessions are complete, increment the next array size by this value
    int max_length       = 100000;    // The maximum array size to be tested
    int min_arr_value = 0, max_arr_value = 5009679;   // The minimum and maximum values in the arrays

    // Define arguments for each sorting algorithm
    SortArgs default_sort_args = {0};
    SortArgs counting_sort_args = {.min_value_zero = 0};
    SortArgs radix_sort_args = {.radix = 16, .use_bitwise_ops = 1, .min_value_zero = 1};
    SortArgs qr_sort_args = {.divisor = 16, .use_bitwise_ops = 1, .min_value_zero = 1};

    // Add new test method for each sorting algorithm
    add_sorting_method("Merge Sort", test_mergesort, default_sort_args);
    add_sorting_method("Quicksort", test_quicksort, default_sort_args);
    add_sorting_method("Counting Sort", test_counting_sort, counting_sort_args);
    add_sorting_method("Radix Sort", test_radix_sort, radix_sort_args);
    add_sorting_method("QR Sort", test_qr_sort, qr_sort_args);

    // END - ARGUMENTS THAT USER-TESTER CAN CHANGE
    printf("sep=,\n");     // Prints the column headers to std_output
    printf("%s\n", csv_column_str);     // Prints the column headers to std_output

    int arr_length, i, j;
    int *arr = malloc(max_length * sizeof (int));        // The array of ints to be copied
    int *copy_arr = malloc(max_length * sizeof (int));   // This array references (copies) the int values in arr at each new trial
    for(arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        lin_space(arr, arr_length, min_arr_value, max_arr_value);     // Populate arr with linearly spaced values between min_arr_value and max_arr_value

        // Each algorithm sorts the same array sequence on each trial; after each trial, the array is shuffled
        for (i = 0; i < num_trials; ++i) {
            shuffle(arr, arr_length);   // Array is shuffled for each trial
            for (j = 0; j < algorithm_count; ++j) {
                algorithm_times[j] += (*sorting_testers[j])(arr, copy_arr, arr_length, sorting_args[j]);
                if (! is_sorted_ascending(copy_arr, arr_length))
                    return -1;
            }
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

double test_mergesort(int arr[], int copy_arr[], int arr_length, SortArgs args) {
    clone_array(arr, copy_arr, arr_length);
    return (double) merge_sort(copy_arr, arr_length);
}

double test_quicksort(int arr[], int copy_arr[], int arr_length, SortArgs args) {
    clone_array(arr, copy_arr, arr_length);
    return (double) quicksort(copy_arr, arr_length);
}

double test_counting_sort(int arr[], int copy_arr[], int arr_length, SortArgs args) {
    clone_array(arr, copy_arr, arr_length);
    return (double) counting_sort(copy_arr, arr_length, args.min_value_zero);
}

double test_radix_sort(int arr[], int copy_arr[], int arr_length, SortArgs args) {
    clone_array(arr, copy_arr, arr_length);
    return (double) radix_sort(copy_arr, arr_length, args.radix, args.min_value_zero, args.use_bitwise_ops);
}

double test_qr_sort(int arr[], int copy_arr[], int arr_length, SortArgs args) {
    clone_array(arr, copy_arr, arr_length);
    return (double) qr_sort(copy_arr, arr_length, args.divisor, args.min_value_zero, args.use_bitwise_ops);
}
