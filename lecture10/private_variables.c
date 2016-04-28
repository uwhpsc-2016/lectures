/*
  private_variables.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
  // get and set number of threads
  int number_of_threads = 4;
  if (argc > 1)
    number_of_threads = atoi(argv[1]);
  omp_set_num_threads(number_of_threads);

  // variables declared outside the parallel region are "global"
  int id;

  #pragma omp parallel
  {
    // each thread will assign (and overwrite) to this variable
    id = omp_get_thread_num();

    // do something that takes some time
    double sum = 0;
    for (int i=0; i<100000; ++i)
      sum += i/4.0;

    // by the time this is executed by thread `i` the variable `id` may have
    // been overwritten by thread `j`
    printf("Is %d == %d?\n", id, omp_get_thread_num());
  }

  printf("\nUsing private variables:\n");
  #pragma omp parallel private(id)
  {
    // now, each thread will have it's own copy of `id`
    id = omp_get_thread_num();

    double sum = 0;
    for (int i=0; i<100000; ++i)
      sum += i/4.0;

    printf("Is %d == %d?\n", id, omp_get_thread_num());
  }

  return 0;
}
