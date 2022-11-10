//
// Created by randy on 11/7/2022.
//
#include "array_utils.h"
#include <stdio.h>
#include <stdlib.h>

void clone_array(const int *arr, int *clone_arr, int n) {
    for(int i = 0; i < n; ++i) {
        clone_arr[i] = arr[i];
    }
}

int generate_random_number(int min, int max) {
    return ((((rand() & 0xff)<<8 | (rand() & 0xff))<<8 | (rand() & 0xff))<<7 | (rand() & 127)) % (max + 1 - min) + min;
}

void lin_space(int *arr, int n, int min, int max) {
    arr[0] = min;
    arr[n - 1] = max;
    for(int i = 1; i < n - 1; ++i)
        arr[i] = (int) (i * ((max - min) / (double) n)) + arr[0];

}

void print_int_array(int *arr, int n) {
    printf("[%d", arr[0]);
    for (int i = 1; i < n; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
}

void shuffle(int *arr, int n) {
    int random_index;
    int temp;
    for(int i = n - 1; i > 0; --i) {
        random_index = generate_random_number(0, i + 1);
        temp = arr[random_index];
        arr[random_index] = arr[i];
        arr[i] = temp;
    }
}

