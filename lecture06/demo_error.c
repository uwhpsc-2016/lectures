#include <stdio.h>
#include <stdlib.h>

// scales an integer array of length n by the factor `scale`
//
void scale_array(int scale, int* a, int n)
{
  for (int i=0; i<n; ++i)
    a[i] = scale*a[i];
}

// prints an integer array of length n
//
void print_array(int* a, int n)
{
  printf("[");
  for (int i=0; i<n; ++i)
    printf(" %d,", a[i]);
  printf("]\n");
}

int* create_range_array(int n)
{
  // THIS IS THE INCORRECT WAY TO HAVE THIS FUNCTION RETURN A (POINTER TO AN)
  // ARRAY. Reason being, using "int new_array[n]" allocates an array on this
  // function's stack frame. "new_array" points to the beginning of this array.
  // Once the function terminates the stack memory it has allocated disappears,
  // invalidating the pointer.
  int new_array[n];
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

  int arr[n];
  // Method 1: write code to populate array within main(). This method works
  for (int i=0; i<n; ++i)
    arr[i] = i;

  // Method 2: try to create "range array" using a separate function. THIS WILL
  //NOT WORK! Try commenting out "Method 1" above and uncommenting the line
  //below and see what happens. You should get a "segmentation fault".
  //
  //arr = create_range_array(n);

  // print the array
  print_array(arr, n);

  // scale and print
  scale_array(2.0, arr, n);
  print_array(arr, n);
  return 0;
}
