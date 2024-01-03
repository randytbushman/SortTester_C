/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */

#ifndef SORT_TESTER_ARRAY_UTILS_H
#define SORT_TESTER_ARRAY_UTILS_H

void clone_array(const int[], int[], int);
int generate_random_number(int, int);
int is_sorted_ascending(const int[], int);
void lin_space(int[], int, int, int);
void print_int_array(int[], int);
void shuffle(int[], int);
void find_min_max(const int[], int, int*, int*, unsigned long long int*);
void find_max(const int[], int, int*, unsigned long long int*);

#endif //SORT_TESTER_ARRAY_UTILS_H
