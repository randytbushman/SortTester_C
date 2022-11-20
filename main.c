#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_utils.h"
#include "countingsort.h"
#include "mergesort.h"
#include "qr_sort.h"
#include "quicksort.h"
#include "radixsort.h"

#define MAX_ALGORITHM_COUNT 24

double test_mergesort(int *, int *, int);
double test_quicksort(int *, int *, int);
double test_counting_sort(int *, int *, int);
double test_radix_sort(int *, int *, int);
double test_qr_sort(int *, int *, int);
//double test_qr_sort_min_value_zero(int *, int *, int);
//double test_qr_sort_power_2(int *, int *, int);
//double test_qr_sort_power_2_min_value_zero(int *, int *, int);
void add_sort_method(char[], double (*)(int*, int*, int));


double (*sorting_testers[MAX_ALGORITHM_COUNT])(int *, int *, int);   // Create array of test methods for each algorithm
double algorithm_times[MAX_ALGORITHM_COUNT] = {0};  // Initialize each measured time to zero
char csv_column_str[1024] = "Array Length";         // The csv column string. Appended each time an algorithm is added
int algorithm_count = 0;                            // The number of algorithms to be tested. Incremented each time an algorithm is added

int main() {
    srand(0);

    // START - ARGUMENTS THAT USER-TESTER CAN CHANGE

    int num_trials = 30;            // The number of trials per array length

    int initial_length   = 1000;         // The initial (smallest) array size to be tested
    int max_length       = 10000000;    // The maximum array size to be tested
    int length_increment = 1000;         // After the trial sessions are complete, increment the next array size by this value

    int min_number = 0, max_number = 50000000;   // The minimum and maximum values in the arrays

    // Add new test method for each sorting algorithm
    //add_sort_method("Merge Sort", test_mergesort);
    //add_sort_method("Quicksort", test_quicksort);
    //add_sort_method("Counting Sort", test_counting_sort);
    add_sort_method("Radix Sort", test_radix_sort);
    add_sort_method("QR Sort", test_qr_sort);

    // Go to test methods to specific power and divisor values
    //add_sort_method("QR Sort Min Value Zero", test_qr_sort_min_value_zero);
    //add_sort_method("QR Sort Power 2", test_qr_sort_power_2);
    //add_sort_method("QR Sort Power 2 Min Value Zero", test_qr_sort_power_2_min_value_zero);


    // END - ARGUMENTS THAT USER-TESTER CAN CHANGE

    printf("%s\n", csv_column_str);     // Prints the column headers to std_output

    int i, j;
    int *arr = NULL;        // The array of ints to be copied
    int *copy_arr = NULL;   // This array references (copies) the int values in arr at each new trial
    for(int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        arr = malloc(arr_length * sizeof (int));
        copy_arr = malloc(arr_length * sizeof (int));
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

        // Memory is freed; size is increased and reallocated at next arr_length iteration
        free(arr);
        free(copy_arr);
    }
    return 0;
}

void add_sort_method(char algorithm_name[], double (*sort_method)(int*, int*, int)) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, algorithm_name);
    sorting_testers[algorithm_count++] = sort_method;
}

double test_mergesort(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    merge_sort(copy_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_quicksort(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    quicksort(copy_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_counting_sort(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    counting_sort(copy_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_radix_sort(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    radix_sort(copy_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_qr_sort(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    qr_sort_divisor_n(copy_arr, arr_length);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_qr_sort_min_value_zero(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    qr_sort_min_value_zero(copy_arr, arr_length, arr_length);  // Specify divisor here
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_qr_sort_power_2(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    qr_sort_power_2(copy_arr, arr_length, 2);       // Specify Power here
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

double test_qr_sort_power_2_min_value_zero(int *arr, int *copy_arr, int arr_length) {
    clock_t begin = clock();
    clone_array(arr, copy_arr, arr_length);
    qr_sort_power_2_min_value_zero(copy_arr, arr_length, 2);
    return (double) (clock() - begin) / CLOCKS_PER_SEC;
}

