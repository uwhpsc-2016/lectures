#include <cstddef>
#include <vector>

using std::vector;
using std::size_t;

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
void matmul_naive(const vector<double>& A,
                    const vector<double>& B,
                    vector<double>& C,
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
void matmul_swap(const vector<double>& A,
                    const vector<double>& B,
                    vector<double>& C,
                    size_t M, size_t N, size_t K)
{
  for (size_t i=0; i<M; ++i)
    for (size_t k=0; k<N; ++k)  // swapped
      for (size_t j=0; j<K; ++j)  // swapped
        C[K*i + j] += A[N*i + k] * B[K*k + j];
}
