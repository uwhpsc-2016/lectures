#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void say_hello(double* a, size_t N, MPI_Comm comm)
{
  // get rank and size of communicator
  int rank, size;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  printf("Process %d / %d\n", rank, size);

  // have only process 0 set the array
  if (rank == 0)
    for (size_t i=0; i<N; ++i)
      a[i] = (double)i;
}
