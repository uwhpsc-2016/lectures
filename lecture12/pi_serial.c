#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
  pi_serial

  A simple way of approximating pi using Riemann sums. Compile with

  $ gcc -lm pi_parallel1.c
  $ ./a.out
*/
int main(int argc, char** argv)
{
  printf("===== Approximating Pi: Serial =====\n");

  // intialize the problem size, target value, and solution storage
  long N = 100000000;
  double pi_actual = 3.1415926535897932;
  double pi_approx = 0;
  double xi;
  double dx = 1.0 / (double) N;

  for (int i=0; i<N; ++i)
    {
      xi = (i + 0.5)*dx;

      // add  f(xi)dx  to sum
      pi_approx += 4.0/(1.0 + xi*xi) * dx;
    }

  printf("pi_actual = %.15f\n", pi_actual);
  printf("pi_approx = %.15f\n", pi_approx);
  printf("absolute error: %e\n", fabs(pi_actual - pi_approx));
}
