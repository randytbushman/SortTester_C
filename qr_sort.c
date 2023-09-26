/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>

static unsigned long long int instruction_counter = 0; // # of comparisons + array accesses


/**
 * Performs QR Sort on the given array with divisor arr_length.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 */
unsigned long long int qr_sort_divisor_n(int arr[], int arr_length) {
    qr_sort(arr, arr_length, arr_length);
    return instruction_counter;
}

/**
 * Performs QR Sort on the given array with the given divisor.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param divisor the divisor used to determine remainder and quotient counting array sizes
 */
unsigned long long int qr_sort(int arr[], int arr_length, int divisor)
{
    int i;
    int minValue = arr[0], maxValue = arr[0];
    instruction_counter = 2;

    for(i = 1; i < arr_length && ++instruction_counter; ++i) {
        ++instruction_counter;
        if (arr[i] < minValue && (instruction_counter += 2))
            minValue = arr[i];
        else if (arr[i] > maxValue && (instruction_counter += 2))
            maxValue = arr[i];
    }

    int maxQuotient = ((maxValue - minValue) / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    ++instruction_counter;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length && ++instruction_counter; ++i) {
        ++countingArr[(arr[i] - minValue) % divisor];
        instruction_counter += 2;
    }
    for(i = 1; i < divisor && ++instruction_counter; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
        shadowArr[--countingArr[(arr[i] - minValue) % divisor]] = arr[i];
        instruction_counter += 4;
    }

    if(maxQuotient > 1 && ++instruction_counter) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor && ++instruction_counter; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }

        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length && ++instruction_counter; ++i) {
            ++countingArr[(shadowArr[i] - minValue) / divisor];
            instruction_counter += 2;
        }

        for(i = 1; i < k && ++instruction_counter; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
            arr[--countingArr[(shadowArr[i] - minValue) / divisor]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else {
        for (i = 0; i < arr_length && ++instruction_counter; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }
    }
    free(shadowArr);
    free(countingArr);

    return instruction_counter;
}

/**
 * Performs QR Sort on the given array with the given divisor. This implementation assumes that the minimum value in the
 * array is zero.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param divisor the divisor used to determine remainder and quotient counting array sizes
 */
unsigned long long int qr_sort_min_value_zero(int arr[], int arr_length, int divisor)
{
    int i;
    int maxValue = arr[0];
    instruction_counter = 1;

    for(i = 1; i < arr_length && ++instruction_counter; ++i)
        if(arr[i] > maxValue && (instruction_counter += 2)) {
            maxValue = arr[i];
            ++instruction_counter;
        }

    int maxQuotient = (maxValue / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    ++instruction_counter;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length && ++instruction_counter; ++i) {
        ++countingArr[arr[i] % divisor];
        instruction_counter += 2;
    }
    for(i = 1; i < divisor && ++instruction_counter; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
        shadowArr[--countingArr[arr[i] % divisor]] = arr[i];
        instruction_counter += 4;
    }

    if(maxQuotient > 1 && ++instruction_counter) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor && ++instruction_counter; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length && ++instruction_counter; ++i) {
            ++countingArr[shadowArr[i] / divisor];
            instruction_counter += 2;
        }
        for(i = 1; i < k && ++instruction_counter; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
            arr[--countingArr[shadowArr[i] / divisor]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else {
        for (i = 0; i < arr_length && ++instruction_counter; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }
    }
    free(shadowArr);
    free(countingArr);

    return instruction_counter;
}

/**
 * Performs QR Sort on the given array. This implementation utilizes bitwise operations to compute the quotient and
 * remainder values.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param power we compute the divisor by raising 2 to this value
 */
unsigned long long int qr_sort_power_2(int arr[], int arr_length, int power)
{
    int i;
    int divisor = 1 << power;
    instruction_counter = 2;

    // Find the minimum and maximum values
    int minValue = arr[0], maxValue = arr[0];
    for(i = 1; i < arr_length && ++instruction_counter; ++i) {
        ++instruction_counter;
        if (arr[i] < minValue && (instruction_counter += 2))
            minValue = arr[i];
        else if (arr[i] > maxValue && (instruction_counter += 2))
            maxValue = arr[i];
    }

    ++instruction_counter;
    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < arr_length && ++instruction_counter; ++i) {
        ++countingArr[(arr[i] - minValue) & (divisor - 1)];
        instruction_counter += 2;
    }
    for(i = 1; i < divisor && ++instruction_counter; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
        shadowArr[--countingArr[(arr[i] - minValue) & (divisor - 1)]] = arr[i];
        instruction_counter += 4;
    }

    if(maxQuotient > 1 && ++instruction_counter) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor && ++instruction_counter; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; i < arr_length && ++instruction_counter; ++i) {
            ++countingArr[(shadowArr[i] - minValue) >> power];
            instruction_counter += 2;
        }
        for(i = 1; i < k && ++instruction_counter; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; i > -1 && ++instruction_counter; --i) {
            arr[--countingArr[(shadowArr[i] - minValue) >> power]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else
        for(i = 0; i < arr_length && ++instruction_counter; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }

    free(shadowArr);
    free(countingArr);

    return instruction_counter;
}

/**
 * Performs QR Sort on the given array. This implementation utilizes bitwise operations to compute the quotient and
 * remainder values and assumes that the minimum value in the array is zero.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param power we compute the divisor by raising 2 to this value
 */
unsigned long long int qr_sort_power_2_min_value_zero(int arr[], int n, int power)
{
    int i;
    int divisor = 1 << power;

    // Find the minimum and maximum values
    instruction_counter = 1;
    int maxValue = arr[0];
    for(i = 1; i < n && ++instruction_counter; ++i)
        if(arr[i] > maxValue && (instruction_counter += 2)) {
            ++instruction_counter;
            maxValue = arr[i];
        }

    ++instruction_counter;
    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(n * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; i < n && ++instruction_counter; ++i) {
        ++countingArr[arr[i] & (divisor - 1)];
        instruction_counter += 2;
    }
    for(i = 1; i < divisor && ++instruction_counter; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = n - 1; i > -1 && ++instruction_counter; --i) {
        shadowArr[--countingArr[arr[i] & (divisor - 1)]] = arr[i];
        instruction_counter += 4;
    }

    if(maxQuotient > 1 && ++instruction_counter) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; i < divisor && ++instruction_counter; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; i < n && ++instruction_counter; ++i) {
            ++countingArr[shadowArr[i] >> power];
            instruction_counter += 2;
        }
        for(i = 1; i < k && ++instruction_counter; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = n - 1; i > -1 && ++instruction_counter; --i) {
            arr[--countingArr[shadowArr[i] >> power]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else
        for(i = 0; i < n && ++instruction_counter; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }

    free(shadowArr);
    free(countingArr);

    return instruction_counter;
}