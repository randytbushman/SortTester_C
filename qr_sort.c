/**
 * @author: Randolph Bushman
 * @date: 1/2/2024
 */
#include "sort.h"
#include "sort_utils.h"
#include <stdlib.h>
#include <math.h>

unsigned int compute_srt_operations(unsigned int n, unsigned int m) {
    // Calculate maximum bit width of n and m using logarithms
    unsigned int max_n_m = (n > m) ? n : m;
    unsigned int max_bit_width = (max_n_m > 0) ? (int)floor(log2(max_n_m)) + 1 : 1;  // Ensure at least 1 iteration

    // Maximum operations per iteration
    const unsigned int OPERATIONS_PER_ITERATION = 6;
    return OPERATIONS_PER_ITERATION * max_bit_width;
}

unsigned long long int qr_sort(int arr[], int arr_length, SortArgs args) {
    if (args.divisor <= 0) // If divisor is not a positive int, assign to arr_length
        args.divisor = arr_length;
    int divisor = args.divisor;

    // # Total number of comparisons + array accesses + divisor and modulo operations
    unsigned long long int instruction_counter = 0;

    // Find min and max array values to get the max_quotient value
    int min_value, max_value;
    if (args.min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    }
    else
        find_min_max(arr, arr_length, &min_value, &max_value, &instruction_counter);
    int max_quotient = ((max_value - min_value) / divisor) + 1;

    // Define auxiliary array and keys
    int* aux_arr = malloc(arr_length * sizeof(int));
    int* counting_arr = calloc(divisor > max_quotient ? divisor : max_quotient, sizeof(int));
    int* keys = malloc(arr_length * sizeof(int));

    // Compute remainder keys
    if (args.use_bitwise_ops) {
        for (int i = 0; i < arr_length; ++i) {
            keys[i] = arr[i] & (divisor - 1); // Bitwise AND for power of 2 divisor
        }
    }
    else {
        for (int i = 0; i < arr_length; ++i) {
            keys[i] = arr[i] % divisor;
        }
    }

    // Perform Remainder Sort; Quotient Sort is not necessary if end-early condition is met
    if (max_quotient == 1) {
        counting_key_sort(arr, aux_arr, keys, counting_arr, arr_length, divisor, 1, &instruction_counter);
    }
    else {
        // Remainder Sort
        counting_key_sort(arr, aux_arr, keys, counting_arr, arr_length, divisor, 0, &instruction_counter);

        // Reset counting array - can optimize.
        for(int i = 0; i < divisor; ++i)
            counting_arr[i] = 0;

        // Compute quotient keys
        if (args.use_bitwise_ops) {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = aux_arr[i] >> __builtin_ctz(divisor); // Bitwise shift for power of 2 divisor
            }
        }
        else {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = aux_arr[i] / divisor; // Standard division
            }
        }

        // Perform Quotient Sort
        counting_key_sort(aux_arr, arr, keys, counting_arr, arr_length, max_quotient, 0, &instruction_counter);
    }

    // Free memory
    free(aux_arr);
    free(counting_arr);
    free(keys);
    return instruction_counter;
}
