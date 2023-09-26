/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include <stdlib.h>
#include "sort.h"

static unsigned long long int instruction_counter = 0; // # of comparisons + array accesses


/**
 * Performs base-arr_length Radix Sort on the array where arr_length = len(arr).
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int radix_sort(int arr[], int arr_length) {
    int i;
    int minValue = arr[0], maxValue = arr[0];
    instruction_counter = 2;

    for(i = 1; (i < arr_length) && ++instruction_counter; ++i) {
        ++instruction_counter;
        if ((arr[i] < minValue) && (instruction_counter += 2))
            minValue = arr[i];
        else if ((arr[i] > maxValue) && (instruction_counter += 2))
            maxValue = arr[i];
    }

    maxValue -= minValue;
    int radix = arr_length;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(arr_length, sizeof(int));     // Array initializes to all zeros

    int isNextRadix = maxValue > 0;
    // exp is prone to overflowing. If error with Radix Sort, check tha first. Perhaps use a larger integer data type
    for (unsigned int exp = 1; isNextRadix && ++instruction_counter;) {
        for (i = 0; i < radix && ++instruction_counter; ++i) {
            countingArr[((arr[i] - minValue) / exp) % radix]++;
            instruction_counter += 2;

        }
        for (i = 1; i < radix && ++instruction_counter; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;

        }
        for (i = radix - 1; i > -1 && ++instruction_counter; --i) {
            shadowArr[--countingArr[((arr[i] - minValue) / exp) % radix]] = arr[i];
            instruction_counter += 4;
        }
        for (i = 0; i < radix && ++instruction_counter; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }
        if ((maxValue / (exp *= radix) > 0) && ++instruction_counter)
            for (i = 0; i < arr_length && ++instruction_counter; ++i) {
                countingArr[i] = 0;
                ++instruction_counter;
            }
        else
            isNextRadix = 0;
    }
    free(shadowArr);
    free(countingArr);
    return instruction_counter;
}