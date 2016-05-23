#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "adaptive.h"


/*
  _quadrature_adaptive_serial()

  A helper function for performing the serial adaptive integration. See the
  implementation documentation for quadrature_adaptive_serial() below for more
  information.
*/
double _quadrature_adaptive_serial(double (*f)(double), double a, double b, double tol,
                                   size_t level, FILE* fp, double* err)
{
  double trapezoid, simpson;
  double mid;
  double fa, fb, fmid;

  double integral, integral_left, integral_right;
  double err_current, err_left, err_right;
  double next_tol;
  int next_level;

  // evaluate the function at the interval boundaries and midpoint
  mid = 0.5*(a+b);
  fa = f(a);
  fb = f(b);
  fmid = f(mid);

  // compute the trapezoidal and simpson's rule approximates of the integral on
  // this interval and estimate the integration error
  //
  // VERY IMPORTANT: the absolute value function for floats / double is fabs().
  // abs() is the integer version
  trapezoid = 0.5*(b-a)*(fa + fb);
  simpson = (b-a)*(fa + 4*fmid + fb) / 6.0;
  err_current = fabs(trapezoid - simpson);

  // write these data to the diagnostic file
  fprintf(fp,
          "%zd,%f,%f,%f,%f,%.15f,%.15f\n",
          level,a,b,mid,fmid,tol,err_current);

  // if the error is greater than the requested tolerance then recursively
  // refine. additionally, only refine up to the maximum recursion level,
  // MAX_LEVEL, defined in adaptive.h
  if ((err_current > tol) && (level < MAX_LEVEL))
    {
      // the requested error tolerance for each subinterval half should be half
      // of the current tolerance (so that the sum of the errors is still less
      // than the desired error tolerance)
      next_tol = 0.5*tol;
      next_level = level + 1;

      // compute the integrals of the left and right subintervals. these are
      // also recursive calls, if necessary
      integral_left = _quadrature_adaptive_serial(f, a, mid, next_tol,
                                                  next_level, fp, &err_left);
      integral_right = _quadrature_adaptive_serial(f, mid, b, next_tol,
                                                   next_level, fp, &err_right);

      // again, because the requested error of each half is less than `tol/2`
      // then the sum of the two integrals have total error less than `tol`.
      //
      // store the resulting error into err, overwriting the "temporary"
      // estimate made above.
      integral = integral_left + integral_right;
      err_current = err_left + err_right;
    }
  else
    integral = trapezoid;

  // returns
  *err = err_current;
  return integral;
}



/*
  quadrature_adaptive_serial()

  Primary entry-point function for performing serial adaptive quadrature.

  This, effectively, just forwards input information to
  _quadrature_adaptive_serial(). The internal version of this function takes in
  several other input data which is determined by this function.

  This design pattern makes it such that the "user" doesn't need to know about
  the internals in order to make use of the code. That is, we hide the
  implementation details and try to make the forward-facing function
  quadrature_adaptive_serial() as easy to use as possible.
*/
double quadrature_adaptive_serial(double (*f)(double), double a, double b, double tol,
                                  double* err)
{
  double integral = 0.0;

  // open the csv file where we will write diagnositic information. A Python
  // script will read in these data and use the information to generate some
  // diagnostic plots. (also print csv headers)
  FILE *fp;
  fp = fopen("./diagnostics.csv", "w");
  if (!fp)
    {
      printf("\nERROR - Could not open diagnostic file.\n");
      exit(0);
    }
  fprintf(fp,"level,a,b,mid,fmid,tol,err\n");

  // call the function that actually does all of the hard work
  integral =  _quadrature_adaptive_serial(f, a, b, tol, 0, fp, err);

  // close the diagnostic file
  if (fclose(fp))
    {
      printf("\nERROR - Could not close diagnostic file.\n");
      exit(0);
    }

  // now that the diagnostic file is closed we can return the integral (the
  // error is returned by reference)
  return integral;
}
