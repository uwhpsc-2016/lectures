#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int* arr, int length)
{
  printf("[");
  for (int i=0; i<length; ++i)
    printf(" %d,", arr[i]);
  printf("]");
}

int main(int argc, char** argv)
{
  // get number of threads from command line
  int num_threads = 2;
  if (argc > 1)
    num_threads = atoi(argv[1]);

  // initalize some arrays
  int a[8] = {1};
  int b[8] = {2};

  int thread_number;
#pragma omp parallel private(thread_number) num_threads(num_threads)
  {
    thread_number = omp_get_thread_num();

    printf("Part A: %d", thread_number);
    printf("\n");

#pragma omp barrier

    printf("Part B: %d", thread_number);
    printf("\n");
  }
}
