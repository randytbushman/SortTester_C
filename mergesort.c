//
// Created by randy on 10/18/2022.
//
#include "mergesort.h"
#include <stdlib.h>

void merge_sort(int *arr, int n)
{
    int mid = n >> 1;
    int *shadowArr = malloc(n * sizeof (int));
    merge_sort_recursive(arr, shadowArr, 0, mid);
    merge_sort_recursive(arr, shadowArr, mid + 1, n - 1);
    merge(arr, shadowArr, 0, mid, n - 1);
    free(shadowArr);
}

void merge_sort_recursive(int *arr, int *shadowArr, int s, int e)
{
    int mid = (s + e) >> 1;
    if(s >= e)
        return;
    merge_sort_recursive(arr, shadowArr, s, mid);
    merge_sort_recursive(arr, shadowArr, mid+1, e);
    merge(arr, shadowArr, s, mid, e);
}

void merge(int *arr, int *shadowArr, int s, int mid, int e)
{
    int i = s;
    int j = mid + 1;
    int k = 0;
    while(i <= mid && j <= e)
        if(arr[i] < arr[j])
            shadowArr[k++] = arr[i++];
        else
            shadowArr[k++] = arr[j++];

    while(i <= mid)
        shadowArr[k++] = arr[i++];

    while(j <= e)
        shadowArr[k++] = arr[j++];

    for(int x = e; x >= s; --x)
        arr[x] = shadowArr[--k];
}