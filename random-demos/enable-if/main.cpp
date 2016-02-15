#include <vector>
#include <random>
#include <iostream>
#include <type_traits>
#include <complex>

using namespace std;
using std::cout;
using std::endl;

/*
  std::vector<T> create_random_vector(size_t length)

  Creates and returns a random vector.

  Returns a vector of length `length` of type `T` filled with random elements.
  If `T` is integer type then the elements will be uniformly distributed from 0
  to 9. Otherwise, real type values will be uniformly distributed on the
  half-open interval [0,1).

  Parameters
  ----------
  length : size_t
      The desired length of the output vector.
  seed : unsigned
      (Default: 0) Seed for the random number generator. 

  Template Parameters
  -------------------
  T : typename
      The type of the output vector. This affects which random number
      distribution is used in the construction of the vector. (See above.)

  Returns
  -------
  v : vector<T>
      A random vector.
 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
  create_random_vector(size_t length, unsigned seed = 0)
{
  uniform_int_distribution<T> u(0,9);
  default_random_engine e(seed);
  vector<T> v(length);

  for (size_t i=0; i<length; ++i)
    {
      v[i] = u(e);
    }
  return v;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::vector<T>>::type
create_random_vector(size_t length, unsigned seed = 0)
{
  uniform_real_distribution<T> u(0,1);
  default_random_engine e(seed);
  vector<T> v(length);

  for (size_t i=0; i<length; ++i)
    {
      v[i] = u(e);
    }
  return v;
}



/*
  Main Program

  Create three vectors of different types and print to terminal.

  This code demonstrates the use o fstd::enable_if behavior defined above. Also
  does some simple command line parsing: the first (optional) argument is the
  desired vector length, the second (optional) argument is the seed for the
  random number generator.
*/
int main(int argc, char** argv)
{

  // determine the size of the vector as well as the random seed from the
  // command line
  size_t size = 10;
  unsigned seed = 0;
  if (argc >= 2)
    {
      size = atoi(argv[1]);
    }
  if (argc >= 3)
    {
      seed = atoi(argv[2]);
    }

  /*
    create three random vectors of various types and print to screen
  */
  std::vector<bool> u = create_random_vector<bool>(size, seed);
  for (size_t i=0; i<size; ++i)
    {
      cout << u[i] << " ";
    }

  cout << endl;

  std::vector<unsigned> v = create_random_vector<unsigned>(size, seed);
  for (size_t i=0; i<size; ++i)
    {
      cout << v[i] << " ";
    }

  cout << endl;

  std::vector<double> w = create_random_vector<double>(size, seed);
  for (size_t i=0; i<size; ++i)
    {
      cout << w[i] << " ";
    }

  cout << endl;
  return 0;
}
