/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "array_utils.h"
#include "sort.h"
#include <stdlib.h>

/**
 *
 * @param arr
 * @param aux_arr
 * @param keys
 * @param counting_arr
 * @param arr_length
 * @param counting_arr_length
 * @param move_aux
 * @return
 */
void counting_key_sort(int arr[], int aux_arr[], const int keys[], int counting_arr[], int arr_length, int counting_arr_length, int move_aux, unsigned long long int* instruction_counter) {
    int i;

    *instruction_counter += arr_length;
    // Count occurrences using keys
    for (i = 0; i < arr_length; ++i) {
        counting_arr[keys[i]]++;
    }

    // Accumulate counts
    for (i = 1; i < counting_arr_length; ++i) {
        counting_arr[i] += counting_arr[i - 1];
    }

    // Rearrange elements
    for (i = arr_length - 1; i >= 0; --i) {
        aux_arr[--counting_arr[keys[i]]] = arr[i];
    }

    // Copy back to original array
    if (move_aux) {
        for (i = 0; i < arr_length; ++i) {
            arr[i] = aux_arr[i];
        }
    }
}


unsigned long long int counting_sort(int arr[], int arr_length, int min_value_zero) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Find minimum and maximum array values
    int min_value, max_value;
    if (min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    }
    else
        find_min_max(arr, arr_length, &min_value, &max_value, &instruction_counter);

    // Auxiliary and keys array
    int* aux_arr = malloc(arr_length * sizeof(int));
    int* counting_arr = calloc((max_value - min_value + 1), sizeof(int));

    // Call the modified counting_key_sort function
    counting_key_sort(arr, aux_arr, arr, counting_arr, arr_length, (max_value - min_value + 1), 1, &instruction_counter);

    // Free the allocated memory
    free(aux_arr);
    free(counting_arr);

    return instruction_counter;
}
