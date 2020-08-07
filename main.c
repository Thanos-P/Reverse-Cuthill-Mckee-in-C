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
  bool A[9] = {1,0,0,0,1,1,0,1,1};
  int n = 3;

  // Find degree for each row
  int *degrees = findDegrees(A,n);

  queue *Q = queueInit();
  if(Q ==  NULL){
    fprintf(stderr, "Queue Init failed.\n");
    exit(1);
  }

  int *R = (int *)malloc(n * sizeof(int));

  // for(int i = 0; i < n; i++){
  //   printf("%d\n", degrees[i]);
  // }

  // Find minimum degree row
  int minIndex = 0;
  for(int i = 1; i < n; i++){
    if(degrees[i] < degrees[minIndex]){
      minIndex = i;
    }
  }

  // Add that item to Q
  queueAdd(Q, minIndex);

  free(degrees);
  free(R);
  queueDelete(Q);

  return 0;
}
