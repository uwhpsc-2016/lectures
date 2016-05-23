#include <math.h>
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
  printf("===== test_serial.c\n");
  double tol = 0.5;
  if (argc > 1)
    tol = atof(argv[1]);

  double err;
  double integral;
  integral = quadrature_adaptive_serial(integrand, -2, 4, tol, &err,
                                        "diagnostics.csv");

  printf("integral:  %f\n", integral);
  printf("(actual:   %f)\n", ACTUAL);
  printf("tolerance: %e\n", tol);
  printf("est error: %e\n", err);
  printf("act error: %e\n", fabs(integral-ACTUAL));
}
