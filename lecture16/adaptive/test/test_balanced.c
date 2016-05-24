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
  printf("===== test_balanced.c\n");
  double tol = 0.5;
  if (argc > 1)
    tol = atof(argv[1]);

  // set up parallel environment: need to explicitly allow "nested" threading.
  // (That is, omp threads creating their own omp parallel constructs.)
  //
  int num_threads = 2; // 1 or 2
  omp_set_num_threads(num_threads);
  omp_set_nested(1);
  omp_set_dynamic(0);
  printf("num_threads = %d\n", num_threads);

  double err;
  double integral;
  integral = quadrature_adaptive_parallel(integrand, -2, 4, tol, &err,
                                          "diagnostics_parallel.csv");

  printf("integral:  %f\n", integral);
  printf("(actual:   %f)\n", ACTUAL);
  printf("tolerance: %e\n", tol);
  printf("est error: %e\n", err);
  printf("act error: %e\n", fabs(integral-ACTUAL));
}
