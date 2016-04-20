#ifndef lecture_matmul_h
#define lecture_matmul_h

#include <stdlib.h>

/*
  matmul_naive

  Compute the matrix product.

  Given matrices `A` and `B` of dimensions `M`x`N` and `N`x`K`, respectively,
  determine their product `C`. This implementation uses the naive approach to
  computing the matrix product.

  This function is return by reference.

  Parameters
  ----------
  C : double*
      Storage for output matrix
  A : double*
  B : double*
      The input matrices.
  M : size_t
  N : size_t
  K : size_t
      Dimensions of the input matrices. `A` is `M`x`N` and `B` is `N`x`K`.

  Returns
  -------
  C : double*
      The output matrix. Return by reference.

*/
void matmul_naive(double* C, double* A, double* B, size_t M, size_t N, size_t K);

/*
  matmul_swap

  Compute the matrix product.

  Given matrices `A` and `B` of dimensions `M`x`N` and `N`x`K`, respectively,
  determine their product `C`. This implementation uses the more memory-optimal
  loop ordering. Otherwise identical to `matmul_naive`.

  This function is return by reference.

  Parameters
  ----------
  C : double*
      Storage for output matrix
  A : double*
  B : double*
      The input matrices.
  M : size_t
  N : size_t
  K : size_t
      Dimensions of the input matrices. `A` is `M`x`N` and `B` is `N`x`K`.

  Returns
  -------
  C : double*
      The output matrix. Return by reference.
*/
void matmul_fast(double* C, double* A, double* B, size_t M, size_t N, size_t K);

float time_naive(size_t N);
float time_fast(size_t N);

#endif
