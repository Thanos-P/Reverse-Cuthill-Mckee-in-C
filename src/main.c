/*
 * @file   main.c
 * @author athanasps <athanasps@ece.auth.gr>
 *         Thanos Paraskevas
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#define A(i,j)  *(A + (i) * n + (j))

int *ReverseCuthillMckee(bool *A, const int n);

int main (){
  // Initialize adjacency matrix
  bool A[] = {
        1, 1, 0, 0, 0, 0, 1, 0, 1, 0,
        1, 1, 0, 0, 1, 0, 1, 0, 0, 1,
        0, 0, 1, 0, 1, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 1, 0, 0, 0, 1,
        0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 0, 1, 0, 0, 0, 1, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 1
  };
  const int n = 10;

  // Time variables
  struct timeval startwtime, endwtime;
  double totaltime;

  gettimeofday(&startwtime, NULL);
  int *R = ReverseCuthillMckee(A,n);
  gettimeofday(&endwtime, NULL);

  totaltime = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
            + endwtime.tv_sec - startwtime.tv_sec);

  // print results
  printf("\nPermutation array: ");
  for(int i = 0; i < n; i++){
    printf("%d ", R[i]);
  }
  printf("\n");

  printf("\nInitial array\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(A(i,j))
        printf("■ ");
      else
        printf("□ ");
    }
    printf("\n");
  }

  printf("\nPermutated array\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(A(R[i],R[j]))
        printf("■ ");
      else
        printf("□ ");
    }
    printf("\n");
  }

  printf("\ntotal time: %f\n", totaltime);

  free(R);

  return 0;
}
