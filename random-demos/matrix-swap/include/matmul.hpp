#ifndef lecture_matmul_hpp
#define lecture_matmul_hpp

#include <cstddef>
#include <vector>

using std::vector;
using std::size_t;

/*
  matmul_naive

  Compute the matrix product.

  Given matrices `A` and `B` of dimensions `M`x`N` and `N`x`K`, respectively,
  determine their product `C`. This implementation uses the naive approach to
  computing the matrix product.

  This function is return by reference.

  Parameters
  ----------
  A : const matrix&
  B : const matrix&
      The input matrices.
  M : size_t
  N : size_t
  K : size_t
      Dimensions of the input matrices. `A` is `M`x`N` and `B` is `N`x`K`.

  Returns
  -------
  C : matrix&
      The output matrix.

*/
void matmul_naive(const vector<double>&, const vector<double>&, vector<double>&,
                  size_t, size_t, size_t);

/*
  matmul_swap

  Compute the matrix product.

  Given matrices `A` and `B` of dimensions `M`x`N` and `N`x`K`, respectively,
  determine their product `C`. This implementation uses the more memory-optimal
  loop ordering. Otherwise identical to `matmul_naive`.

  This function is return by reference.

  Parameters
  ----------
  A : const matrix&
  B : const matrix&
      The input matrices.
  M : size_t
  N : size_t
  K : size_t
      Dimensions of the input matrices. `A` is `M`x`N` and `B` is `N`x`K`.

  Returns
  -------
  C : matrix&
      The output matrix.

*/
void matmul_swap(const vector<double>&, const vector<double>&, vector<double>&,
                 size_t, size_t, size_t);

#endif
