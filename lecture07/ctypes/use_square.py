
import ctypes
from ctypes import c_void_p, c_int, c_double

# load the library
square_library = ctypes.cdll.LoadLibrary('./libsquare.so')

# SQUARE function
# establish input / output types of function
square_library.square.restype = c_double
square_library.square.argtypes = [c_double]

# call
print "Calling library function"
print square_library.square(2.0)


# SQUARES function
# establish input / output types of function
square_library.squares.restype = c_void_p
square_library.squares.argtypes = [c_void_p, c_int]

# call
import numpy
arr = numpy.array([1,2,3,4], dtype=numpy.double)

print "Calling library function"

square_library.squares(arr.ctypes.data, len(arr))

print arr


