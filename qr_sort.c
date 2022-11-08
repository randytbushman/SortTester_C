//
// Created by randy on 10/18/2022.
//

#include "qr_sort.h"
#include <stdlib.h>

void qr_sort_divisor_n(int *arr, int n) {
    qr_sort(arr, n, n);
}

void qr_sort(int *arr, int n, int divisor)
{
    int i;
    int minValue = arr[0], maxValue = arr[0];

    for(i = 1; i < n; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = ((maxValue - minValue) / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < n; ++i)
        ++countingArr[(arr[i] - minValue) % divisor];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = n-1; i > -1; --i)
        shadowArr[--countingArr[(arr[i] - minValue) % divisor]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < n; ++i)
            ++countingArr[(shadowArr[i] - minValue) / divisor];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = n - 1; i > -1; --i)
            arr[--countingArr[(shadowArr[i] - minValue) / divisor]] = shadowArr[i];
    }
    else {
        for (i = 0; i < n; ++i)
            arr[i] = shadowArr[i];
    }
    free(shadowArr);
    free(countingArr);

}

void qr_sort_min_value_zero(int *arr, int n, int divisor)
{
    int i;
    // Find the minimum and maximum values
    int maxValue = arr[0];
    for(i = 1; i < n; ++i)
        if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = (maxValue / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < n; ++i)
        ++countingArr[arr[i] % divisor];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = n - 1; i > -1; --i)
        shadowArr[--countingArr[arr[i] % divisor]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < n; ++i)
            ++countingArr[shadowArr[i]/ divisor];
        for(i = 1; i < n; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = n - 1; i > -1; --i)
            arr[--countingArr[shadowArr[i] / divisor]] = shadowArr[i];
    }
    else
        for(i = 0; i < n; ++i)
            arr[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}

void qr_sort_power_2(int *arr, int n, int power)
{
    int i;
    int divisor = 1 << power;

    // Find the minimum and maximum values
    int minValue = arr[0], maxValue = arr[0];
    for(i = 1; i < n; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < n; ++i)
        ++countingArr[(arr[i] - minValue) & (divisor-1)];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = n - 1; i > -1; --i)
        shadowArr[--countingArr[(arr[i] - minValue) & (divisor-1)]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < n; ++i)
            ++countingArr[(shadowArr[i] - minValue) >> power];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = n - 1; i > -1; --i)
            arr[--countingArr[(shadowArr[i] - minValue) >> power]] = shadowArr[i];
    }
    else
        for(i = 0; i < n; ++i)
            arr[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}

void qr_sort_power_2_min_value_zero(int *arr, int n, int power)
{
    int i;
    int divisor = 1 << power;

    // Find the minimum and maximum values
    int maxValue = arr[0];
    for(i = 1; i < n; ++i)
        if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));


    // Perform Counting Sort with remainder values
    for(i = 0; i < n; ++i)
        ++countingArr[arr[i] & (divisor-1)];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = n - 1; i > -1; --i)
        shadowArr[--countingArr[arr[i] & (divisor-1)]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;
        // Perform Counting Sort on quotient values
        for(i = 0; i < n; ++i)
            ++countingArr[shadowArr[i] >> power];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = n - 1; i > -1; --i)
            arr[--countingArr[shadowArr[i] >> power]] = shadowArr[i];
    }
    else
        for(i = 0; i < n; ++i)
            arr[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}