#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

void print_array(long* array, size_t length)
{
  printf("[");
  for (size_t i=0; i<length; ++i)
    printf(" %ld,", array[i]);
  printf("]\n");
}


/*
  shift.c
  =======

  This MPI code does the following:

  * Each process allocates some data array of its own: "uk"

  * The processes spawned will establish a "left" process and a "right" process
    with which to communicate. That is, if the current process is of rank "rank"
    it will only communicate with process "(rank-1)" and process "(rank+1)".
    This communication wraps around: that is, if there are S processes then the
    rank "0" process communicates with the rank "S-1" process and the rank "1"
    process.

  * The data within the array will be shifted one space to the right. *However*,
    we want the element at the right-end of the array to be sent to the "right"
    process's data array. As a result, we want to take then endpoint of the
    "left" process and place it in the beginning of the current process's array.

    For example, let the arrays below represent the data in some "adjacent"
    processes

      Proc0        Proc1        Proc2
    [a, b, c]    [d, e, f]    [g, h, i]

    After one shift we want the data to be

           Proc0        Proc1        Proc2
         [i, a, b]    [c, d, e]    [f, g, h]
     --->        --->         --->          --->
     |            c            f               |
     |_________________________________________|
                          i

    The arrows represent the explicit communcation of data between the involved
    processes.

  * Furthermore, the number of shifts can be made arbitrary via command line argument.
 */
int main(int argc, char** argv)
{
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // each process knows how much to shift via the command line. This is because
  // of the use of MPI_Init above.
  long num_shifts = 1;
  if (argc > 1)
    num_shifts = atoi(argv[1]);

  // keep track of which process is to the "left" of the current process and
  // which process is to the "right". include wraparound
  int left_process = (rank-1+size) % size; // note that modulus "rounds" to zero
  int right_process = (rank+1) % size;
  MPI_Request req;
  MPI_Status stat;

  // Initialize some data
  //
  // Process 0 starts with: uk = [0, 1, ..., N]
  // Process 1 starts with: uk = [N, N+1, ..., 2*N-1]
  // ...
  // Process P-1 starts with: uk = [..., N*P-2, N*P-1]
  size_t N = 8;
  long* uk = (long*) malloc(N * sizeof(long));
  for (size_t i=0; i<N; ++i)
    uk[i] = rank*N + i;

  // we will use "ghost cells" to store the overlaps so that, with each
  // iteration of the shift, we can communicate the data from one process to the
  // "next" process
  //
  // the ghost is initialized to the right endpoint of uk (since we are shifting right)
  long left_ghost, right_ghost = uk[N-1];

  // have each process print its chunk
  printf("\n[%d] Data array:\n", rank);
  print_array(uk, N);
  printf("\n");

  // *try* to force the print statements to make their way out now so that
  // *they're "well separated". this doesn't always work...
  MPI_Barrier(MPI_COMM_WORLD);
  fflush(stdout);

  for (long shift_count=0; shift_count<num_shifts; ++shift_count)
    {
      // communicate boundary data --- data is flowing from left to right
      //
      // the current process will send the right ghost cell data to the process
      // "on the right".
      printf("shift:%ld [%d -> %d] sending boundary data = %ld\n",
             shift_count, rank, right_process, right_ghost);
      MPI_Isend(&right_ghost, 1, MPI_LONG, right_process, 0, MPI_COMM_WORLD, &req);

      // the current process is receiving data from the process "on the left".
      // The data that it sent (which was *its* copy of right_ghost) will be
      // stored in *current* process's left_ghost variable
      MPI_Recv(&left_ghost, 1, MPI_LONG, left_process, 0, MPI_COMM_WORLD, &stat);
      printf("shift:%ld [%d <- %d] ...received data = %ld\n",
             shift_count, rank, left_process, left_ghost);

      // at this point in the code we have successfully communicated the
      // boundary data between processes:
      //
      // * left_ghost now contains the left process's boundary data (which was
      //   the left process's value of right_ghost)
      //
      // we will now shift the current process's data array / "internal cells"
      for (size_t i=N-1; i>=1; --i)
        uk[i] = uk[i-1];

      // next, take the left_ghost data and shift it "into" the "internal cells"
      uk[0] = left_ghost;

      // finally, set the new right_ghost (which is just a copy of the last
      // element of the array) for the purposes of communicating to the right
      // process in the next iteration of the loop
      right_ghost = uk[N-1];
    }

  // *try* to force the print statements to make their way out now so that
  // *they're "well separated". this doesn't always work...
  MPI_Barrier(MPI_COMM_WORLD);
  fflush(stdout);

  // shifting complete. have each process print its chunk
  printf("\n[%d] Shifted Data array:\n", rank);
  print_array(uk, N);
  printf("\n");

  // free and clean up
  free(uk);
  MPI_Finalize();
  return 0;
}
