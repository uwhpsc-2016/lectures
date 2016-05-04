#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

/*
  pi_parallel4

  Final optimization where we use the "reduction(op:list)" clause to get rid of
  the critical / atomic block. Compile with,

  $ gcc -lm -fopenmp pi_parallel4.c
  $ ./a.out
*/
int main(int argc, char** argv)
{
  printf("===== Approximating Pi: Parallel 4 =====\n");

  // get number of threads from command line
  int num_threads = 4;
  if (argc > 1)
    num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  long N = 100000000;
  double pi_actual = 3.1415926535897932;
  double pi_approx = 0;
  double end, start = omp_get_wtime();
  #pragma omp parallel
  {
    double xi;
    double dx = 1.0 / (double) N;

    /*
      omit the need to the critical / atomic block by using reduction()

      OpenMP may be able to optimally store values based on thread activity.
     */
    #pragma omp for reduction(+:pi_approx)
    for (int i=0; i<N; ++i)
      {
        xi = (i + 0.5)*dx;
        pi_approx += 4.0/(1.0 + xi*xi) * dx;
      }
  }
  end = omp_get_wtime();

  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("absolute error: %e\n", fabs(pi_actual - pi_approx));
  printf("\ntime: %f\n", end-start);
}
