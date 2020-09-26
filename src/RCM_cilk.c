/*
* @file        RCM_cilk.c
* @reference   https://www.geeksforgeeks.org/reverse-cuthill-mckee-algorithm/
* @author      athanasps <athanasps@ece.auth.gr>
*              Thanos Paraskevas
*
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#include "myQuickSort.h"
#include "queue.h"

// Utility function to find degree of each node
// I  --> rows recorded at .mtx file
// J  --> columns recorded at .mtx file
// nz --> nonzeros in .mtx file
// totalDegrees --> the sum of all degrees (pointer in order to be written)
int *findDegrees(int *I, int *J, int nz, int M, int *totalDegrees){
  int *degrees = (int *)calloc(M, sizeof(int));
  *totalDegrees = 0;

  // for every record
  for(int i = 0; i < nz; i++){
    // Omit self loops
    if(I[i] != J[i]){
      degrees[I[i]]++;
      degrees[J[i]]++;
      *totalDegrees += 2;
    }
  }

  return degrees;
}

// Utility function to find index of minimum degree node
// that has not yet been visited
// degrees --> degrees of all nodes
// visited --> logical array that has true on all previously visited nodes
// M       --> dimension of sparse matrix
int findMinDegreeNode(int *degrees, bool *visited, int M){
  // Find first node that has not been visited
  // to be the starting minimum index
  int minIndex = -1;
  for(int i = 0; i < M; i++){
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
  for(int i = minIndex + 1; i < M; i++){
    if(degrees[i] < degrees[minIndex] && !visited[i]){
      minIndex = i;
    }
  }

  return minIndex;
}

// Utility function to find neighbors of each node
// I  --> rows recorded at .mtx file
// J  --> columns recorded at .mtx file
// nz --> nonzeros in .mtx file
// M  --> dimension of sparse matrix
// degrees      --> degree of each node
// totalDegrees --> the sum of all degrees
int **findNeighbors(int *I, int *J, int nz, int M, int *degrees, int totalDegrees){
  // Initialize neighbors matrix
  // row i will contain the neighbors of node i
  int **neighbors = (int **)malloc(M * sizeof(int *));
  neighbors[0] = (int *)malloc(totalDegrees * sizeof(int));
  // row i will contain degrees[i] elements
  for(int i = 1; i < M; i++){
    neighbors[i] = neighbors[i-1] + degrees[i-1];
  }

  // Keep track of current neighbors added for each node
  int *neighborsCount = (int *)calloc(M, sizeof(int));

  // for every record
  for(int i = 0; i < nz; i++){
    // Omit self loops
    if(I[i] != J[i]){
      neighbors[ J[i] ][ neighborsCount[J[i]] ] = I[i];
      neighbors[ I[i] ][ neighborsCount[I[i]] ] = J[i];
      neighborsCount[J[i]]++;
      neighborsCount[I[i]]++;
    }
  }

  free(neighborsCount);

  return neighbors;
}

// Reverse Cuthill Mckee algorithm implementation
// I  --> rows recorded at .mtx file
// J  --> columns recorded at .mtx file
// nz --> nonzeros in .mtx file
// M  --> dimension of sparse matrix
int *ReverseCuthillMckee(int *I, int *J, int nz, int M){
  // Find degree for each node
  int totalDegrees;
  int *degrees = findDegrees(I, J, nz, M, &totalDegrees);

  // Initialize queue
  queue *Q = queueInit(M);
  if(Q ==  NULL){
    fprintf(stderr, "Queue Init failed.\n");
    exit(EXIT_FAILURE);
  }

  // Initialize permutation array
  int *R = (int *)malloc(M * sizeof(int));
  // Initialize current permutation index
  int Rcount = 0;

  // Initialize array which keeps track of visited nodes
  bool *visited = (bool *)calloc(M, sizeof(bool));

  // Find neighbors for each node
  int **neighbors = findNeighbors(I, J, nz, M, degrees, totalDegrees);

  // Loop until every node has been added to permutation array R
  while(Rcount < M){
    // Find minimum degree node
    int minIndex = findMinDegreeNode(degrees, visited, M);

    // Add that item to Q
    node newNode;
    newNode.num = minIndex;
    newNode.degree = degrees[minIndex];
    queueAdd(Q, newNode);
    // and mark it as visited
    visited[minIndex] = true;

    while(!Q->empty){
      // Extract element from Q
      node qfront;
      queueDel(Q, &qfront);

      // Keep track of start index of the new elements
      // to be sorted later
      int newElementsStartIndex = Q->tail;

      // Find all non-visited neighbors of extracted element and add them to Q
      for(int i = 0; i < degrees[qfront.num]; i++){
        if(!visited[neighbors[qfront.num][i]]){
          newNode.num = neighbors[qfront.num][i];
          newNode.degree = degrees[neighbors[qfront.num][i]];
          visited[neighbors[qfront.num][i]] = true;
          queueAdd(Q, newNode);
        }
      }

      // Sort new elements of queue in ascending order of degree
      quickSort(Q->buf, newElementsStartIndex, Q->tail - 1);

      // Add extracted element to R
      R[Rcount] = qfront.num;
      Rcount++;
    }
  }

  free(neighbors[0]);
  free(neighbors);
  free(degrees);
  free(visited);
  queueDelete(Q);

  // Reverse permutation array
  cilk_for(int i = 0; i < M/2; i++){
    int temp = R[M-1-i];
    R[M-1-i] = R[i];
    R[i] = temp;
  }

  return R;
}
