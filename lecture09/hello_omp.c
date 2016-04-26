/*
  hello_omp.c

  Compile using:

  $ gcc -fopenmp hello_omp.c -o hello

 */

#include <stdio.h>
#include "omp.h"

int main()
{
#pragma omp parallel num_threads(4)
  {
    int id = omp_get_thread_num();
    printf("Hello(%d),", id);
    printf("world(%d)!\n", id);
  }
}
