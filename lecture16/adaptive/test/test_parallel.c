#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "adaptive.h"


#define BETA 10.0
#define ACTUAL 0.414742169407

double integrand(double x)
{
  double value = exp(-BETA*BETA * x*x) + sin(x);
  return value;
}

int main(int argc, char** argv)
{
  printf("===== test_parallel.c\n");
  double tol = 0.5;
  if (argc > 1)
    tol = atof(argv[1]);

  double err = 0;
  double integral = 0.0;
  double a = -2;
  double b = 4;

  /*
    parallelize over the domain: have each thread take a chunk.
   */
  #pragma omp parallel shared(integral, err) num_threads(2)
  {
    double thread = omp_get_thread_num();
    double thread_integral;
    double thread_error;
    double thread_tol = 0.5*tol;
    double mid = 0.5*(a+b);

    // split the thread work
    if (thread == 0)
      thread_integral = quadrature_adaptive_serial(integrand, a, mid, thread_tol,
                                                   &thread_error, "diag0.csv");
    else
      thread_integral = quadrature_adaptive_serial(integrand, mid, b, thread_tol,
                                                   &thread_error, "diag1.csv");

    // safely accumulate results
    #pragma omp critical
    {
      integral += thread_integral;
      err += thread_error;
    }
  }

  printf("integral:  %f\n", integral);
  printf("(actual:   %f)\n", ACTUAL);
  printf("tolerance: %e\n", tol);
  printf("est error: %e\n", err);
  printf("act error: %e\n", fabs(integral-ACTUAL));
}
