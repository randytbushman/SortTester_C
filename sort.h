/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */

#ifndef SORT_TESTER_SORT_H
#define SORT_TESTER_SORT_H


unsigned long long int quicksort(int[], int);
unsigned long long int merge_sort(int[], int);
void counting_key_sort(int[], int[], const int[], int[], int, int, int, unsigned long long int*);
unsigned long long int counting_sort(int[], int, int);
unsigned long long int qr_sort(int[], int, int, int, int);
unsigned long long int radix_sort(int[], int, int, int, int);


#endif //SORT_TESTER_SORT_H
