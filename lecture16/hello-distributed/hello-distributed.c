#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  MPI_Init(NULL,NULL);

  int proc_id;
  int num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int processor_name_length;
  MPI_Get_processor_name(processor_name, &processor_name_length);
  printf("Hello from proc %d of %d on processor %s.\n",
         proc_id, num_procs, processor_name);

  MPI_Finalize();
}
