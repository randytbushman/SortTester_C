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
 * @param keys
 * @param arr_length
 * @param min_value
 * @param exp
 * @param args
 * @param instruction_counter
 */
void compute_keys(int arr[], int keys[], int arr_length, int min_value, unsigned long long int exp, SortArgs args, unsigned long long int *instruction_counter) {
    if (args.bitwise_ops) {
        *instruction_counter += 5 * arr_length + 1;
        if (args.min_value_zero) {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = (arr[i] >> __builtin_ctz(exp)) & (args.radix - 1);
            }
        } else {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = ((arr[i] - min_value) >> __builtin_ctz(exp)) & (args.radix - 1);
            }
        }
    } else {
        int val;
        *instruction_counter += (3 * arr_length) + 1;
        if (args.min_value_zero) {
            for (int i = 0; i < arr_length; ++i) {
                val = arr[i] / exp;
                *instruction_counter += compute_srt_operations(arr[i], exp) + compute_srt_operations(val, args.radix);
                keys[i] = val % args.radix;
            }
        } else {
            for (int i = 0; i < arr_length; ++i) {
                val = arr[i] / exp;
                *instruction_counter += compute_srt_operations(arr[i], exp) + compute_srt_operations(val, args.radix);
                keys[i] = ((arr[i] - min_value) / exp) % args.radix;
            }
        }

    }
}

/**
 * Performs base-arr_length Radix Sort on the array where arr_length = len(arr).
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param args
 */
unsigned long long int radix_sort(int arr[], int arr_length, SortArgs args) {
    int radix = (args.radix > 0) ? args.radix : arr_length;
    args.radix = radix;

    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Find min and max array values to get the max_quotient value
    int min_value, max_value;
    if (args.min_value_zero) {
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

    unsigned long long int exp = 1;
    int is_next_radix = max_value > 0;
    while (is_next_radix) {

        // Compute the keys for the next least significant digit
        compute_keys(temp_a, keys, arr_length, min_value, exp, args, &instruction_counter);

        exp *= radix;
        is_next_radix = (max_value / exp) > 0;

        // Check if there is another radix to iterate over after the current one
        if (!is_next_radix) {
            counting_key_sort(temp_a, temp_b, keys, counting_arr, arr_length, radix, arr == temp_a, &instruction_counter);
        } else {
            counting_key_sort(temp_a, temp_b, keys, counting_arr, arr_length, radix, 0, &instruction_counter);

            // Reset Counting Array Values
            instruction_counter += 2 * arr_length + 1;
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
