#include <stdio.h>
#include "matmul.h"

/*
  main

  Take the matrix sizes as a command line argument. (Default 8x8)
*/
int main(int argc, char** argv)
{
  // get size from command line
  size_t N = 8;
  if (argc > 1)
    N = atoi(argv[1]);

  // time native and fast methods
  float seconds;
  seconds = time_naive(N);
  printf("naive: %f sec\n", seconds);
  seconds = time_fast(N);
  printf("fast:  %f sec\n", seconds);

  return 0;
}
