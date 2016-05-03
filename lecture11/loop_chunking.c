#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  // get the problem size
  int N = 8;
  if (argc > 1)
    N = atoi(argv[1]);

  /*
    parallel iterate with chunk_size = 1 (default)

    At each iteration, print the index being worked on and the thread number
  */
  omp_set_num_threads(2);
  printf("chunk size = 1\n");
#pragma omp parallel for schedule(static)
  for (int i=0; i<N; ++i)
    {
      int id = omp_get_thread_num();
      printf("Thread(%d) -- Index %d\n", id, i);
    }

  /*
    parallel iterate with chunk_size = 2

    Note that if a thread is computing index i it always ends up computing index
    i+1 as well. (Not necessarily the case with chunk_size = 1)
  */
  printf("\nchunk size = 2\n");
#pragma omp parallel for schedule(static, 2)
  for (int i=0; i<N; ++i)
    {
      int id = omp_get_thread_num();
      printf("Thread(%d) -- Index %d\n", id, i);
    }

  /*
    parallel iterate with chunk_size = 4

    If a thread computes index i it also computes indices i+1, i+2, and i+3
  */
  printf("\nchunk size = 4\n");
#pragma omp parallel for schedule(static, 4)
  for (int i=0; i<N; ++i)
    {
      int id = omp_get_thread_num();
      printf("Thread(%d) -- Index %d\n", id, i);
    }
}
