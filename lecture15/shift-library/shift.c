#include <mpi.h>

#include "shift.h"

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
