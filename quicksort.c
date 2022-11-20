/**
 * @author: Randolph Bushman
 * @date: 11/20/2022
 */
#include "sort.h"


void quicksort(int *arr, int n) {
    int p = partition(arr, 0, n - 1);
    recursive_quicksort(arr, 0, p-1);
    recursive_quicksort(arr, p+1,  n - 1);
}

void recursive_quicksort(int *arr, int start, int end)
{
    if (end - start < 1)
        return;
    int p = partition(arr, start, end);
    recursive_quicksort(arr, start, p - 1);
    recursive_quicksort(arr, p+1, end);
}

int partition(int *arr, int start, int end)
{
    int x = arr[end];
    int i = start - 1;
    for (int j = start; j < end; ++j)
        if(arr[j] < x)
            swap(arr, ++i, j);
    swap(arr, i + 1, end);
    return i + 1;
}

void swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}