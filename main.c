/**
 * @author: Randolph Bushman
 * @date: 01/12/2024
 *
 * This program is designed to test and compare the performance of various sorting algorithms. It measures and records
 * the time taken by each algorithm to sort arrays of different sizes, and outputs these measurements in CSV format for
 * further analysis.
 *
 * --- Configurations for QR Sort Paper ---
 *
 * Figure 5:
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 50000 --divisor 0 --figure_mode 5 --csv_file B:\c_projects\sort_tester\output_files\fig_5_a.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 500000 --divisor 0 --figure_mode 5 --csv_file B:\c_projects\sort_tester\output_files\fig_5_b.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 5000000 --divisor 0 --figure_mode 5 --csv_file B:\c_projects\sort_tester\output_files\fig_5_c.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 50000000 --divisor 0 --figure_mode 5 --csv_file B:\c_projects\sort_tester\output_files\fig_5_d.csv
 *
 * Figure 6:
 * --num_trials 10 --initial_length 10 --length_increment 10 --max_length 2000 --min_arr_value 0 --max_arr_value 150000000 --divisor 0 --figure_mode 6 --csv_file B:\c_projects\sort_tester\output_files\fig_6.csv
 *
 * Figure 7:
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 50000 --divisor 16 --figure_mode 7 --csv_file B:\c_projects\sort_tester\output_files\fig_7_a.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 500000 --divisor 16 --figure_mode 7 --csv_file B:\c_projects\sort_tester\output_files\fig_7_b.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 5000000 --divisor 16 --figure_mode 7 --csv_file B:\c_projects\sort_tester\output_files\fig_7_c.csv
 * --num_trials 10 --initial_length 10000 --length_increment 10000 --max_length 1000000 --min_arr_value 0 --max_arr_value 50000000 --divisor 16 --figure_mode 7 --csv_file B:\c_projects\sort_tester\output_files\fig_7_d.csv
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sort_utils.h"
#include "sort.h"
#include <string.h>
#define MAX_ALGORITHM_COUNT 24  // Maximum number of sorting algorithms that can be tested

SortFunc sorting_algorithms[MAX_ALGORITHM_COUNT]; // Array of sorting algorithm functions
SortArgs sorting_args[MAX_ALGORITHM_COUNT];       // Array of arguments for each sorting algorithm
unsigned long long int algorithm_times[MAX_ALGORITHM_COUNT] = {0}; // Execution times for algorithms
char csv_column_str[1024] = "Array Length";       // CSV column header string
int algorithm_count = 0;                          // Count of sorting algorithms added

/**
 * Parses command line arguments to set sorting test parameters.
 *
 * @param argc number of command line arguments
 * @param argv array of command line argument strings
 * @param num_trials pointer to the number of trials
 * @param initial_length pointer to the initial array length
 * @param length_increment pointer to the array length increment
 * @param max_length pointer to the maximum array length
 * @param min_arr_value pointer to the minimum array value
 * @param max_arr_value pointer to the maximum array value
 * @param divisor pointer to the divisor for sorting algorithms
 * @param csv_file pointer to the CSV file name string
 */
void parse_arguments(int argc, char *argv[], int *num_trials, int *initial_length, int *length_increment, int *max_length, int *min_arr_value, int *max_arr_value, int *divisor, int *figure_mode, char **csv_file) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--num_trials")) {
            *num_trials = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--initial_length")) {
            *initial_length = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--length_increment")) {
            *length_increment = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--max_length")) {
            *max_length = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--min_arr_value")) {
            *min_arr_value = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--max_arr_value")) {
            *max_arr_value = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--divisor")) {
            *divisor = atoi(argv[++i]);}
        else if (!strcmp(argv[i], "--figure_mode")) {
            *figure_mode = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--csv_file")) {
            *csv_file = argv[++i];
        }
    }
}

/**
 * Adds a sorting algorithm to the global arrays for testing.
 * @param name the name of the sorting algorithm.
 * @param func the function pointer to the sorting algorithm.
 * @param args the arguments that the algorithm takes.
 */
