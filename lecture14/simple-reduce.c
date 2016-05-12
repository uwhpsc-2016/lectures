#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>


int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);

  int rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // variables used by all processes
  //
  // each process comptues / has their own version of value. the objective is to
  // compute the sum across these versions and store the result in some process
  // (here, process 0)
  srand(rank);
  int value = ((int) rand()) % 10;
  int sum = 0;
  printf("[%d] value = %d\n", rank, value);

  // each process "calls" MPI_Reduce. here, only Proc 0 is requesting the result
  // of MPI_SUM which will be stored in its copy of the variable `sum`.
  //
  //         send    recv  len type     op       root comms
  MPI_Reduce(&value, &sum, 1,  MPI_INT, MPI_SUM, 0,   MPI_COMM_WORLD);

  // have Proc 0 print the result of the reduce. (any other proc will print 0)
  //
  // we include MPI_Barrier here only to make the print statements sync up. That
  // is, we want the printing of "values" to come before the printing of the
  // results
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0)
    {
      printf("[0] sum   = %d\n", sum);
    }
  else
    {
      printf("[%d] wrong = %d\n", rank, sum);
    }

  MPI_Finalize();
  return 0;
}

