#include <stdio.h>
#include <stdlib.h>

void scale_array(int scale, int* a, int n)
{
  for (int i=0; i<n; ++i)
    a[i] = scale*a[i];
}

void print_array(int* a, int n)
{
  printf("[");
  for (int i=0; i<n; ++i)
    printf(" %d,", a[i]);
  printf("]\n");
}

int* create_range_array(int n)
{
  // CORRECT METHOD: need to heap allocate memory or else it is lost in the stack frame
  int new_array = (int*) malloc(n*sizeof(int));
  for (int i=0; i<n; ++i)
    new_array[i] = i;
  return new_array;
}

int main(int argc, char** argv)
{
  // Bonus: get the desired size of array from the command line
  int n = 2;
  if (argc > 1)
    {
      n = atoi(argv[1]);
    }

  int arr;
  arr = create_range_array(n);

  // print the array
  print_array(arr, n);

  // scale and print
  scale_array(2.0, arr, n);
  print_array(arr, n);
  return 0;
}
