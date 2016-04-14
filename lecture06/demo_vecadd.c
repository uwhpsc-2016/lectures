#include <stdio.h>
#include <stdlib.h>

void print_array(int* a, int n)
{
  printf("[");
  for (int i=0; i<n; ++i)
    printf(" %d,", a[i]);
  printf("]\n");
}

int* create_range(int n)
{
  int new_array = (int*) malloc(n * sizeof(int));
  for (int i=0; i<n; ++i)
    new_array[i] = i;
  return new_array;
}

void vec_add(int* out, int* v, int* w, int length)
{
  for (int i=0; i<length; ++i)
    out[i] = v[i] + w[i];
}

int main(int argc, char** argv)
{
  // get optional vector length from command line
  int n = 2;
  if (argc > 1)
    n = atoi(argv[1]);

  // heap allocate some arrays (vectors)
  int* vec1 = create_range(n);
  int* vec2 = create_range(n);
  int* sum = (int*) malloc(n * sizeof(int));  // empty, heap allocated array

  // call vec_add which stores result of sum in first argument
  vec_add(sum, v, w, n);
  print_array(sum, n);

  // free the heap allocated memory
  free(vec1); // we need to know that "create_range" heap allocates memory!
  free(vec2); // we need to know that "create_range" heap allocates memory!
  free(sum);
}
