/**
 * @author: Randolph Bushman
 * @date: 1/10/2024
 */
#include "sort.h"
#include "sort_utils.h"
#include <stdlib.h>

/**
 * Merges two sorted segments of arr from start_idx to mid_idx and mid_idx + 1 to end_idx.
 * @param arr the array where merging is taking place
 * @param aux_arr an auxiliary array used as temporary storage
 * @param start_idx the index that represents the start of the first segment
 * @param mid_idx the index that represents the end of the first segment and the beginning of the second segment
 * @param end_idx the index that represents the end of the second index
 */
void merge(int arr[], int aux_arr[], const int start_idx, const int mid_idx, const int end_idx, unsigned long long int* instruction_counter) {
    int i = start_idx, j = mid_idx + 1, k = start_idx;

    while ((++(*instruction_counter) && i <= mid_idx) && (++(*instruction_counter) && j <= end_idx)) {
        *instruction_counter += 5;
        if (arr[i] < arr[j])
            aux_arr[k++] = arr[i++];
        else
            aux_arr[k++] = arr[j++];
    }

    // Increment counters for the next 3 loops
    *instruction_counter += ((mid_idx - i + 1) + (mid_idx - i) * 2);
    *instruction_counter += ((end_idx - j + 1) + (end_idx - j) * 2);
    *instruction_counter += ((end_idx - start_idx + 1) + (end_idx - start_idx) * 2);

    while (i <= mid_idx)
        aux_arr[k++] = arr[i++];

    while (j <= end_idx)
        aux_arr[k++] = arr[j++];

    for (int x = start_idx; x <= end_idx; x++)
        arr[x] = aux_arr[x];
}

/**
 * A helper recursive function used to perform merge sort from the start index to the end index.
 * @param arr the array to be sorted
 * @param aux_arr an auxiliary array used as temporary storage
 * @param start_idx the start index where merge sort is performed on arr
 * @param end_idx the end index where Merge Sort is performed on arr
 */
void merge_sort_recursive(int arr[], int aux_arr[], const int start_idx, const int end_idx, unsigned long long int* instruction_counter) {
    if (++(*instruction_counter) && start_idx < end_idx) {
        int mid = (start_idx + end_idx) >> 1;
        merge_sort_recursive(arr, aux_arr, start_idx, mid, instruction_counter);
        merge_sort_recursive(arr, aux_arr, mid + 1, end_idx, instruction_counter);
        merge(arr, aux_arr, start_idx, mid, end_idx, instruction_counter);
    }
}

/**
 * Performs recursive Merge Sort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int merge_sort(int arr[], const int arr_length, const SortArgs args) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses
    int *aux_array = malloc(arr_length * sizeof (int));
    merge_sort_recursive(arr, aux_array, 0, arr_length - 1, &instruction_counter);
    free(aux_array);
    return instruction_counter;
}



