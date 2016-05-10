#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  // initialize the MPI environment. must be the first MPI call
  MPI_Init(NULL,NULL);

  // get the number of processes
  int num_procs;
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // get the "rank" of the current process. Each process in the communicator is
  // running the same code but is assigned a different "rank" or "id"
  int proc_id;
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

  // identify yourself, program
  printf("Hello from proc %d of %d.\n", proc_id, num_procs);

  /*
  // (optionally) get the name of the processor and print it
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int processor_name_length;
  MPI_Get_processor_name(processor_name, &processor_name_length);
  printf("Hello from proc %d of %d on processor %s.\n",
         proc_id, num_procs, processor_name);
  */

  // clean up the MPI environment
  MPI_Finalize();
}
