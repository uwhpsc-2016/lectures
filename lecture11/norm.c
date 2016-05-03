#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
  // get the problem size
  int num_threads = 4;
  if (argc > 1)
    num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  /*
    initalize some arrays

    Important note: shared arrays used in parallel blocks must be heap
    allocated. This is because each thread has its own stack.
  */
  srand(0);
  int N = 1000;
  double* a = (double*) malloc(N * sizeof(double));
  double* b = (double*) malloc(N * sizeof(double));
  for (int i=0; i<N; ++i)
    {
      a[i] = (double)rand() / (double)(RAND_MAX) - 0.5;
      b[i] = (double)rand() / (double)(RAND_MAX) - 0.5;
    }

  /*
    serial version
  */
  double norm = 0;
  double temp;
  for (int i=0; i<N; ++i)
    {
      temp = a[i] + b[i];
      norm += temp*temp;
    }
  printf("Serial norm:   %f\n", norm);

  /*
    parallel version using reduction
   */
  norm = 0;
  #pragma omp parallel for  \
    private(temp)           \
    schedule(static,10)     \
    reduction(+:norm)
  for (int i=0; i<N; ++i)
    {
      temp = a[i] + b[i];
      norm += temp*temp;
    }

  printf("Parallel norm: %f\n", norm);
  free(a);
  free(b);

  return 0;
}
