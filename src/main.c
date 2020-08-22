/*
 * @file        main.c
 * @reference   https://math.nist.gov/MatrixMarket/resources.html
 * @author      athanasps <athanasps@ece.auth.gr>
 *              Thanos Paraskevas
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#include "mmio.h"

#define A(i,j)  *(A + (i) * n + (j))

int *ReverseCuthillMckee(int *I, int *J, int nz, int M);

int main (int argc, char *argv[]){

  int ret_code;
  MM_typecode matcode;
  FILE *f;
  // M,N --> dimensions of sparse matrix
  // nz  --> nonzeros in .mtx file
  int M, N, nz;
  // I   --> rows recorded at .mtx file
  // J   --> columns recorded at .mtx file
  int *I, *J;
  // val --> values of edges recorded at .mtx file
  double *val;

  // Check input arguements
  if(argc < 2){
    fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  else{
    if((f = fopen(argv[1], "r")) == NULL){
      fprintf(stderr, "File \'%s\' not found.\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  }

  // Read file banner
  if(mm_read_banner(f, &matcode) != 0){
    fprintf(stderr, "Could not process Matrix Market banner.\n");
    exit(EXIT_FAILURE);
  }

  // Check for correct file types
  if(!mm_is_matrix(matcode) || !mm_is_symmetric(matcode))
  {
    fprintf(stderr, "Sorry, this application does not support ");
    fprintf(stderr, "Matrix Market type: [%s]\n", mm_typecode_to_str(matcode));
    exit(EXIT_FAILURE);
  }

  // Find out size of sparse matrix
  if((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
    exit(EXIT_FAILURE);

  if(M != N)
    fprintf(stderr, "Error: dimensions of sparse matrix not equal.");

  // Read values
  printf("\nAllocating space...\n");
  // Reseve memory for matrices
  I = (int *) malloc(nz * sizeof(int));
  J = (int *) malloc(nz * sizeof(int));
  val = (double *) malloc(nz * sizeof(double));

  // Read values
  printf("Loading file...\n");
  for(int i = 0; i < nz; i++){
      int num = fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
      if(num == 0){
        fprintf(stderr, "Read error: not enough elements\n");
        exit(EXIT_FAILURE);
      }
      // Adjust from 1-based to 0-based
      I[i]--;
      J[i]--;
  }

  // Close file
  if (f != stdin) fclose(f);

  // Time variables
  struct timeval startwtime, endwtime;
  double totaltime;

  // Call RCM
  gettimeofday(&startwtime, NULL);
  int *R = ReverseCuthillMckee(I, J, nz, M);
  gettimeofday(&endwtime, NULL);

  totaltime = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
            + endwtime.tv_sec - startwtime.tv_sec);

  // // print results
  // printf("\nPermutation array: ");
  // for(int i = 0; i < M; i++){
  //   printf("%d ", R[i]);
  // }
  // printf("\n");

  printf("\ntotal time: %f\n", totaltime);

  free(R);
  free(I);
  free(J);
  free(val);

  return 0;
}
