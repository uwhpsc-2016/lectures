#include "matmul.hpp"

#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>


using std::size_t;

int main(int argc, char** argv)
{
  std::cout << "[Matmul]" << std::endl;

  // determine the size of the matrix from the command line
  size_t size = 32;
  if (argc == 2)
    size = atoi(argv[1]);

  // allocate matrices
  size_t M = size, N = size, K = size;
  std::vector<double> A(M*N, 0);
  std::vector<double> B(N*K, 0);
  std::vector<double> C_naive(M*K, 0);
  std::vector<double> C_swap(M*K, 0);

  // populate A and B with random numbers
  std::default_random_engine e;
  std::uniform_real_distribution<double> uniform(-1,1);
  for (size_t n=0; n<M*N; ++n)
    A[n] = uniform(e);
  for (size_t n=0; n<N*K; ++n)
    B[n] = uniform(e);

  // compute matrix product
  std::cout << "Computing matrix product..." << std::endl;

  // compute and time using naive algorithm
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  matmul_naive(A, B, C_naive, M, N, K);

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "time (naive): " << elapsed_seconds.count() << std::endl;

  // // compute and time using swapped algorithm
  // start = std::chrono::system_clock::now();

  // matmul_swap(A, B, C_swap, M, N, K);

  // end = std::chrono::system_clock::now();
  // elapsed_seconds = end - start;
  // std::cout << "time (swap):  " << elapsed_seconds.count() << std::endl;

  // // check that the results are equal
  // bool equal = true;
  // for (size_t n=0; n<M*K; ++n)
  //   if (std::abs(C_naive[n] - C_swap[n]) > 1e-12)
  //     equal = false;

  // if (not equal)
  //   std::cout << "\tMATRICES NOT EQUAL" << std::endl;

  std::cout << "[Done]" << std::endl;
  return 0;
}
