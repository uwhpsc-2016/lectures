#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "shift.h"

void print_array(long* array, size_t length)
{
  printf("[");
  for (size_t i=0; i<length; ++i)
    printf(" %ld,", array[i]);
  printf("]\n");
}


int main(int argc, char** argv)
{
  // get the number of shifts from the command line
  int num_shifts = 1;
  if (argc > 1)
    num_shifts = atoi(argv[1]);

  MPI_Init(&argc, &argv);

  // each process initialize some data: (use rank and size as before)
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  size_t N = 8;
  long* uk = (long*) malloc(N * sizeof(long));
  for (size_t i=0; i<N; ++i)
    uk[i] = rank*N + i;

  // call the perform_shift() function, passing in MPI_COMM_WORLD for the
  // communicator. (We perform three shifts, for example.)
  //
  // ========== defined in shift.h. compiled in libshift.so ==========
  //
  perform_shift(uk, N, num_shifts, MPI_COMM_WORLD);

  // shifting complete. have each process print its chunk
  printf("\n[%d] Shifted Data array:\n", rank);
  print_array(uk, N);
  printf("\n");

  // free and clean up
  free(uk);

  MPI_Finalize();
  return 0;
}
