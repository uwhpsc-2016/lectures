#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <omp.h>

/*
  pi_inclass

  Iteratively parallelizing numerical integration.

 */
int main(int argc, char** argv)
{
  printf("=== Approximating Pi ===\n");

  // get number of threads from command line
  int num_threads = 4;
  if (argc > 1)
    num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  long N = 100000000;
  double pi_actual = 3.1415926535897932;
  double pi_approx = 0.0;
  double xi;

  double end, start = omp_get_wtime();
  #pragma omp parallel private(xi)
  {
    int id = omp_get_thread_num();
    double dx = 1.0 / (double) N;

    #pragma omp for reduction(+:pi_approx)
    for (int i=0; i<N; ++i)
      {
        xi = (i + 0.5)*dx;
        pi_approx += 4.0 / (1.0 + xi*xi) * dx;
      }
  }

  end = omp_get_wtime();
  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("error:    = %e\n", fabs(pi_actual - pi_approx));
  printf("\ntime: %f sec\n", end - start);
  return 0;
}
