/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

    for(i = 1; (++instruction_counter) && (i < arr_length); ++i) {
        ++instruction_counter;
        if ((instruction_counter += 2) && (arr[i] < minValue))
            minValue = arr[i];
        else if ((instruction_counter += 2) && (arr[i] > maxValue))
            maxValue = arr[i];
    }

    maxValue -= minValue;
    int radix = arr_length;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(arr_length, sizeof(int));     // Array initializes to all zeros
    int num_iterations = 0;

    ++instruction_counter;
    int isNextRadix = maxValue > 0;
    for (unsigned long long int exp = 1; isNextRadix;) {
        for (i = 0; (++instruction_counter) && (i < radix); ++i) {
            countingArr[((arr[i] - minValue) / exp) % radix]++;
            instruction_counter += 2;
        }

        for (i = 1; (++instruction_counter) && (i < radix); ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;

        }

        for (i = radix - 1; (++instruction_counter) && (i > -1); --i) {
            shadowArr[--countingArr[((arr[i] - minValue) / exp) % radix]] = arr[i];
            instruction_counter += 4;
        }

        for (i = 0; (++instruction_counter) && (i < radix); ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }

        if ((++instruction_counter) && (maxValue / (exp *= radix) > 0)) {
            for (i = 0; (++instruction_counter) && (i < arr_length); ++i) {
                countingArr[i] = 0;
                ++instruction_counter;
            }
        }
        else
            isNextRadix = 0;
        ++num_iterations;
    }

    free(shadowArr);
    free(countingArr);
    return instruction_counter;
}