/**
 * @author: Randolph Bushman
 * @date: 1/12/2024
 */
#include "../sort_utils.h"
#include "../sort.h"
#include <stdlib.h>

/**
 * Computes the sorting keys for each element in the array based on the current digit.
 * @param arr the elements of which to compute the keys
 * @param keys array to store the computed keys for sorting
 * @param arr_length the length of the input array
 * @param min_value the minimum value in the array
 * @param exp the exponent representing the current digit being processed
 * @param args additional sorting arguments
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void compute_keys(const int arr[], int keys[], const int arr_length, const int min_value, const unsigned long long int exp, const SortArgs args, unsigned long long int *instruction_counter) {
    if (args.bitwise_ops) {
        *instruction_counter += 5 * arr_length + 1;
        if (args.min_value_zero)
            for (int i = 0; i < arr_length; ++i)
                keys[i] = (arr[i] >> __builtin_ctz(exp)) & (args.radix - 1);
        else
            for (int i = 0; i < arr_length; ++i)
                keys[i] = ((arr[i] - min_value) >> __builtin_ctz(exp)) & (args.radix - 1);
    } else {
        *instruction_counter += (3 * arr_length) + 1 + (2 * DIVISION_INSTRUCTION_WEIGHT * arr_length);  // Add weighted division and modulo operation count
        if (args.min_value_zero)
            for (int i = 0; i < arr_length; ++i)
                keys[i] = (arr[i] / exp) % args.radix;
        else
            for (int i = 0; i < arr_length; ++i)
                keys[i] = ((arr[i] - min_value) / exp) % args.radix;
    }
}

/**
 * Performs Radix Sort on the given array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param args additional sorting arguments
 * @return the total number of instructions executed during the sort.
 */
unsigned long long int radix_sort(int arr[], const int arr_length, SortArgs args) {
    unsigned long long int instruction_counter = 0;  // # of comparisons + array accesses

    // Determine the radix (base) for the sorting; defaults to arr_length if not specified
    int radix = (args.radix > 0) ? args.radix : arr_length;
    args.radix = radix;

    // Find the minimum and maximum values in the array for range calculation
    int min_value, max_value;
    if (args.min_value_zero) {
        min_value = 0;
        find_max(arr, arr_length, &max_value, &instruction_counter);
    } else
        find_min_max(arr, arr_length, &min_value, &max_value, &instruction_counter);
    max_value -= min_value;  // Normalize max value based on min value

    // Allocate memory for auxiliary array and keys
    int* aux_arr = malloc(arr_length * sizeof(int));
    int* keys = malloc(arr_length * sizeof(int));
    int* counting_arr = calloc(radix, sizeof(int));

    // Initialize pointers for swapping arrays
    int* temp_a = arr;
    int* temp_b = aux_arr;
    int* temp = NULL;

    unsigned long long int exp = 1;  // Exponent to isolate each digit
    int is_next_radix = max_value > 0;  // Flag to check if another digit is to be sorted
    while (is_next_radix) {
        // Compute the keys for the next iteration
        compute_keys(temp_a, keys, arr_length, min_value, exp, args, &instruction_counter);
        exp *= radix;  // Moves to next digit

        instruction_counter += DIVISION_INSTRUCTION_WEIGHT;
        is_next_radix = (max_value / exp) > 0;  // Checks if there is another digit to be sorted after this one

        // Perform counting sort on the keys
        if (!is_next_radix)
            counting_key_sort(temp_a, temp_b, keys, counting_arr, arr_length, radix, arr == temp_a, &instruction_counter);
        else {
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

    free(aux_arr);
    free(counting_arr);
    free(keys);
    return instruction_counter;
}
