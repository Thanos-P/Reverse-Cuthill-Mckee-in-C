/*
 * @file        RCM_sequential.h
 * @reference   https://www.geeksforgeeks.org/reverse-cuthill-mckee-algorithm/
 * @author      athanasps <athanasps@ece.auth.gr>
 *              Thanos Paraskevas
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "myQuickSort.h"

#define A(i,j)  *(A + (i) * n + (j))

// Utility function to find degree of each node of n-by-n adjacency matrix A
int *findDegrees(bool *A, int n){
  int *degrees = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++){
    double count = 0;

    for (int j = 0; j < n; j++){
        count += (int) A(i,j);
    }

    degrees[i] = count;
  }

  return degrees;
}

/* Reverse Cuthill Mckee algorithm implementation
  A --> n-by-n adjacency matrix
  n --> dimension of A
*/
int *ReverseCuthillMckee(bool *A, const int n){
  // Find degree for each node
  int *degrees = findDegrees(A,n);

  // Initialize queue
  queue *Q = queueInit(n);
  if(Q ==  NULL){
    fprintf(stderr, "Queue Init failed.\n");
    exit(EXIT_FAILURE);
  }

  // Initialize node elements
  node *nodes = (node *)malloc(n * sizeof(node));
  for(int i = 0; i < n; i++){
    nodes[i].num = i;
    nodes[i].degree = degrees[i];
  }

  free(degrees);

  // Initialize permutation array
  int *R = (int *)malloc(n * sizeof(int));
  // Initialize current permutation index
  int Rcount = 0;

  // Initialize array which keeps track of visited nodes
  bool *visited = (bool *)calloc(n, sizeof(bool));

  while(Rcount < n){
    // Find first node that has not been visited
    // to be the starting minimum index
    int minIndex = -1;
    for(int i = 0; i < n; i++){
      if(!visited[i]){
        minIndex = i;
        break;
      }
    }
    // Assert that an index has been found
    if(minIndex == -1){
      fprintf(stderr, "An error has occured.\n");
      exit(EXIT_FAILURE);
    }
    // Find minimum degree node index
    for(int i = minIndex + 1; i < n; i++){
      if(nodes[i].degree < nodes[minIndex].degree && !visited[i]){
        minIndex = i;
      }
    }

    // Add that item to Q
    queueAdd(Q, nodes[minIndex]);
    // and mark it as visited
    visited[minIndex] = true;

    while(!Q->empty){
      // Extract element from Q
      node qfront, newNode;
      queueDel(Q, &qfront);

      // Keep track of start index of the new elements
      // to be sorted later
      int newElementsStartIndex = Q->tail;

      // Find all non-visited neighboors of extracted element and add them to Q
      for(int i = 0; i < n; i++){
        if(i != qfront.num && A(qfront.num,i) && !visited[i]){
          newNode.num = i;
          newNode.degree = nodes[i].degree;
          visited[i] = true;
          queueAdd(Q, newNode);
        }
      }

      // Sort new elements of queue in ascending order of degree
      quickSort(Q->buf, newElementsStartIndex, Q->tail - 1);

      // Add element to R
      R[Rcount] = qfront.num;
      Rcount++;
    }
  }

  free(visited);
  free(nodes);
  queueDelete(Q);

  // Reverse permutation array
  for(int i = 0; i < n/2; i++){
    int temp = R[n-1-i];
    R[n-1-i] = R[i];
    R[i] = temp;
  }

  return R;
}
