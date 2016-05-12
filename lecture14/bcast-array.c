#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char** argv)
{
  int rank, world_size;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // every proc allocates its own copy of "data" but only "proc 0" initializes
  // it to [0, 1, ..., N-1]
  int N = 8;
  int* data = (int*) malloc(N * sizeof(int));
  if (rank == 0)
    for (int i=0; i<N; ++i)
      data[i] = i;

  printf("[PRE-BCAST] Proc %d --- data = [%d, %d, %d, ...]\n",
         rank, data[0], data[1], data[2]);

  // common confusion with Bcast: again, everyone calls bcast.
  //
  // in this case, we want to transmit a chunk of data to each process.
  // (including process 0) for example, if there are a total of 2 processes we
  // will transmit the first half of "data" to proc 0 and the second half to
  // process 1
  //
  //        buffer len type     source_proc communicator
  MPI_Bcast(data,  N,  MPI_INT, 0,          MPI_COMM_WORLD);

  // call MPI_Barrier just to separate the printing of PRE- and POST- broadcast
  // information
  MPI_Barrier(MPI_COMM_WORLD);

  printf("[POST-BCAST] Proc %d --- data = [%d, %d, %d, ...]\n",
         rank, data[0], data[1], data[2]);

  // where do you free? each process should free its allocation before
  // MPI_Finalize is called (otherwise, only "root" process frees
  free(data);
  MPI_Finalize();
  return 0;
}
