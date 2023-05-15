# SortTester_C: A C-based Sorting Algorithm Performance Evaluator

## Overview

SortTester_C is a C program designed to evaluate and compare the efficiency of various sorting algorithms. It achieves this by measuring the time taken to sort arrays of different lengths. The user is able to specify the minimum and maximum array lengths for testing. SortTester conducts numerous tests within the user-defined range, performing multiple trials for each test. The times taken from these trials are then averaged to provide a comprehensive analysis of each sorting algorithm's performance. The results are conveniently outputted to the standard console.

## User Guide

### Running SortTester_C

To utilize SortTester_C:

1. Compile the 'main.c' file.
2. Run the compiled program.

The main function in 'main.c' contains several parameters that can be fine-tuned to suit the user's requirements. These parameters include:

- Trial Count: The number of trials performed for each test.
- Array Length Increment: The change in length between each tested array.
- Minimum and Maximum Array Length: The bounds for the lengths of arrays tested.
- Minimum and Maximum Array Value: The range of values the array elements can have.

### Incorporating New Sorting Algorithms

To introduce and evaluate a new sorting algorithm, follow these steps:

1. Create a new C file for the sorting algorithm.
2. Append the 'sort.h' file with that algorithm's header.
3. Append the boilerplate code in 'main.c' to this file - this should be a function that returns a double and takes as parameters the array to be sorted, a copy of this array, and the known length of the array.

It's important to note that while more streamlined methods exist for integrating new sorting algorithms into the testing framework, these methods may not be as accessible to those unfamiliar with the C programming language.

After adding a new sorting algorithm, the user must also update the `csv_column_str` buffer size and the maximum algorithm count in the 'main.c' file.

The random seed generator value is set to a constant by default to allow for accurate reproduction and verification of tests. If different random values are needed for each test, this value can be changed.

Please note that while implementing these changes may require a certain level of familiarity with C programming, the process is straightforward and yields valuable insights into the performance of different sorting algorithms.