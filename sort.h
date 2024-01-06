/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */

#include "sort_utils.h"

#ifndef SORT_TESTER_SORT_H
#define SORT_TESTER_SORT_H


unsigned long long int quicksort(int[], int, SortArgs);
unsigned long long int merge_sort(int[], int, SortArgs);
void counting_key_sort(int[], int[], const int[], int[], int, int, int, unsigned long long int*);
unsigned long long int counting_sort(int[], int, SortArgs);
unsigned long long int qr_sort(int[], int, SortArgs);
unsigned long long int radix_sort(int[], int, SortArgs);


#endif //SORT_TESTER_SORT_H
