//
// Created by randy on 10/17/2022.
//
#include "countingsort.h"
#include <stdlib.h>

void counting_sort(int *array, int n) {
    int i;
    int minValue = array[0], maxValue = array[0];

    // Locates minimum and maximum values
    for(i = 1; i < n; ++i)
        if(array[i] < minValue)
            minValue = array[i];
        else if(array[i] > maxValue)
            maxValue = array[i];

    int k =  maxValue - minValue + 1;   // Length of the counting array
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    for(i = 0; i < n; ++i)
        ++countingArr[array[i] - minValue];
    for(i = 1; i < k; ++i)
        countingArr[i] += countingArr[i - 1];
    for(i = n - 1; i > -1; --i)
        shadowArr[--countingArr[array[i] - minValue]] = array[i];
    for(i = 0; i < n; ++i)
        array[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}
