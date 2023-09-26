/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>

static unsigned long long int instruction_counter = 0; // # of comparisons + array accesses


/**
 * Performs ascending counting_sort on the array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int counting_sort(int arr[], int arr_length) {
    int i;
    instruction_counter = 2;
    int minValue = arr[0], maxValue = arr[0];

    // Locates minimum and maximum values
    for(i = 1; i < arr_length && ++instruction_counter; ++i) {
        ++instruction_counter;
        if (arr[i] < minValue && (instruction_counter += 2))
            minValue = arr[i];
        else if (arr[i] > maxValue && (instruction_counter += 2))
            maxValue = arr[i];
    }

    int k =  maxValue - minValue + 1;   // Length of the counting arr
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    for(i = 0; i < arr_length && ++instruction_counter; ++i) {
        ++countingArr[arr[i] - minValue]; instruction_counter += 2;
    }
    for(i = 1; i < k && ++instruction_counter; ++i) {
        countingArr[i] += countingArr[i - 1]; instruction_counter += 2;
    }
    for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
        shadowArr[--countingArr[arr[i] - minValue]] = arr[i]; instruction_counter += 4;
    }
    for(i = 0; i < arr_length && ++instruction_counter; ++i) {
        arr[i] = shadowArr[i]; instruction_counter += 2;
    }

    free(shadowArr);
    free(countingArr);
    return instruction_counter;
}
