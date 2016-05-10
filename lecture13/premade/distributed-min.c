#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>


// returns the minimum across an array
int min(int* array, long N)
{
  int minimum = INT_MAX;
  for (int i=0; i<N; ++i)
    minimum = (array[i] < minimum ? array[i] : minimum);
  return minimum;
}

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  /*
    process 0 -- moderator. creates data array. asks other available processes
    to find minimum in subarray

    process k -- finds minimum in subarray
   */

  // variables used by all processes
  int N = 1000;
  int minimum = INT_MAX;
  int id;

  if (world_rank == 0)
    {
      // create random data
      int data[N];
      srand((long) time(NULL));
      for (int i=0; i<N; ++i)
        data[i] = rand();

      // create space to store local minima from each other process
      int local_minima[world_size-1];

      // determine partition size: note that we're already using one process
      // (proc 0) for managing the group of processes
      //
      // if (world_size - 1) does not evenly divide N then bug. (simple example
      // for now / we won't pick such a world_size so let's not worry)
      int N_partition = N / (world_size - 1);

      // send chunk of data array to each other process
      for (id=1; id<world_size; ++id)
        {
          printf("Proc 0 --- sending to Proc %d\n", id);
          MPI_Send(&data[(id-1)*N_partition], N_partition, MPI_INT, id, 0,
                   MPI_COMM_WORLD);
        }

      // now receive local minima from other processes
      for (id=1; id<world_size; ++id)
        {
          printf("Proc 1 --- receiving from Proc %d\n", id);
          MPI_Recv(&local_minima[id-1], 1, MPI_INT, id, 0,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

      // finally, compute minimum across these local minima and report
      printf("\n===== REPORT =====\n\n");

      minimum = min(local_minima, world_size-1);
      printf("\tDistributed minimum: %d.\n", minimum);

      // compare with directly computing minimum
      minimum = min(data, N);
      printf("\tSerial minimum:      %d.\n", minimum);
    }
  else
    {
      // the following is executed by each other available process
      //
      // create space for incoming data chunk. first, determine partition size
      // (this could've been done by all processes outside this conditional
      // statement)
      long N_chunk = N / (world_size - 1);
      int values[N_chunk];
      int local_minimum;

      // populate array with incoming data
      printf("Proc %d --- receiving from Proc 0\n", world_rank);
      MPI_Recv(&values, N_chunk, MPI_INT, 0, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      // find minimum across these values
      local_minimum = min(values, N_chunk);

      // send values back to process 0
      printf("Proc %d --- sending to Proc 0\n", world_rank);
      MPI_Send(&local_minimum, 1, MPI_INT, 0, 0,
               MPI_COMM_WORLD);
    }

  MPI_Finalize();

  return 0;
}
