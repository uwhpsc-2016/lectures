#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/*
  deadlocking example

  run this with two processes
 */
int main(int argc, char** argv)
{
  int rank, world_size;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  /*
    things to try:

    * replace MPI_Send with MPI_Ssend
    * replace MPI_Send with MPI_Isend
    * replace one MPI_Send with MPI_SSend and other with MPI_Isend
    * (other conbinations of Send, Ssend, Isend, Recv, Irecv)
   */
  double value = 0.0;
  MPI_Request req;
  if (rank == 0)
    {
      // code only executed by process 0
      value = 0.1234;
      printf("[%d] value = %f\n", rank, value);
      MPI_Send(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
      MPI_Recv(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("[%d] value = %f\n", rank, value);
    }
  else if (rank == 1)
    {
      // code only executed by process 1
      value = 0.5678;
      printf("[%d] value = %f\n", rank, value);
      MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("[%d] value = %f\n", rank, value);
    }


  MPI_Finalize();
  return 0;
}
