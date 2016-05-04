#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

/*
  pi_parallel1

  Manual work sharing across threads using array storage. Compile with

  $ gcc -lm -fopenmp pi_parallel1.c
  $ ./a.out
*/
int main(int argc, char** argv)
{
  printf("===== Approximating Pi: Parallel 1 =====\n");

  // get number of threads from command line
  int num_threads = 4;
  if (argc > 1)
    num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  long N = 100000000;
  double pi_actual = 3.1415926535897932;
  double pi_approx = 0;

  /*
    set number of threads and create a heap-allocated array which will be used
    to store the partial sums.

    zero out these partial sums
   */
  double* partial_sums = (double*) malloc(num_threads * sizeof(double));
  for (int k=0; k<num_threads; k++)
    partial_sums[k] = 0.0;

  /*
    create a parallel block.

    by default, the variables defined above are shared. however, xi needs to be
    explicitly defined as private or else we run into race conditions. we also
    make dx private for performance purposes.
   */
  double end, start = omp_get_wtime();
  #pragma omp parallel
  {
    double xi;
    double dx = 1.0 / (double) N;
    int id = omp_get_thread_num();

    /*
      tell the current thread to only work on the elements equal to the thread
      `id` modulo the number of threads (num_threads)

      the following is a very common trick. study it well (though, in a future
      version of this program we'll let OpenMP do the work for us.)
     */
    for (int i=id; i<N; i += num_threads)
      {
        xi = (i + 0.5)*dx;

        // add f(xi)dx to appropriate location in thread storage array
        partial_sums[id] += 4.0/(1.0 + xi*xi) * dx;
      }
  }

  /*
    finally, sum up all of the partial sums
   */
  for (int k=0; k<num_threads; ++k)
    pi_approx += partial_sums[k];

  end = omp_get_wtime();

  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("absolute error: %e\n", fabs(pi_actual - pi_approx));
  printf("\ntime: %f\n", end-start);

  free(partial_sums);
}
