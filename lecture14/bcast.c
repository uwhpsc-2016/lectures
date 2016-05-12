#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
  int rank, world_size;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // every proc declares "buff" but only "proc 0" initializes it
  int data = 0;
  if (rank == 0)
    data = 42;

  printf("[PRE-BCAST] Proc %d --- data = %d\n", rank, data);

  // common confusion with Bcast: everyone calls bcast. however, the input data
  // is from the specified process. everyone will receive that data. note that
  // only proc 0 set data = 42. additionally, everyone also has a copy of "data"
  //
  //        buffer len type     source_proc communicator
  MPI_Bcast(&data, 1,  MPI_INT, 0,          MPI_COMM_WORLD);

  printf("[POST-BCAST] Proc %d --- data = %d\n", rank, data);

  MPI_Finalize();
  return 0;
}
