/**
 * @author: Randolph Bushman
 * @date: 1/12/2024
 */
#include "sort_utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Given a reference array (arr) and an array to clone to (copy_arr), this function copies the values from
 * arr into copy_arr => copy_arr[i] = arr[i] for i=0 to arr_length.
 * @param arr the array that the copy_arr references
 * @param copy_arr the array to clone the reference values to
 * @param arr_length the length of arr; len(arr) == len(copy_arr)
 */
void clone_array(const int arr[], int copy_arr[], const int arr_length) {
    for(int i = 0; i < arr_length; ++i)
        copy_arr[i] = arr[i];
}

/**
 * Finds the maximum value in the given array.
 * @param arr the array to search
 * @param arr_length the length of the array
 * @param max a pointer to store the max value
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void find_max(const int arr[], const int arr_length, int *max, unsigned long long int *instruction_counter) {
    int i;
    *max = arr[0];
    for(i = 1; (i < arr_length); ++i) {
        *instruction_counter += 2;
        if (arr[i] > *max) {
            ++(*instruction_counter);
            *max = arr[i];
        }
    }
}

/**
 * Finds the minimum and maximum value in the given array.
 * @param arr the array to search
 * @param arr_length the length of the array
 * @param min a pointer to store the minimum value
 * @param max a pointer to store the maximum value
 * @param instruction_counter pointer to the counter tracking the number of instructions
 */
void find_min_max(const int arr[], const int arr_length, int *min, int *max, unsigned long long int *instruction_counter) {
    int i;
    *min = arr[0];
    *max = *min;
    for(i = 1; (i < arr_length); ++i) {
        *instruction_counter += 3;
        if (arr[i] < *min)
            *min = arr[i];
        else if (arr[i] > *max) {
            *instruction_counter += 2;
            *max = arr[i];
        }
    }
}

/**
 * Generates a random int between the specified min and max values.
 * Random numbers in the stdlib.h library only generate values as large as 2^15. As a result, we bitwise OR and bitwise
 * left shift 4 random numbers to generate a larger values.
 * Reference: https://forums.codeguru.com/showthread.php?534679-Generating-big-random-numbers-in-C
 * @param min the minimum inclusive value
 * @param max the maximum exclusive value
 * @return a random int between the specified min and max values
 */
int generate_random_number(const int min, const int max) {
    return ((((rand() & 0xff)<<8 | (rand() & 0xff))<<8 | (rand() & 0xff))<<7 | (rand() & 127)) % (max + 1 - min) + min;
}

/**
 * Ensures that the given array is sorted in ascending order.
 * @param arr the array to be tested
 * @param arr_length the length of the array
 * @return 0 if the array is not sorted, and 1 if the array is sorted
 */
int is_sorted_ascending(const int arr[], const int arr_length) {
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
void lin_space(int arr[], const int arr_length, const int min, const int max) {
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
void print_int_array(const int arr[], const int arr_length) {
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
void shuffle(int arr[], const int arr_length) {
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
 * Swaps the value at index i with the value at index j in the given array.
 * @param arr the array where swapping takes place
 * @param i the index of the first value to swap
 * @param j the index of the second value to swap
 */
void swap(int arr[], const int i, const int j, unsigned long long int* instruction_counter) {
    *instruction_counter += 4;
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
