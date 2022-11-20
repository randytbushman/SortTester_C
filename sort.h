/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */

#ifndef SORT_TESTER_SORT_H
#define SORT_TESTER_SORT_H

int partition(int[], int, int);
void quicksort(int[], int);
void swap(int[], int, int);
void recursive_quicksort(int[], int, int);
void merge_sort(int[], int);
void merge_sort_recursive(int[], int[], int, int);
void merge(int[], int[], int, int, int);
void counting_sort(int[], int);
void qr_sort_divisor_n(int[], int);
void qr_sort(int[], int, int);
void qr_sort_min_value_zero(int[], int, int);
void qr_sort_power_2(int[], int, int);
void qr_sort_power_2_min_value_zero(int[], int, int);
void radix_sort(int[], int);


#endif //SORT_TESTER_SORT_H
