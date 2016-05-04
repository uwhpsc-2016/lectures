#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

/*
  pi_quick

  Trying to modify pi_serial.c as little as possible to use OpenMP. Compile
  with,

  $ gcc -lm -fopenmp pi_quick.c
  $ ./a.out
*/
int main(int argc, char** argv)
{
  printf("===== Approximating Pi: Serial =====\n");

  long N = 100000000;
  double pi_actual = 3.1415926535897932;
  double pi_approx = 0;
  double xi;
  double dx = 1.0 / (double) N;

  // ====== one-line change from pi_serial (other than the timing stuff) ======
  double end, start = omp_get_wtime();  // timing
  #pragma omp parallel for private(xi) reduction(+:pi_approx) num_threads(4)
  for (int i=0; i<N; ++i)
    {
      xi = (i + 0.5)*dx;

      // add  f(xi)dx  to sum
      pi_approx += 4.0/(1.0 + xi*xi) * dx;
    }
  end = omp_get_wtime();  // timing

  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("absolute error: %e\n", fabs(pi_actual - pi_approx));
  printf("\ntime: %f\n", end-start);  // timing
}
