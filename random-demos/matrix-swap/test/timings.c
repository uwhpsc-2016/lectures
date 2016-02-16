#include "matmul.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  rand_unit

  Returns a random number on the unit interval [-1,1].

  Parameters
  ----------
  None

  Returns
  -------
  value : double
      A random number.
*/
double rand_unit(void);
double rand_unit(void)
{
  // scale from [0,RAND_MAX] to [0,1]
  double value = (double)rand() / (double)RAND_MAX;

  // scale from [0,1] to [-1,1]
  value = 2*value - 1;
  return value;
}


int main(int argc, char** argv)
{
  printf("[Lecture - Matmul]\n");

  // determine the size of the matrix from the command line
  size_t size = 32;
  if (argc == 2)
    size = atoi(argv[1]);

  // allocate matrices
  size_t M = size, N = size, K = size;
  double* A = malloc(M*N*sizeof(double));
  double* B = malloc(N*K*sizeof(double));
  double* C_naive = malloc(M*K*sizeof(double));
  double* C_swap = malloc(M*K*sizeof(double));

  // populate A and B with random numbers
  for (size_t n=0; n<M*N; ++n)
    A[n] = rand_unit();
  for (size_t n=0; n<N*K; ++n)
    B[n] = rand_unit();

  // compute matrix product
  printf("Computing matrix product...\n");

  // compute and time using naive algorithm
  matmul_naive(A, B, C_naive, M, N, K);

  // compute and time using swapped algorithm
  matmul_swap(A, B, C_swap, M, N, K);

  // check that the results are equal
  int equal = 1;
  for (size_t n=0; n<M*K; ++n)
    if (fabs(C_naive[n] - C_swap[n]) > 1e-12)
      equal = 0;

  if (!equal)
    printf("\tMATRICES NOT EQUAL\n");

  printf("[Done]\n");
  return 0;
}
