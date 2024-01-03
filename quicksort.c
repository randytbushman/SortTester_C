/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"

int partition(int[], int, int, unsigned long long int*);
void recursive_quicksort(int[], int, int, unsigned long long int*);

/**
 * Performs Quicksort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int quicksort(int arr[], int arr_length) {
    unsigned long long int instruction_counter = 0; // # of comparisons + array accesses
    recursive_quicksort(arr, 0, arr_length - 1, &instruction_counter);
    return instruction_counter;
}

/**
 * A helper recursive function used to perform Quicksort from the start_idx index to the end_idx index of the given
 * array.
 * @param arr the array to be sorted
 * @param start_idx the start index where Quicksort is performed on arr
 * @param end_idx the end index where Quicksort is performed on arr
 */
void recursive_quicksort(int arr[], int start_idx, int end_idx, unsigned long long int* instruction_counter) {
    if (++instruction_counter && end_idx - start_idx < 1)
        return;
    int p = partition(arr, start_idx, end_idx, instruction_counter);
    recursive_quicksort(arr, start_idx, p - 1, instruction_counter);
    recursive_quicksort(arr, p+1, end_idx, instruction_counter);
}

/**
 * Partitions the element at end_idx in the given array.
 * @param arr the array to be partitioned
 * @param start_idx the start index where the partitioning is performed on arr
 * @param end_idx the end index where the partitioning is performed on arr
 * @return the new index of the partitioned array value
 */
int partition(int arr[], int start_idx, int end_idx, unsigned long long int* instruction_counter) {
    int x = arr[end_idx];
    ++instruction_counter;
    int i = start_idx - 1;
    for (int j = start_idx; ++instruction_counter && j < end_idx; ++j)
        if ((instruction_counter += 2) && arr[j] < x)
            swap(arr, ++i, j);

    swap(arr, i + 1, end_idx);
    return i + 1;
}

/**
 * Swaps the value at index i with the value at index j in the given array.
 * @param arr the array where swapping takes place
 * @param i the index of the first value to swap
 * @param j the index of the second value to swap
 */
void swap(int arr[], int i, int j, unsigned long long int* instruction_counter) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    instruction_counter += 4;
}