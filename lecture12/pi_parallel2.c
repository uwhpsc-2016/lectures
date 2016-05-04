#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

/*
  pi_parallel2

  Manual work sharing across threads using local / private variables for storing
  thread-specific partial sums

  $ gcc -lm -fopenmp pi_parallel2.c
  $ ./a.out
*/
int main(int argc, char** argv)
{
  printf("===== Approximating Pi: Parallel 2 =====\n");

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
    int id = omp_get_thread_num();
    int nthreads = num_threads;

    // still using our manual for loop work sharing. store partial result in a
    // local (thread private) variable
    double thread_partial_sum = 0.0;
    for (int i=id; i<N; i += nthreads)
      {
        xi = (i + 0.5)*dx;

        // add f(xi)dx to local (thread private) accumulator. No other thread
        // will write to this so it is a thread-safe operation
        thread_partial_sum += 4.0/(1.0 + xi*xi) * dx;
      }

    // once all the threads compute their partial sum (i.e. when they reach this
    // point) accumulated to the shared variable `pi_approx`. must be
    // thread-controlled so as to avoid race conditions
    #pragma omp atomic
    pi_approx += thread_partial_sum;
  }
  end = omp_get_wtime();

  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("absolute error: %e\n", fabs(pi_actual - pi_approx));
  printf("\ntime: %f\n", end-start);
}
