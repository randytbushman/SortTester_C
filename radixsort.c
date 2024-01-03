/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "array_utils.h"
#include "sort.h"
#include <stdlib.h>


/**
 * Performs base-arr_length Radix Sort on the array where arr_length = len(arr).
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int radix_sort(int arr[], int arr_length, int radix, int min_value_zero, int use_bitwise) {
    if (radix <= 0) // If radix is not a positive int, assign to arr_length
        radix = arr_length;

    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Find min and max array values to get the max_quotient value
    int min_value, max_value;
    if (min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    }
    else
        find_min_max(arr, arr_length, &min_value, &max_value, &instruction_counter);
    max_value -= min_value;

    // Auxiliary array and keys
    int* aux_arr = malloc(arr_length * sizeof(int));
    int* temp_a = arr;
    int* temp_b = aux_arr;
    int* temp = NULL;

    int* keys = malloc(arr_length * sizeof(int));
    int* counting_arr = calloc(radix, sizeof(int));

    // Compute the keys for the least significant digit
    for (int i = 0; i < arr_length; ++i) {
        if (use_bitwise) {
            keys[i] = ((arr[i] - min_value) >> __builtin_ctz(use_bitwise)) % radix; // Bitwise shift
        } else {
            keys[i] = ((arr[i] - min_value)) % radix; // Standard division
        }
    }

    unsigned long long int exp = 1;
    int is_next_radix = max_value > 0;
    while (is_next_radix) {
        exp *= radix;
        is_next_radix = (max_value / exp) > 0;

        // Check if there is another radix to iterate over after the current one
        if (!is_next_radix) {
            counting_key_sort(temp_a, temp_b, keys, counting_arr, arr_length, radix, arr == temp_a, &instruction_counter);
        } else {
            counting_key_sort(temp_a, temp_b, keys, counting_arr, arr_length, radix, 0, &instruction_counter);

            // Compute the keys for the next least significant digit
            for (int i = 0; i < arr_length; ++i) {
                if (use_bitwise) {
                    keys[i] = ((temp_b[i] - min_value) >> __builtin_ctz(exp)) % radix; // Bitwise shift
                } else {
                    keys[i] = ((temp_b[i] - min_value) / exp) % radix; // Standard division
                }
            }

            // Reset Counting Array Values
            for (int i = 0; i < radix; ++i)
                counting_arr[i] = 0;

            // Swap pointers to avoid extra copy from aux_arr to arr
            temp = temp_a;
            temp_a = temp_b;
            temp_b = temp;
        }
    }

    // Free memory
    free(aux_arr);
    free(counting_arr);
    free(keys);
    return instruction_counter;
}
