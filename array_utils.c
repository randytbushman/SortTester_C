/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "array_utils.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Given a reference array (ref_arr) and an array to clone to (clone_to_arr), this function copies the values from
 * ref_arr into clone_to_arr => clone_to_arr[i] = ref_arr[i] for i=0 to arr_length.
 * @param ref_arr the array that the clone_to_arr references
 * @param clone_to_arr the array to clone the reference values to
 * @param arr_length the length of ref_arr; len(ref_arr) == len(clone_to_arr)
 */
void clone_array(const int ref_arr[], int clone_to_arr[], int arr_length) {
    for(int i = 0; i < arr_length; ++i)
        clone_to_arr[i] = ref_arr[i];
}

/**
 * Generates a random int between the specified min and max values.
 * Reference: https://forums.codeguru.com/showthread.php?534679-Generating-big-random-numbers-in-C
 * @param min the minimum inclusive value
 * @param max the maximum exclusive value
 * @return a random int between the specified min and max values
 */
int generate_random_number(int min, int max) {
    // Random numbers in the stdlib.h library only generate values as large as 2^15. As a result, we bitwise OR and
    // bitwise left shift 4 random numbers to generate a larger values.
    return ((((rand() & 0xff)<<8 | (rand() & 0xff))<<8 | (rand() & 0xff))<<7 | (rand() & 127)) % (max + 1 - min) + min;
}

/**
 * Ensures that the given array is sorted in ascending order.
 * @param arr the array to be tested
 * @param arr_length the length of the array
 * @return 0 if the array is not sorted, and 1 if the array is sorted
 */
int is_sorted_ascending(const int arr[], int arr_length) {
    for (int i = 1; i < arr_length; ++i)
        if (arr[i-1] > arr[i])
            return 0;
    return 1;
}

/**
 * Populates the given array with linearly spaced values in ascending order from the given minimum and maximum values.
 * @param arr the array to be populated
 * @param arr_length the length of the array
 * @param min the minimum array value; min < max
 * @param max the maximum array value; max > min
 */
void lin_space(int arr[], int arr_length, int min, int max) {
    arr[0] = min;
    arr[arr_length - 1] = max;
    for(int i = 1; i < arr_length - 1; ++i)
        arr[i] = (int) (i * ((max - min) / (double) arr_length)) + arr[0];

}

/**
 * Given an int array and int array length, print a string representation of the array to the standard output.
 * @param arr the array to be printed
 * @param arr_length the length of the array
 */
void print_int_array(int arr[], int arr_length) {
    printf("[%d", arr[0]);
    for (int i = 1; i < arr_length; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
}

/**
 * Given an int array and int array length, shuffle all the elements of the array with the Fisher-Yates algorithm which
 * produces an unbiased permutation.
 * @param arr the array to be shuffled
 * @param arr_length the length of the array
 */
void shuffle(int arr[], int arr_length) {
    int random_index;
    int tmp;
    for(int i = arr_length - 1; i > 0; --i) {
        random_index = generate_random_number(0, i);
        tmp = arr[random_index];
        arr[random_index] = arr[i];
        arr[i] = tmp;
    }
}

/**
 * Given an array and pointers, find and store the minimum and maximum values and increment the instruction counter
 * accordingly.
 * @param arr
 * @param arr_length
 * @param min
 * @param max
 * @param instruction_counter
 */
void find_min_max(const int arr[], int arr_length, int *min, int *max, unsigned long long int *instruction_counter) {
    int i;
    *min = arr[0];
    *max = *min;
    for(i = 1; (i < arr_length); ++i) {
        ++instruction_counter;
        if (arr[i] < *min)
            *min = arr[i];
        else if (arr[i] > *max)
            *max = arr[i];
    }
}

void find_max(const int arr[], int arr_length, int *max, unsigned long long int *instruction_counter) {
    int i;
    *max = arr[0];
    for(i = 1; (i < arr_length); ++i) {
        ++instruction_counter;
        if (arr[i] > *max)
            *max = arr[i];
    }
}
