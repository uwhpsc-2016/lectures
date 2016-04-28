#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

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
  int i;
#pragma omp parallel for shared(out,v,w) private(i) num_threads(4)
  for (i=0; i<N; ++i)
    {
      out[i] = v[i] + w[i];
    }
}

void vec_add_chunked(int* out, int* v, int* w, int N)
{
  int i;
  #pragma omp parallel shared(out,v,w) private(i) num_threads(4)
  {
    int chunk_size = N / omp_get_num_threads();
    #pragma omp for schedule(static,chunk_size)
    for (i=0; i<N; ++i)
      {
        out[i] = v[i] + w[i];
      }
  }
}



int main(int argc, char** argv)
{
  // create some random vectors and storage on the heap
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

  // time chunked vecadd
  start = omp_get_wtime();
  vec_add_chunked(out_parallel, v, w, N);
  end = omp_get_wtime();
  chunked_time = end - start;
  printf("chunked time:  %f sec\n", chunked_time);

  // speedup
  printf("\nspeedup: %f\n", serial_time/parallel_time);
  printf("chunked: %f\n", serial_time/chunked_time);

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
