/**
 * @author: Randolph Bushman
 * @date: 1/12/2024
 */
#include "../sort.h"
#include <stdlib.h>

/**
 * Computes and stores the remainder keys of arr.
 * @param arr the elements of which to compute the remainder keys
 * @param keys where the remainder keys are stored
 * @param arr_length the length of arr
 * @param min_value the minimum value in arr
 * @param args additional sorting arguments
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void compute_remainder_keys(const int arr[], int keys[], const int arr_length, const int min_value, const SortArgs args, unsigned long long int *instruction_counter) {
    if (args.bitwise_ops) {
        *instruction_counter += (4 * arr_length) + 1;
        if (args.min_value_zero)
            for (int i = 0; i < arr_length; ++i)
                keys[i] = arr[i] & (args.divisor - 1);
        else
            for (int i = 0; i < arr_length; ++i)
                keys[i] = (arr[i] - min_value) & (args.divisor - 1);
    }
    else {
        *instruction_counter += (3 * arr_length) + 1 + (DIVISION_INSTRUCTION_WEIGHT * arr_length);  // Add weighted modulo operation count
        if (args.min_value_zero)
            for (int i = 0; i < arr_length; ++i)
                keys[i] = arr[i] % args.divisor;
        else
            for (int i = 0; i < arr_length; ++i)
                keys[i] = (arr[i] - min_value) % args.divisor;
    }
}

/**
 * Computes and stores the quotient keys of arr.
 * @param arr the elements of which to compute the quotient keys
 * @param keys where the quotient keys are stored
 * @param arr_length the length of arr
 * @param min_value the minimum value in arr
 * @param args additional sorting arguments
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void compute_quotient_keys(const int arr[], int keys[], const int arr_length, const int min_value, const SortArgs args, unsigned long long int *instruction_counter) {
    if (args.bitwise_ops) {
        *instruction_counter += (4 * arr_length) + 1;
        if (args.min_value_zero) {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = arr[i] >> __builtin_ctz(args.divisor); // Bitwise shift for power of 2 divisor
            }
        } else {
            for (int i = 0; i < arr_length; ++i) {
                keys[i] = (arr[i] - min_value) >> __builtin_ctz(args.divisor); // Bitwise shift for power of 2 divisor
            }
        }
    } else {
        *instruction_counter += (3 * arr_length) + 1 + (DIVISION_INSTRUCTION_WEIGHT * arr_length); // Add weighted division operation count
        if (args.min_value_zero)
            for (int i = 0; i < arr_length; ++i)
                keys[i] = arr[i] / args.divisor;
        else
            for (int i = 0; i < arr_length; ++i)
                keys[i] = (arr[i] - min_value) / args.divisor;
    }
}

/**
 * Performs QR Sort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param args additional sorting arguments
 * @return the total number of instructions executed during the sort
 */
unsigned long long int qr_sort(int arr[], const int arr_length, SortArgs args) {
    unsigned long long int instruction_counter = 0;

    // If divisor is not a positive int, assign to arr_length
    if (args.divisor <= 0)
        args.divisor = arr_length;
    int divisor = args.divisor;

    // Find min and max array values to get the max_quotient value
    int min_value, max_value;
    if (args.min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    } else
        find_min_max(arr, arr_length, &min_value, &max_value, &instruction_counter);
    int max_quotient = ((max_value - min_value) / divisor) + 1;
    instruction_counter += DIVISION_INSTRUCTION_WEIGHT;

    // Define auxiliary array and keys
    int* aux_arr = malloc(arr_length * sizeof(int));
    int* counting_arr = calloc(divisor > max_quotient ? divisor : max_quotient, sizeof(int));
    int* keys = malloc(arr_length * sizeof(int));

    // Compute remainder keys
    compute_remainder_keys(arr, keys, arr_length, min_value, args, &instruction_counter);

    // Perform Remainder Sort; Quotient Sort is not necessary if end-early condition is met
    if (max_quotient == 1) {
        counting_key_sort(arr, aux_arr, keys, counting_arr, arr_length, divisor, 1, &instruction_counter);
    } else {
        // Perform Counting Sort on the Remainder Keys
        counting_key_sort(arr, aux_arr, keys, counting_arr, arr_length, divisor, 0, &instruction_counter);

        // Reset counting array
        instruction_counter += 2 * (divisor > max_quotient ? max_quotient : divisor) + 1;
        for(int i = 0; i < (divisor > max_quotient ? max_quotient : divisor); ++i)
            counting_arr[i] = 0;

        // Compute quotient keys
        compute_quotient_keys(aux_arr, keys, arr_length, min_value, args, &instruction_counter);

        // Perform Counting Sort on the Quotient Keys
        counting_key_sort(aux_arr, arr, keys, counting_arr, arr_length, max_quotient, 0, &instruction_counter);
    }

    free(aux_arr);
    free(counting_arr);
    free(keys);
    return instruction_counter;
}