void add_sorting_method(const char* name, const SortFunc func, const SortArgs args) {
    sprintf(csv_column_str, "%s, %s", csv_column_str, name);
    sorting_args[algorithm_count] = args;
    sorting_algorithms[algorithm_count++] = func;
}

int main(int argc, char *argv[]) {
    srand(0);

    // Trial parameters
    int num_trials = 10;                // Number of trials per array length
    int initial_length = 1000;          // Initial (smallest) array size to be tested
    int length_increment = 10000;       // Increment for the next array size after each trial
    int max_length = 1000000;           // Maximum array size to be tested
    int min_arr_value = 0;              // Minimum value in the arrays
    int max_arr_value = 50000000;       // Maximum value in the arrays
    int divisor = 16;                   // Common divisor for QR Sort optimizations (should be a power of 2)
    int figure_mode = 5;                // The number figure_mode to generate
    char *csv_file = "output.csv";      // Output CSV file

    // Parse command line arguments
    parse_arguments(argc, argv, &num_trials, &initial_length, &length_increment, &max_length, &min_arr_value, &max_arr_value, &divisor, &figure_mode, &csv_file);

    // Open the CSV file for writing
    FILE *file = fopen(csv_file, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    printf("Output file: %s\n", csv_file);

    // Add new sorting algorithms to be tested
    if (figure_mode == 5) {
        add_sorting_method("Merge Sort", merge_sort, (SortArgs) {});
        add_sorting_method("Quicksort", quicksort, (SortArgs) {});
        add_sorting_method("Counting Sort", counting_sort, (SortArgs) {});
        add_sorting_method("Radix Sort", radix_sort, (SortArgs) {});
        add_sorting_method("QR Sort", qr_sort, (SortArgs) {});
    } else if (figure_mode == 6) {
        add_sorting_method("Radix Sort", radix_sort, (SortArgs) {});
        add_sorting_method("QR Sort", qr_sort, (SortArgs) {});
    } else if (figure_mode == 7) {
        add_sorting_method("QR Sort", qr_sort, (SortArgs) {});
        add_sorting_method("QR Sort Set Divisor", qr_sort, (SortArgs) {.divisor = divisor});
        add_sorting_method("QR Sort Min Value Zero", qr_sort, (SortArgs) {.divisor = divisor, .min_value_zero = 1});
        add_sorting_method("QR Sort Bitwise", qr_sort, (SortArgs) {.divisor = divisor, .bitwise_ops = 1});
        add_sorting_method("QR Sort Bitwise Min Value Zero", qr_sort, (SortArgs) {.divisor = divisor, .bitwise_ops = 1, .min_value_zero = 1});
    }

    // Print csv column headers
    fprintf(file, "sep=,\n");
    fprintf(file, "%s\n", csv_column_str);
    printf("%s\n", csv_column_str);

    // Allocate memory for arrays
    int *arr = malloc(max_length * sizeof(int));      // Array to sort
    int *copy_arr = malloc(max_length * sizeof(int)); // Copy of the array for sorting

    // Run sorting tests
    for (int arr_length = initial_length; arr_length <= max_length; arr_length += length_increment) {
        lin_space(arr, arr_length, min_arr_value, max_arr_value); // Populate arr with linearly spaced values

        // Perform trials for each algorithm
        for (int i = 0; i < num_trials; ++i) {
            shuffle(arr, arr_length);  // Shuffle the array for each trial

            // Test each algorithm
            for (int j = 0; j < algorithm_count; ++j) {
                clone_array(arr, copy_arr, arr_length);  // Create a copy of the array for sorting
                algorithm_times[j] += (*sorting_algorithms[j])(copy_arr, arr_length, sorting_args[j]);
            }
        }

        // Print the average time for each algorithm trial in CSV format
        fprintf(file, "%d", arr_length);
        printf("%d", arr_length);
        for (int i = 0; i < algorithm_count; ++i) {
            fprintf(file, ", %llu", 1000 * algorithm_times[i] / num_trials);
            printf( ", %llu", 1000 * algorithm_times[i] / num_trials);
            algorithm_times[i] = 0;  // Reset time for the next trial
        }
        fprintf(file, "\n");
        printf("\n");
    }

    fclose(file);
    free(arr);
    free(copy_arr);
    return 0;
}
