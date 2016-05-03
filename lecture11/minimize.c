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

    * condition == true:   "value" set to "value1"
    * condition == false: "value" set to "value2"
   */
  /* if (a<b) */
  /*   return a; */
  /* else */
  /*   return b; */
  return (a < b ? a : b);
}


int main(int argc, char** argv)
{
  // get the problem size
  int N = 1024;
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
  int minimum = INT_MAX;
  for (int i=0; i<N; ++i)
    minimum = min(minimum, a[i]);
  printf("Serial min:   %d\n", minimum);


  /*
    parallelize finding the minimum

    Each thread will compute a local minimum in parallel. Finally, we enter a
    critical section that each thread will execute one at a time. This is to
    make sure the minimum is correctly computed.
  */
  minimum = INT_MAX;
  #pragma omp parallel shared(a,minimum) num_threads(4)
  {
    int local_minimum = minimum;
    int temp;

    // determine local minimum for current chunk.
    //
    // optional: add "nowait" to omp for
    #pragma omp for nowait
    for (int i=0; i<N; ++i)
      local_minimum = min(local_minimum, a[i]);

    // now determine minimum from each thread's work
    //
    // (OMIT omp critical to see race condition effects. may need to run
    // multiple times.)
    #pragma omp critical
    {
      temp = min(local_minimum, minimum);

      // do some dummy work to illustrate potential issues if this were not a
      // critical section. i.e. encountering race conditions. that is, becuase
      // the line
      //
      // minimum = min(local_minimum, minimum)
      //
      // contains few instructions it is very rare to encounter a race condition
      // (though possible!)
      for(int j=0; j<100000; ++j)
        local_minimum += 0.0001*j;

      // actually set the minimum
      minimum = temp;
    }
  }

  printf("Parallel min: %d\n", minimum);
  free(a);
}
