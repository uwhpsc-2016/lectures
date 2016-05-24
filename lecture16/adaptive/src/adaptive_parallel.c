#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "adaptive.h"


/*
  _quadrature_adaptive_parallel()

  A helper function for performing the serial adaptive integration. See the
  implementation documentation for quadrature_adaptive_serial() below for more
  information.
*/
double _quadrature_adaptive_parallel(double (*f)(double), double a, double b,
                                     double tol, size_t level, FILE* fp,
                                     double* err)
{
  double trapezoid, simpson;
  double mid;
  double fa, fb, fmid;

  double integral, integral_left, integral_right;
  double err_current, err_left, err_right;
  double next_tol;
  int next_level;

  // evaluate the function at the interval boundaries and midpoint and
  // approximate the integral
  mid = 0.5*(a+b);
  fa = f(a);
  fb = f(b);
  fmid = f(mid);
  trapezoid = 0.5*(b-a)*(fa + fb);
  simpson = (b-a)*(fa + 4*fmid + fb) / 6.0;
  err_current = fabs(trapezoid - simpson);

  // write these data to the diagnostic file
  int thread_id = omp_get_thread_num();
  #pragma omp critical
  {
    fprintf(fp,
            "%d,%zd,%f,%f,%f,%f,%.15f,%.15f\n",
            thread_id,level,a,b,mid,fmid,tol,err_current);
  }

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

      /*
        INTRO TO OMP SECTIONS

        Sections are a non-iterative work-sharing construct. Each section is executed once by *a* thread in the team
       */
      #pragma omp parallel sections
      {
        #pragma omp section
        {
          integral_left = _quadrature_adaptive_parallel(
                              f, a, mid, next_tol, next_level,
                              fp, &err_left);
        }
        #pragma omp section
        {
          integral_right = _quadrature_adaptive_parallel(
                               f, mid, b, next_tol, next_level,
                               fp, &err_right);
        }
      }

      // accumulate. since integral_left and integral right are shared and
      // mutually exclusively computed we (a) don't need to put this in a
      // parallel region and therefore (b) don't need to make this critical /
      // atomic
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
double quadrature_adaptive_parallel(double (*f)(double), double a, double b,
                                    double tol, double* err, char* fname)
{
  double integral = 0.0;

  // open the csv file where we will write diagnositic information. A Python
  // script will read in these data and use the information to generate some
  // diagnostic plots. (also print csv headers)
  FILE *fp;
  fp = fopen(fname, "w");
  if (!fp)
    {
      printf("\nERROR - Could not open diagnostic file.\n");
      exit(0);
    }
  fprintf(fp,"thread,level,a,b,mid,fmid,tol,err\n");

  // call the function that actually does all of the hard work
  integral =  _quadrature_adaptive_parallel(f, a, b, tol, 0, fp, err);

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
