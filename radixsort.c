#include <stdlib.h>
#include <stdio.h>
#include "radixsort.h"
//
// Created by randy on 10/18/2022.
//
void radix_sort(int *arr, int n) {
    int i;

    int minValue = arr[0], maxValue = arr[0];
    for(i = 1; i < n; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];
    maxValue -= minValue;

    int radix = n;
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(n, sizeof(int));     // Array initializes to all zeros

    int isNextRadix = (maxValue > 0);
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
            for (i = 0; i < n; ++i)
                countingArr[i] = 0;
        else
            isNextRadix = 0;
    }
    free(shadowArr);
    free(countingArr);
}