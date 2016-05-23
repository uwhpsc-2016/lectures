#ifndef __adaptive_h
#define __adaptive_h

/*
  MAX_LEVEL

  The maximum levels of recursion allowed in the adaptive integration routines.
 */
#define MAX_LEVEL 32

/*
  quadrature_adaptive_serial

  Given a function (as a function pointer), an interval [a,b], and an
  integration tolerance compute the integral of f on the interval to the
  requested tolerance using an adaptive integration routine.

  This recursive algorithm will estimate the integral on successive subintervals
  until the desired accuracy is obtained.

  The function also outputs a diagnostic file in csv format for visualizing how
  the adaptive refinement was executed.

  Parameters
  ----------
  f : function (double -> double)
      The function to integrate.
  a : double
  b : double
      The interval [a,b] over which to integrate.
  tol : double
      Requested accuracy / tolerance of the adaptive routine.
  err : double*
      A return-by-reference estimate of the actual error in the adaptive
      integration routine.
  fname : string
      Name of file to write diagnostic results to. Sort of breaks the philosophy of
      this function hiding the internals but...this is easy for now.

  Returns
  -------
  integral : double
      The integral of f on the interval.
  err : double*
      Return-by-reference of the estimated error.
 */
double quadrature_adaptive_serial(double (*f)(double), double a, double b,
                                  double tol, double* err, char* fname);

#endif
