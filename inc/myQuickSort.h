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
void swap(node* a, node* b)
{
    node t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot
*/
int partition (node *arr, int low, int high)
{
    int pivot = arr[high].degree;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j].degree < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
   arr  --> Array to be sorted,
   low  --> Starting index,
   high --> Ending index
*/
void quickSort(node *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif /* MYQUICKSORT_H */
