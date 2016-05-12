#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>

int min(int* array, int length)
{
  int val = INT_MAX;
  for (int i=0; i<length; ++i)
    val = (array[i] < val ? array[i] : val);
  return val;
}

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);

  int rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // variables used by all processes
  //
  // each process has their own version of the array "data". the objective is to
  // compute the global minimum across each of these data arrays. this is done
  // in two steps:
  //
  // 1) each process computes their local min
  //
  // 2) communication is performed across all processes to compute the min
  // across these local minima to produce the global min
  //
  int Nproc = 100;  // each proc has this many random elements
  int data[Nproc];  // data array
  int local_min;    // local min
  int global_min = 0;   // storage for global min
  srand((long) time(NULL) + rank);
  for (int i=0; i<Nproc; ++i)
    data[i] = rand();

  // compute the local minimum within the current process using only its data.
  // (Again, this data is unavailable to the other processes)
  //
  local_min = min(data, Nproc);

  printf("[%d] local minimum  = %d\n", rank, local_min);

  // call MPI_Reduce using the MPI_MIN op and store result in Proc 0's
  // "global_min" variable
  //
  // MPI will evviciently communicate the local_minima to other processes and
  // keep track of the minimum across these communications. eventually, the
  // global minimum reaches process 0, in this case,
  //
  //         send        recv         len type     op       root
  MPI_Reduce(&local_min, &global_min, 1,  MPI_INT, MPI_MIN, 0,
             MPI_COMM_WORLD);

  // print the result, which is only stored in process zero's global_min
  if (rank == 0)
    printf("\n[0] global minimum = %d\n", global_min);

  MPI_Finalize();

  return 0;
}
