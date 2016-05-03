/*
  Demonstrates critical sections
 */
#include <limits.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/*
  min(a,b) - returns the minimium of a and b
 */
int min(int a, int b)
{
  /*
    C mini-lesson: "ternary operators"

    value = (condition ? value1 : value2);

    "value" is set equal to one of the two following values depending on the
    result of "condition"

    * conditon == true:   "value" set to "value1"
    * condition == false: "value" set to "value2"
   */
  return (a < b ? a : b);
}


int main(int argc, char** argv)
{
  // get the problem size
  int N = 1000;
  if (argc > 1)
    N = atoi(argv[1]);

  /*
    initalize some arrays

    Important note: shared arrays used in parallel blocks must be heap
    allocated. This is because each thread has its own stack.
  */
  srand(0);
  int* a = (int*) malloc(N * sizeof(int));
  for (int i=0; i<N; ++i)
    a[i] = rand();

  /*
    find the minimum

    Find and print the minimum in serial
  */
  int minimum = INT_MAX - 1;
  for (int i=0; i<N; ++i)
    minimum = min(minimum, a[i]);
  printf("Serial min:   %d\n", minimum);


  /*
    parallelize finding the minimum

    Each thread will compute a local minimum in parallel. Finally, we enter a
    critical section that each thread will execute one at a time. This is to
    make sure the minimum is correctly computed.
  */
  minimum = INT_MAX - 1;
  #pragma omp parallel shared(a) num_threads(4)
  {
    int local_minimum = minimum;

    // optional: add "nowait" to omp for
    #pragma omp for schedule(static) nowait
    for (int i=0; i<N; ++i)
      local_minimum = min(local_minimum, a[i]);

    // simulate big computation
    double dummy = 0;
    for (int j=0; j<10000; ++j)
      dummy += 0.001*j;

    // update
    #pragma omp critical
    {
      minimum = min(local_minimum, minimum);
    }
  }

  printf("Parallel min: %d\n", minimum);
  free(a);
}
