/*
 * @file        myQuickSort.h
 * @reference   https://www.geeksforgeeks.org/quick-sort/
 * @author      athanasps <athanasps@ece.auth.gr>
 *              Thanos Paraskevas
 *
 */

#ifndef MYQUICKSORT_H
#define MYQUICKSORT_H

/* C implementation QuickSort */
#include <stdio.h>
#include "queue.h"

// A utility function to swap two elements
void swap(node* a, node* b);

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot
*/
int partition (node *arr, int low, int high);

/* The main function that implements QuickSort
   arr  --> Array to be sorted,
   low  --> Starting index,
   high --> Ending index
*/
void quickSort(node *arr, int low, int high);

#endif /* MYQUICKSORT_H */
