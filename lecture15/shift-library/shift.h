
/*
  perform_shift

  Given an MPI communicator, `comm`, and data arrays `uk` on each process of
  length `N` shift the data in these arrays by `num_shifts`.

  This function "orders" the processes in `comm` such that the data at process
  `k` (`uk`) lies between process `k-1` and process `k+1`.

  Parameters
  ----------
  uk : long array
      An data array corresponding to process `k`.
  N : size_t
      The length of `uk`.
  num_shifts : long
      The number of times to shift the data in the arrays to the right.
  comm : MPI_Comm
      A communicator containing the processes with the `uk` data. See
      description for assumed topology.

  Returns
  -------
  None
      Modifies `uk` in-place.
 */
void perform_shift(long* uk, size_t N, long num_shifts, MPI_Comm comm);
