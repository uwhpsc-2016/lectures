import numpy
import matplotlib.pyplot as plt

import ctypes
from ctypes import c_float, c_void_p, c_int, c_size_t

matmul = ctypes.cdll.LoadLibrary('./libmatmul.so')
matmul.time_naive.restype = c_float
matmul.time_naive.argtype = [c_size_t]
matmul.time_fast.restype = c_float
matmul.time_fast.argtype = [c_size_t]

def time_naive(n):
    return matmul.time_naive(n)

def time_fast(n):
    return matmul.time_fast(n)

if __name__ == '__main__':
    import matplotlib.pyplot as plt

    sizes = range(50,700,50)

    print "Timing naive..."
    naive_times = map(time_naive, sizes)

    print "Timing fast..."
    fast_times = map(time_fast, sizes)

    print "Saving plot in current directory..."
    plt.hold(True)
    p1, = plt.plot(sizes, naive_times, 'bo-', label='naive')
    p2, = plt.plot(sizes, fast_times, 'go-', label='fast')
    plt.legend([p1,p2])
    plt.savefig('./timings.png')
