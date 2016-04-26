/*
  dynamic_threads.c

  How to dynamically set the number of threads in an OpenMP code.

  Compile:

      $ gcc -fopenmp dynamic_threads.c -o dynamic_threads

  Run:

      $ ./dynamic_threads 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
  // obtain the number of threads from the command line.
  // use four by default
  int number_of_threads = 4;
  if (argc > 1)
    number_of_threads = atoi(argv[1]);

  // dynamically (i.e. at runtime) set the number of threads used from here on
  omp_set_num_threads(number_of_threads);

  // this block will now execute with `number_of_threads` threads
#pragma omp parallel
  {
    // assign to the local variable `id` (local to the current thread) the
    // current thread's unique identification number
    int id = omp_get_thread_num();

    // print thread information
    printf("Thread %d / %d\n", id, number_of_threads);
  }

  // now halve the number of threads and run a different block
  number_of_threads >>= 1;  // fancy way of writing: "x /= 2" or "x = x/2"
  omp_set_num_threads(number_of_threads);

#pragma omp parallel
  {
    int id = omp_get_thread_num();
    printf("(Second block) Thread %d / %d\n", id, number_of_threads);
  }

  return 0;
}
