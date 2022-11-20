/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>

/**
 * Performs ascending counting_sort on the array.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
void counting_sort(int arr[], int arr_length) {
    int i;
    int minValue = arr[0], maxValue = arr[0];

    // Locates minimum and maximum values
    for(i = 1; i < arr_length; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];

    int k =  maxValue - minValue + 1;   // Length of the counting arr
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    for(i = 0; i < arr_length; ++i)
        ++countingArr[arr[i] - minValue];
    for(i = 1; i < k; ++i)
        countingArr[i] += countingArr[i - 1];
    for(i = arr_length - 1; i > -1; --i)
        shadowArr[--countingArr[arr[i] - minValue]] = arr[i];
    for(i = 0; i < arr_length; ++i)
        arr[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}
