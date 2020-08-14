/**
 * @file   main.c
 * @author athanasps <athanasps@ece.auth.gr>
 *         Thanos Paraskevas
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#include "queue.h"
#define A(i,j)  *(A + (i) * n + (j))

typedef struct {
  int row;
  int degree;
} rowStruct;

// Function to find degree of each row of n-by-n sparse matrix A
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


int main (){
  // Initialize sparse matrix
  bool A[9] = {1,0,0,0,1,1,0,1,1};
  int n = 3;

  // Find degree for each row
  int *degrees = findDegrees(A,n);

  // Initialize queue
  queue *Q = queueInit();
  if(Q ==  NULL){
    fprintf(stderr, "Queue Init failed.\n");
    exit(1);
  }

  int *R = (int *)malloc(n * sizeof(int));
  int Rcount = 0;

  // Initialize notVisited elements
  rowStruct *notVisited = (rowStruct *)malloc(n * sizeof(rowStruct));
  int notVisitedSize = n;
  for(int i = 0; i < n; i++){
    notVisited[i].row = i;
    notVisited[i].degree = degrees[i];
  }

  // for(int i = 0; i < n; i++){
  //   printf("%d\n", degrees[i]);
  // }

  while(notVisitedSize > 0){
    // Find minimum degree row
    int minIndex = 0;
    for(int i = 1; i < notVisitedSize; i++){
      if(notVisited[i].row < notVisited[minIndex].row){
        minIndex = i;
      }
    }

    // Add that item to Q
    queueAdd(Q, notVisited[minIndex].row);

    // Erase

    while(!Q.empty){
      
    }

  }

  free(degrees);
  free(R);
  free(notVisited);
  queueDelete(Q);

  return 0;
}
