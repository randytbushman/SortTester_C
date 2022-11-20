/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include <stdlib.h>
#include "sort.h"


/**
 * Performs base-arr_length Radix Sort on the array where arr_length = len(arr).
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
void radix_sort(int arr[], int arr_length) {
    int i;

    int minValue = arr[0], maxValue = arr[0];
    for(i = 1; i < arr_length; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];
    maxValue -= minValue;

    int radix = arr_length;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(arr_length, sizeof(int));     // Array initializes to all zeros

    int isNextRadix = maxValue > 0;
    // exp is prone to overflowing. If error with Radix Sort, check tha first. Perhaps use a larger integer data type
    for (unsigned int exp = 1; isNextRadix;) {
        for (i = 0; i < radix; ++i)
            countingArr[((arr[i] - minValue) / exp) % radix]++;
        for (i = 1; i < radix; ++i)
            countingArr[i] += countingArr[i - 1];
        for (i = radix - 1; i > -1; --i)
            shadowArr[--countingArr[((arr[i] - minValue) / exp) % radix]] = arr[i];
        for (i = 0; i < radix; ++i)
            arr[i] = shadowArr[i];
        if (maxValue / (exp *= radix) > 0)
            for (i = 0; i < arr_length; ++i)
                countingArr[i] = 0;
        else
            isNextRadix = 0;
    }
    free(shadowArr);
    free(countingArr);
}