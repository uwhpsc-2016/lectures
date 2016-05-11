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
  int N_partition = N / (world_size - 1);

  if (world_rank == 0)
    {
      // create random data
      int data[N];
      srand((long) time(NULL));
      for (int i=0; i<N; ++i)
        data[i] = rand();

      // store local minima
      int local_minima[world_size-1];

      // send chunk of data array to each _other_ process
      for (id=1; id<world_size; ++id)
        {
          printf("Proc 0 --- sending data to proc %d\n", id);
          MPI_Send(&data[(id-1)*N_partition], N_partition,
                   MPI_INT, id, 0, MPI_COMM_WORLD);
        }

      // receive results from other procs
      for (id=1; id<world_size; ++id)
        {
          printf("Proc 0 --- receiving data from proc %d\n", id);
          MPI_Recv(&local_minima[id-1], 1, MPI_INT,
                   id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

      // compute minimum
      printf("\n ====== REPORT =======\n");
      minimum = min(local_minima, world_size-1);
      printf("min = %d\n", minimum);

      minimum = min(data, N);
      printf("min = %d\n", minimum);
    }
  else
    {
      int values[N_partition];
      int local_minimum;

      // populate values with incoming data from proc 0
      printf("Process %d --- receiving from proc 0\n",
             world_rank);
      MPI_Recv(values, N_partition, MPI_INT, 0, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      // find local min in this subarray
      local_minimum = min(values, N_partition);

      // send local min back to proc 0
      printf("Process %d --- sending to proc 0\n",
             world_rank);
      MPI_Send(&local_minimum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

  MPI_Finalize();

  return 0;
}
