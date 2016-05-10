#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);

  /*
    message passing function prototypes

    MPI_Send(
        void* data,
        int count,
        MPI_Datatype datatype,
        int destination,
        int tag,
        MPI_Comm communicator)

    MPI_Recv(
        void* data,
        int count,
        MPI_Datatype datatype,
        int source,
        int tag,
        MPI_Comm communicator,
        MPI_Status* status)

    * data - the data buffer. that which is sent / received
    * count - the number of elements in the data buffer
    * datatype - the type of the elements int eh data buffer
    * destination / source - the rank of the receiver / original sender
    * tag - used to classify / tag certain types of messages
    * communicator - the communicator containing the participating processes
    * status - provides information about the received message
  */

  // determine size and rank of current process. sometimes people store info in
  // variables called "rank" and "size""
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // have process 0 send the number 42 to process 1. the variable "value" is
  // initialized to zero in both processes
  int value = 0;
  if (world_rank == 0) // only have process zero execute this block
    {
      // send a message to 1. note that the other branch doesn't know about the
      // setting of value to 42 because it is a completely separate process
      value = 42;
      printf("Process 0 --- sending [%d] to process 1...\n", value);

      //       data    n  type   dest tag communicator
      MPI_Send(&value, 1, MPI_INT, 1,  0, MPI_COMM_WORLD);
      printf("Process 0 --- ...send complete.\n");

      // reset "value" (see last print statment)
      value = 0;
    }
  else if (world_rank == 1) // this block is executed only by process 1
    {
      // receive a message from 0
      //
      // currently, process 1 doesn't know about the setting of value to "42"
      // until it receives this information via "MPI_Recv"
      printf("Process 1 --- currently value = %d\n", value);
      printf("Process 1 --- receiving from process 0...\n");

      //       data    n  type    src tag communicator    status
      MPI_Recv(&value, 1, MPI_INT, 0,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Process 1 --- received [%d] from process 0.\n", value);

      // reset "value" (see last print statment)
      value = 1;
    }

  // have each processor identify themselves: both processes execute this codex
  printf("\n === Goodbye from process %d! (value = %d) === \n\n",
         world_rank, value);

  MPI_Finalize();

  return 0;
}
