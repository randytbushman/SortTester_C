/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"
#include <stdlib.h>
#include <math.h>

static unsigned long long int instruction_counter = 0; // # of comparisons + array accesses


unsigned int compute_srt_operations(unsigned int n, unsigned int m) {
    // Calculate maximum bit width of n and m using logarithms
    unsigned int max_n_m = (n > m) ? n : m;
    unsigned int max_bit_width = (max_n_m > 0) ? (int)floor(log2(max_n_m)) + 1 : 1;  // Ensure at least 1 iteration

    // Maximum operations per iteration
    const unsigned int OPERATIONS_PER_ITERATION = 6;
    return OPERATIONS_PER_ITERATION * max_bit_width;
}


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

    for(i = 1; ++instruction_counter && i < arr_length; ++i) {
        ++instruction_counter;
        if ((instruction_counter += 2) && arr[i] < minValue)
            minValue = arr[i];
        else if ((instruction_counter += 2) && arr[i] > maxValue)
            maxValue = arr[i];
    }

    unsigned long long int div_counter = instruction_counter; // # of comparisons + array accesses
    for (i = 0; i < arr_length; ++i) {
        div_counter += compute_srt_operations(arr[i], divisor);
    }

    int maxQuotient = ((maxValue - minValue) / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    ++instruction_counter;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; ++instruction_counter && i < arr_length; ++i) {
        ++countingArr[(arr[i] - minValue) % divisor];
        instruction_counter += 2;
    }
    for(i = 1; ++instruction_counter && i < divisor; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
        shadowArr[--countingArr[(arr[i] - minValue) % divisor]] = arr[i];
        instruction_counter += 4;
    }

    if(++instruction_counter && maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; ++instruction_counter && i < divisor; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }

        // Perform Counting Sort on quotient values
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            ++countingArr[(shadowArr[i] - minValue) / divisor];
            instruction_counter += 2;
        }

        for(i = 1; ++instruction_counter && i < k; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
            arr[--countingArr[(shadowArr[i] - minValue) / divisor]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else {
        for (i = 0; ++instruction_counter && i < arr_length; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }
    }
    free(shadowArr);
    free(countingArr);

    return div_counter;
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

    for (i = 1; ++instruction_counter && i < arr_length; ++i)
        if ((instruction_counter += 2) && arr[i] > maxValue) {
            maxValue = arr[i];
            ++instruction_counter;
        }

    unsigned long long int div_counter = instruction_counter; // # of comparisons + array accesses
    for (i = 0; i < arr_length; ++i) {
        div_counter += compute_srt_operations(arr[i], divisor);
    }

    int maxQuotient = (maxValue / divisor) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    ++instruction_counter;

    // Shadow array that is meant for temporary storage for all values
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; ++instruction_counter && i < arr_length; ++i) {
        ++countingArr[arr[i] % divisor];
        instruction_counter += 2;
    }
    for(i = 1; ++instruction_counter && i < divisor; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
        shadowArr[--countingArr[arr[i] % divisor]] = arr[i];
        instruction_counter += 4;
    }

    if(++instruction_counter && maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; ++instruction_counter && i < divisor; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            ++countingArr[shadowArr[i] / divisor];
            instruction_counter += 2;
        }
        for(i = 1; ++instruction_counter && i < k; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
            arr[--countingArr[shadowArr[i] / divisor]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else {
        for (i = 0; ++instruction_counter && i < arr_length; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }
    }
    free(shadowArr);
    free(countingArr);

    return div_counter;
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
    for(i = 1; ++instruction_counter && i < arr_length; ++i) {
        ++instruction_counter;
        if ((instruction_counter += 2) && arr[i] < minValue)
            minValue = arr[i];
        else if ((instruction_counter += 2) && arr[i] > maxValue)
            maxValue = arr[i];
    }
    unsigned long long int div_counter = instruction_counter; // # of comparisons + array accesses
    for (i = 0; i < arr_length; ++i) {
        div_counter += 4;
    }

    ++instruction_counter;
    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));

    // Perform Counting Sort with remainder values
    for(i = 0; ++instruction_counter && i < arr_length; ++i) {
        ++countingArr[(arr[i] - minValue) & (divisor - 1)];
        instruction_counter += 2;
    }
    for(i = 1; ++instruction_counter && i < divisor; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
        shadowArr[--countingArr[(arr[i] - minValue) & (divisor - 1)]] = arr[i];
        instruction_counter += 4;
    }

    if(++instruction_counter && maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; ++instruction_counter && i < divisor; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            ++countingArr[(shadowArr[i] - minValue) >> power];
            instruction_counter += 2;
        }
        for(i = 1; ++instruction_counter && i < k; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
            arr[--countingArr[(shadowArr[i] - minValue) >> power]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }

    free(shadowArr);
    free(countingArr);

    return div_counter;

    //return instruction_counter;
}

/**
 * Performs QR Sort on the given array. This implementation utilizes bitwise operations to compute the quotient and
 * remainder values and assumes that the minimum value in the array is zero.
 * @param arr the array to be sorted
 * @param arr_length the length of the array
 * @param power we compute the divisor by raising 2 to this value
 */
unsigned long long int qr_sort_power_2_min_value_zero(int arr[], int arr_length, int power)
{
    int i;
    int divisor = 1 << power;



    // Find the minimum and maximum values
    instruction_counter = 1;
    int maxValue = arr[0];
    for(i = 1; ++instruction_counter && i < arr_length; ++i)
        if((instruction_counter += 2) && arr[i] > maxValue) {
            ++instruction_counter;
            maxValue = arr[i];
        }

    unsigned long long int div_counter = instruction_counter; // # of comparisons + array accesses


    ++instruction_counter;
    int maxQuotient = (maxValue >> power) + 1;
    int k = (divisor > maxQuotient) ? divisor : maxQuotient;
    int *shadowArr = malloc(arr_length * sizeof (int));
    int *countingArr = calloc(k, sizeof(int));
    div_counter++;

    // Perform Counting Sort with remainder values
    for(i = 0; ++instruction_counter && i < arr_length; ++i) {
        ++countingArr[arr[i] & (divisor - 1)];
        instruction_counter += 2;
    }
    for(i = 1; ++instruction_counter && i < divisor; ++i) {
        countingArr[i] += countingArr[i - 1];
        instruction_counter += 2;
    }
    for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
        shadowArr[--countingArr[arr[i] & (divisor - 1)]] = arr[i];
        instruction_counter += 4;
    }

    if(++instruction_counter && maxQuotient > 1) {
        // Reset the values to reuse counting array for sorting quotients
        for(i = 0; ++instruction_counter && i < divisor; ++i) {
            countingArr[i] = 0;
            ++instruction_counter;
        }
        // Perform Counting Sort on quotient values
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            ++countingArr[shadowArr[i] >> power];
            instruction_counter += 2;
        }
        for(i = 1; ++instruction_counter && i < k; ++i) {
            countingArr[i] += countingArr[i - 1];
            instruction_counter += 2;
        }
        for(i = arr_length - 1; ++instruction_counter && i > -1; --i) {
            arr[--countingArr[shadowArr[i] >> power]] = shadowArr[i];
            instruction_counter += 4;
        }
    }
    else
        for(i = 0; ++instruction_counter && i < arr_length; ++i) {
            arr[i] = shadowArr[i];
            instruction_counter += 2;
        }

    free(shadowArr);
    free(countingArr);


    for (i = 0; i < arr_length; ++i) {
        div_counter += 4;
    }

    return div_counter;
    //return instruction_counter;
}