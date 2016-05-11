#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);

  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int value = 0;

  if (world_rank == 0)
    {
      // only executed by Proc 0
      value = 42;

      printf("Process 0 --- sending [%d] to process 1...\n", value);
      //       data    n  type   dest tag communicator
      MPI_Send(&value, 1, MPI_INT, 1,  0, MPI_COMM_WORLD);

      printf("Process 0 --- ...finished sending.\n");
      value = 0;
    }
  else if (world_rank == 1)
    {
      // only executed by Proc 1
      printf("Process 1 --- current value = %d\n", value);
      printf("Process 1 --- receiving from process 0...\n");

      MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

      printf("Process 1 --- ...received value = %d\n", value);

      value = 1;
    }

  printf("\n ===== Goodbye from process %d (value = %d) ==== \n",
         world_rank, value);

  MPI_Finalize();

  return 0;
}
