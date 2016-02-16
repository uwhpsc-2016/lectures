#ifndef lecture__matmul_hpp
#define lecture__matmul_hpp

#include <cstddef>

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

template <typename T>
void matmul_naive(const T&, const T&, T&, std::size_t, std::size_t, std::size_t);

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

template <typename T>
void matmul_swap(const T&, const T&, T&, std::size_t, std::size_t, std::size_t);

#endif
