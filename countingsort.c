/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort_utils.h"
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
void counting_key_sort(int arr[], int aux_arr[], const int keys[], int counting_arr[], const int arr_length, const int counting_arr_length, const int move_aux, unsigned long long int* instruction_counter) {
    // Count occurrences using keys
    *instruction_counter += 3 * arr_length + 1;
    for (int i = 0; i < arr_length; ++i) {
        counting_arr[keys[i]]++;
    }

    // Accumulate counts
    *instruction_counter += 3 * counting_arr_length;
    for (int i = 1; i < counting_arr_length; ++i) {
        counting_arr[i] += counting_arr[i - 1];
    }

    // Rearrange elements
    *instruction_counter += 5 * arr_length + 1;
    for (int i = arr_length - 1; i > -1; --i) {
        aux_arr[--counting_arr[keys[i]]] = arr[i];
    }

    // Copy back to original array
    if (move_aux) {
        *instruction_counter += 3 * arr_length + 1;
        for (int i = 0; i < arr_length; ++i) {
            arr[i] = aux_arr[i];
        }
    }
}

/**
 *
 * @param arr
 * @param arr_length
 * @param args
 * @return
 */
unsigned long long int counting_sort(int arr[], int arr_length, SortArgs args) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Find minimum and maximum array values
    int min_value, max_value;
    if (args.min_value_zero) {
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

    free(aux_arr);
    free(counting_arr);
    return instruction_counter;
}
