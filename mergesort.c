/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>

static unsigned long long int instruction_counter = 0; // # of comparisons + array accesses


/**
 * Performs recursive Merge Sort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int merge_sort(int arr[], int arr_length) {
    instruction_counter = 0;
    int mid = arr_length >> 1;
    int *aux_array = malloc(arr_length * sizeof (int));
    merge_sort_recursive(arr, aux_array, 0, mid);
    merge_sort_recursive(arr, aux_array, mid + 1, arr_length - 1);
    merge(arr, aux_array, 0, mid, arr_length - 1);
    free(aux_array);
    return instruction_counter;
}

/**
 * A helper recursive function used to perform merge sort from the start index to the end index.
 * @param arr the array to be sorted
 * @param aux_arr an auxiliary array used as temporary storage
 * @param start_idx the start index where merge sort is performed on arr
 * @param end_idx the end index where Merge Sort is performed on arr
 */
void merge_sort_recursive(int arr[], int aux_arr[], int start_idx, int end_idx) {
    int mid = (start_idx + end_idx) >> 1;
    ++instruction_counter;
    if(start_idx >= end_idx)
        return;
    merge_sort_recursive(arr, aux_arr, start_idx, mid);
    merge_sort_recursive(arr, aux_arr, mid + 1, end_idx);
    merge(arr, aux_arr, start_idx, mid, end_idx);
}

/**
 * Merges two sorted segments of arr from start_idx to mid_idx and mid_idx + 1 to end_idx.
 * @param arr the array where merging is taking place
 * @param aux_arr an auxiliary array used as temporary storage
 * @param start_idx the index that represents the start of the first segment
 * @param mid_idx the index that represents the end of the first segment and the beginning of the second segment
 * @param end_idx the index that represents the end of the second index
 */
void merge(int arr[], int aux_arr[], int start_idx, int mid_idx, int end_idx) {
    int i = start_idx;
    int j = mid_idx + 1;
    int k = 0;

    // Begin merge and store results in aux_arr
    while((++instruction_counter && i <= mid_idx) && j <= (++instruction_counter && end_idx)) {
        instruction_counter += 4;
        if (arr[i] < arr[j])
            aux_arr[k++] = arr[i++];
        else
            aux_arr[k++] = arr[j++];
    }

    // Fill remaining items from after merge into aux_arr
    while(++instruction_counter && i <= mid_idx) {
        aux_arr[k++] = arr[i++];
        instruction_counter += 2;
    }
    while(++instruction_counter && j <= end_idx) {
        aux_arr[k++] = arr[j++];
        instruction_counter += 2;
    }
    // Fill arr with the values of aux_arr
    for(int x = end_idx; ++instruction_counter && x >= start_idx ; --x) {
        arr[x] = aux_arr[--k];
        instruction_counter += 2;
    }
}