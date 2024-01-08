/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */

#ifndef SORT_TESTER_SORT_UTILS_H
#define SORT_TESTER_SORT_UTILS_H

void clone_array(const int[], int[], int);
int generate_random_number(int, int);
int is_sorted_ascending(const int[], int);
void lin_space(int[], int, int, int);
void print_int_array(int[], int);
void shuffle(int[], int);
void find_min_max(const int[], int, int*, int*, unsigned long long int*);
void find_max(const int[], int, int*, unsigned long long int*);
void swap(int[], int, int, unsigned long long int*);

typedef struct {
    int radix;  // Used in Radix Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length.
    int divisor;  // Used in QR Sort and specifies the divisor to use. If the user does not provide a positive value, default to array length
    int min_value_zero;  // Flag indicating if the minimum value in the array is zero, optimizing Radix Sort and QR Sort.
    int bitwise_ops;  // Flag indicating if bitwise operations should be used, optimizing Radix Sort and QR Sort.
} SortArgs;

typedef unsigned long long int (*SortFunc)(int[], int, SortArgs);

#endif //SORT_TESTER_SORT_UTILS_H
