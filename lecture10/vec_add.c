#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "omp.h"


// arrays_equal
//
// returns 1 if the two input arrays are equal, 0 otherwise
int arrays_equal(int* a, int* b, int N)
{
  for (int i=0; i<N; ++i)
    if (a[i] != b[i])
      return 0;
  return 1;
}

void vec_add_serial(int* out, int* v, int* w, int N)
{
  int i;
  for (i=0; i<N; ++i)
    {
      out[i] = v[i] + w[i];
    }
}

void vec_add_parallel(int* out, int* v, int* w, int N)
{
  // create a parallel region
  //
  // by default, anything declared outside is shared.
  //
  // good design: explicitly declare what is shared to
  // indicate to people reading your code what is being
  // read / written to in parallel
  //
  // if the looping variable is declared outside then remember
  // to label it as "private"
  int i;
#pragma omp parallel shared(out,v,w) private(i) num_threads(4)
  {
    // <-- or you can declare "int i;" here and omit "private(i)"
    //
    // also, try removing "#pragma omp for" to see the resulting slowdown
    #pragma omp for
    for (int i=0; i<N; ++i)  // or you can declare "int i=0" here ...
      out[i] = v[i] + w[i];
  }
}


void vec_add_chunked(int* out, int* v, int* w, int N)
{
  // choosing an optimal loop chunk size is problem-dependent. in this case,
  // because the work done in each iteration is not that expensive (adding two
  // integers) it's probably best to assign a large chunk size
  int i;
  int chunk_size = 2048;
  #pragma omp parallel shared(out,v,w,chunk_size) private(i) num_threads(4)
  {
    // <-- or you can declare "int i;" here and omit "private(i)"
    #pragma omp for schedule(dynamic, chunk_size)
    for (int i=0; i<N; ++i)  // or you can declare "int i=0" here ...
      out[i] = v[i] + w[i];
  }
}

int main(int argc, char** argv)
{
  // create some random vectors and storage on the stack
  int N = 1 << 23; // about 8 million
  int* v = (int*) malloc(N*sizeof(int));
  int* w = (int*) malloc(N*sizeof(int));
  int* out_serial = (int*) malloc(N*sizeof(int));
  int* out_parallel = (int*) malloc(N*sizeof(int));

  // seed the random number generator
  srand(0);
  for (int i=0; i<N; ++i)
    {
      v[i] = ((int)rand() % 11) - 10; // random numbers between -10 and 10
      w[i] = ((int)rand() % 11) - 10;
    }

  double start, end;
  double serial_time, parallel_time, chunked_time;

  // time serial vecadd
  start = omp_get_wtime();
  vec_add_serial(out_serial, v, w, N);
  end = omp_get_wtime();
  serial_time = end - start;
  printf("serial time:   %f sec\n", serial_time);

  // time parallel vecadd
  start = omp_get_wtime();
  vec_add_parallel(out_parallel, v, w, N);
  end = omp_get_wtime();
  parallel_time = end - start;
  printf("parallel time: %f sec\n", parallel_time);

  // time chunked vecadd (overwrite out_parallel to save space)
  start = omp_get_wtime();
  vec_add_chunked(out_parallel, v, w, N);
  end = omp_get_wtime();
  chunked_time = end - start;
  printf("chunked time:  %f sec\n", chunked_time);

  printf("\nparallel speed up = %f\n", serial_time / parallel_time);
  printf("chunked speed up  = %f\n", serial_time / chunked_time);

  // will throw a runtime error if the arrays are not equal.
  // (a very harsh way to quit the program)
  printf("\nTesting if vectors are equal...");
  int are_equal = arrays_equal(out_serial, out_parallel, N);
  if (are_equal)
    printf("true.\n");
  else
    printf("false.\n");


  free(v);
  free(w);
  free(out_serial);
  free(out_parallel);
  return 0;
}
