#include <stdio.h>
#include <stdlib.h>

void double_array(int* arr, int length)
{
  int temp[length]; // dynamic stack allocation. disappears after func call
  int i;

  // copy contents of arr to temp
  for (i=0; i<length; ++i)
    temp[i] = arr[i];

  // double
  for (i=0; i<length; ++i)
    temp[i] *= 2;

  // copy contents back
  for (i=0; i<length; ++i)
    arr[i] = temp[i];

  // `temp` (and `i`) pops off the stack
}

void print_array(int* a, int n)
{
  printf("[");
  for (int i=0; i<n; ++i)
    printf(" %d,", a[i]);
  printf("]\n");
}

int main(int argc, char** argv)
{
  // get the vector size from the command line
  int length = 2;
  if (argc > 1)
    length = atoi(argv[1]);

  // initialize arr to range(length)
  int* arr = (int*) malloc(length * sizeof(int));
  for (int i=0; i<length; ++i)
    arr[i] = i;

  print_array(arr, length);
  double_array(arr, length);
  print_array(arr, length);

  return 0;
}
