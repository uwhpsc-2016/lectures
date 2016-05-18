#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

void print_array(long* array, size_t length)
{
  printf("[");
  for (size_t i=0; i<length; ++i)
    printf(" %ld,", array[i]);
  printf("]\n");
}


/*
  Factor out the shifting operation in a separate function. useful if, say, you
  want to use this functionality again.

  Each process will call this function passing in its own copies of uk. These
  copies of uk are modified in-place.
 */
void perform_shift(long* uk, size_t N, long num_shifts, MPI_Comm comm)
{
  int rank, size;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  int left_process = (rank-1+size) % size;
  int right_process = (rank+1) % size;
  MPI_Request req;
  MPI_Status stat;
  long left_ghost, right_ghost = uk[N-1];

  for (long shift_count=0; shift_count<num_shifts; ++shift_count)
    {
      // communicate boundary data: pass right_ghost to right_process.
      // right_process then stores result in its own left_ghost
      MPI_Send(&right_ghost, 1, MPI_LONG, right_process, 0, MPI_COMM_WORLD);
      MPI_Recv(&left_ghost, 1, MPI_LONG, left_process, 0, MPI_COMM_WORLD, &stat);

      // shift data
      for (size_t i=N-1; i>=1; --i)
        uk[i] = uk[i-1];
      uk[0] = left_ghost;

      // update right_ghost for next communication
      right_ghost = uk[N-1];
    }

  // nothing to return: the arrays, uk, are modified in-place
}


/*
  main() will now call perform_shift() after creating some example data.
 */
int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);

  // each process initialize some data: (use rank and size as before)
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  size_t N = 8;
  long* uk = (long*) malloc(N * sizeof(long));
  for (size_t i=0; i<N; ++i)
    uk[i] = rank*N + i;

  // have each process print its chunk
  printf("\n[%d] Data array:\n", rank);
  print_array(uk, N);
  printf("\n");
  MPI_Barrier(MPI_COMM_WORLD);
  fflush(stdout);

  // call the perform_shift() function, passing in MPI_COMM_WORLD for the
  // communicator. (We perform three shifts, for example.)
  perform_shift(uk, N, 3, MPI_COMM_WORLD);

  // shifting complete. have each process print its chunk
  printf("\n[%d] Shifted Data array:\n", rank);
  print_array(uk, N);
  printf("\n");

  // free and clean up
  free(uk);

  MPI_Finalize();
  return 0;
}
