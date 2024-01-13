/**
 * @author: Randolph Bushman
 * @date: 01/12/2024
 */
#include "../sort.h"

/**
 * Partitions the element at end_idx in the given array and rearranges the elements so that all elements less than the
 * pivot are on the left and all elements greater are on the right.
 * @param arr the array to be partitioned
 * @param start_idx the start index where the partitioning is performed on arr
 * @param end_idx the end index where the partitioning is performed on arr
 * @param instruction_counter pointer to the counter tracking the number of instructions
 * @return the new index of the pivot element after partitioning
 */
int partition(int arr[], const int start_idx, const int end_idx, unsigned long long int* instruction_counter) {
    ++(*instruction_counter);
    int x = arr[end_idx];
    int i = start_idx - 1;

    for (int j = start_idx; ++(*instruction_counter) && j < end_idx; ++j)
        if ((*instruction_counter += 2) && arr[j] < x)
            swap(arr, ++i, j, instruction_counter);

    swap(arr, i + 1, end_idx, instruction_counter);
    return i + 1;
}

/**
 * A helper recursive function that performs the Quicksort algorithm. It divides the array into two parts, and sorts
 * them independently.
 * @param arr the array to be sorted
 * @param start_idx the start index of the sub-array to be sorted
 * @param end_idx the end index of the sub-array to be sorted
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void recursive_quicksort(int arr[], const int start_idx, const int end_idx, unsigned long long int* instruction_counter) {
    if (++(*instruction_counter) && end_idx - start_idx < 1)
        return;
    int p = partition(arr, start_idx, end_idx, instruction_counter);
    recursive_quicksort(arr, start_idx, p - 1, instruction_counter);
    recursive_quicksort(arr, p + 1, end_idx, instruction_counter);
}

/**
 * Performs Quicksort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param args additional sorting arguments (not used in this implementation)
 * @return the total number of instructions executed during the sort
 */
unsigned long long int quicksort(int arr[], const int arr_length, const SortArgs args) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses
    recursive_quicksort(arr, 0, arr_length - 1, &instruction_counter);
    return instruction_counter;
}
