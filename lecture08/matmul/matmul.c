#include <stdlib.h>
#include <time.h>

/*
  matmul_naive

  Implementation Notes
  --------------------

  `matmul_naive` is the standard implementation of matrix multiplication. The
  outer two loops determine which element of the output matric `C` to compute:
  `C[i][j]`. For each element, we compute the inner product of the `i`th row of
  `A` with the `j`th column of `B`.

      C[i][j] = < A[i][:], B[:][j] >

*/
void matmul_naive(double* C, double* A, double* B,
                  size_t M, size_t N, size_t K)
{
  for (size_t i=0; i<M; ++i)
    for (size_t j=0; j<K; ++j)
      for (size_t k=0; k<N; ++k)
        C[K*i + j] += A[N*i + k] * B[K*k + j];
}

/*
  matmul_swap

  Implementation Notes
  --------------------

  The only difference between `matmul_swap` and `matmul_naive` is that two
  inner-most loops have been swapped. That is, instead of choosing an `[i][j]`
  element of `C` and computing an inner product we instead compute one term of
  the inner products of each element in the `i`th row of C.

  This is a much better memory access pattern than in the naive case. Here, we
  not only are accessing an entire row of `B` at a time (elements `B[K*k]` to
  `B[K*k+(K-1)]`) but storing results in an entire row of `C` (elements `C[K*i]`
  to `C[K*i+(K-1)]`). Each of these chunks of memory are contiguous.
*/
void matmul_fast(double* C, double* A, double* B,
                 size_t M, size_t N, size_t K)
{
  for (size_t i=0; i<M; ++i)
    for (size_t k=0; k<N; ++k)  // swapped
      for (size_t j=0; j<K; ++j)  // swapped
        C[K*i + j] += A[N*i + k] * B[K*k + j];
}


float time_naive(size_t N)
{
  // create three matrices
  double* A = (double *) malloc(N*N*sizeof(double));
  double* B = (double *) malloc(N*N*sizeof(double));
  double* C = (double *) malloc(N*N*sizeof(double));

  // populate A and B with (seeded) random floats in the interval [-1,1]
  //
  // See documentation for rand() in the random.h library. Also, note that two
  // loops is contiguous memory access for each matrix, as opposed to one loop

  // for both.
  srand(0);
  for (int i=0; i<N*N; ++i)
    A[i] = 2*((double)rand()/(double)RAND_MAX) - 1;
  for (int i=0; i<N*N; ++i)
    B[i] = 2*((double)rand()/(double)RAND_MAX) - 1;

  // time the naive method
  clock_t elapsed;
  float seconds;

  elapsed = clock();
  matmul_naive(C, A, B, N, N, N);
  elapsed = clock() - elapsed;
  seconds = (float) elapsed / CLOCKS_PER_SEC;

  // free
  free(A);
  free(B);
  free(C);
  return seconds;
}

float time_fast(size_t N)
{
  // create three matrices
  double* A = (double *) malloc(N*N*sizeof(double));
  double* B = (double *) malloc(N*N*sizeof(double));
  double* C = (double *) malloc(N*N*sizeof(double));

  // populate A and B with (seeded) random floats in the interval [-1,1]
  //
  // See documentation for rand() in the random.h library. Also, note that two
  // loops is contiguous memory access for each matrix, as opposed to one loop
  // for both.
  srand(0);
  for (int i=0; i<N*N; ++i)
    A[i] = 2*((double)rand()/(double)RAND_MAX) - 1;
  for (int i=0; i<N*N; ++i)
    B[i] = 2*((double)rand()/(double)RAND_MAX) - 1;

  // time the naive method
  clock_t elapsed;
  float seconds;

  elapsed = clock();
  matmul_fast(C, A, B, N, N, N);
  elapsed = clock() - elapsed;
  seconds = (float) elapsed / CLOCKS_PER_SEC;

  // free
  free(A);
  free(B);
  free(C);
  return seconds;
}
