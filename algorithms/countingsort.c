/**
 * @author: Randolph Bushman
 * @date: 01/12/2024
 */
#include "../sort_utils.h"
#include "../sort.h"
#include <stdlib.h>

/**
 * Performs counting key sort on the given array.
 * @param arr the array of integers to be sorted
 * @param aux_arr an auxiliary array used for sorting
 * @param keys an array of keys corresponding to the elements in arr
 * @param counting_arr an array used for counting occurrences of each key
 * @param arr_length the length of arr, aux_arr, and keys
 * @param counting_arr_length The length of counting_arr
 * @param move_aux a flag indicating whether to copy sorted elements back to arr (1: Yes, 0: No).
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void counting_key_sort(int arr[], int aux_arr[], const int keys[], int counting_arr[], const int arr_length, const int counting_arr_length, const int move_aux, unsigned long long int* instruction_counter) {
    *instruction_counter += 3 * arr_length + 1;
    *instruction_counter += 3 * counting_arr_length;
    *instruction_counter += 5 * arr_length + 1;

    // Count occurrences using keys
    for (int i = 0; i < arr_length; ++i)
        counting_arr[keys[i]]++;

    // Accumulate counts
    for (int i = 1; i < counting_arr_length; ++i)
        counting_arr[i] += counting_arr[i - 1];

    // Rearrange elements
    for (int i = arr_length - 1; i > -1; --i)
        aux_arr[--counting_arr[keys[i]]] = arr[i];

    // Copy back to original array
    if (move_aux) {
        *instruction_counter += 3 * arr_length + 1;
        for (int i = 0; i < arr_length; ++i)
            arr[i] = aux_arr[i];
    }
}

/**
 * Performs Counting Sort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param args additional sorting arguments (not used in this implementation)
 * @return the total number of instructions executed during the sort
 */
unsigned long long int counting_sort(int arr[], const int arr_length, const SortArgs args) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Find minimum and maximum array values
    int min_value, max_value;
    if (args.min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    } else
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
