from mpi4py import MPI
import ctypes
import os
import numpy

from ctypes import c_int, c_long, c_void_p, c_double

# link to c library:
#
# deep down below, MPI_Comm types are represented by an integer
#
if MPI._sizeof(MPI.Comm) == ctypes.sizeof(c_int):
    MPI_Comm = ctypes.c_int
else:
    MPI_Comm = ctypes.c_void_p
libhello = ctypes.CDLL('libhello.so')
libhello.say_hello.restype = None
libhello.say_hello.argtypes = [ctypes.c_void_p, ctypes.c_size_t, MPI_Comm]


# call c library function with a communicator
def say_hello(comm):
    r"""Given a communicator, have each process in the communicator call
    say_hello().

    This Python function will be executed by each MPI process. Each will create
    its own copy of the data array `a` and send that array to the C function
    `say_hello()`.

    """
    comm_ptr = MPI._addressof(comm)
    comm_val = MPI_Comm.from_address(comm_ptr)

    N = 8
    a = numpy.ascontiguousarray(numpy.zeros(N, dtype=numpy.double))
    libhello.say_hello(a.ctypes.data, N, comm_val)

    print '%d ---- test: %s'%(comm.rank, a)
    if (comm.rank == 0):
        return a
    else:
        return None

# run mpi4py program
#
#     $ make lib
#     $ mpiexec -n 4 python hello.py
#
if __name__ == '__main__':
    from mpi4py import MPI
    import hello

    comm = MPI.COMM_WORLD

    arr = say_hello(comm)
    if comm.rank == 0:
        print "===== Running Test Script ====="
        print arr
