/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>


/**
 * Performs QR Sort on the given array with divisor arr_length.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
void qr_sort_divisor_n(int arr[], int arr_length) {
    qr_sort(arr, arr_length, arr_length);
}

/**
 * Performs QR Sort on the given array with the given divisor.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param divisor the divisor used to determine remainder and quotient counting array sizes
 */
void qr_sort(int arr[], int arr_length, int divisor)
{
    int i;
    int minValue = arr[0], maxValue = arr[0];

    for(i = 1; i < arr_length; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = ((maxValue - minValue) / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length; ++i)
        ++countingArr[(arr[i] - minValue) % divisor];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = arr_length - 1; i > -1; --i)
        shadowArr[--countingArr[(arr[i] - minValue) % divisor]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length; ++i)
            ++countingArr[(shadowArr[i] - minValue) / divisor];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = arr_length - 1; i > -1; --i)
            arr[--countingArr[(shadowArr[i] - minValue) / divisor]] = shadowArr[i];
    }
    else {
        for (i = 0; i < arr_length; ++i)
            arr[i] = shadowArr[i];
    }
    free(shadowArr);
    free(countingArr);

}

/**
 * Performs QR Sort on the given array with the given divisor. This implementation assumes that the minimum value in the
 * array is zero.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param divisor the divisor used to determine remainder and quotient counting array sizes
 */
void qr_sort_min_value_zero(int arr[], int arr_length, int divisor)
{
    int i;
    int maxValue = arr[0];

    for(i = 1; i < arr_length; ++i)
        if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = (maxValue / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length; ++i)
        ++countingArr[arr[i] % divisor];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = arr_length - 1; i > -1; --i)
        shadowArr[--countingArr[arr[i] % divisor]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length; ++i)
            ++countingArr[shadowArr[i] / divisor];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = arr_length - 1; i > -1; --i)
            arr[--countingArr[shadowArr[i] / divisor]] = shadowArr[i];
    }
    else {
        for (i = 0; i < arr_length; ++i)
            arr[i] = shadowArr[i];
    }
    free(shadowArr);
    free(countingArr);
}

/**
 * Performs QR Sort on the given array. This implementation utilizes bitwise operations to compute the quotient and
 * remainder values.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param power we compute the divisor by raising 2 to this value
 */
void qr_sort_power_2(int arr[], int arr_length, int power)
{
    int i;
    int divisor = 1 << power;

    // Find the minimum and maximum values
    int minValue = arr[0], maxValue = arr[0];
    for(i = 1; i < arr_length; ++i)
        if(arr[i] < minValue)
            minValue = arr[i];
        else if(arr[i] > maxValue)
            maxValue = arr[i];

    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length; ++i)
        ++countingArr[(arr[i] - minValue) & (divisor-1)];
    for(i = 1; i < divisor; ++i)
        countingArr[i] += countingArr[i-1];
    for(i = arr_length - 1; i > -1; --i)
        shadowArr[--countingArr[(arr[i] - minValue) & (divisor-1)]] = arr[i];

    if(maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor; ++i)
            countingArr[i] = 0;

        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length; ++i)
            ++countingArr[(shadowArr[i] - minValue) >> power];
        for(i = 1; i < k; ++i)
            countingArr[i] += countingArr[i-1];
        for(i = arr_length - 1; i > -1; --i)
            arr[--countingArr[(shadowArr[i] - minValue) >> power]] = shadowArr[i];
    }
    else
        for(i = 0; i < arr_length; ++i)
            arr[i] = shadowArr[i];

    free(shadowArr);
    free(countingArr);
}

/**
 * Performs QR Sort on the given array. This implementation utilizes bitwise operations to compute the quotient and
 * remainder values and assumes that the minimum value in the array is zero.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param power we compute the divisor by raising 2 to this value
 */
void qr_sort_power_2_min_value_zero(int arr[], int n, int power)
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