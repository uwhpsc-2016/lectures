#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned int digits_naive(unsigned long v) {
  unsigned int result = 0;
  do
    {
      ++result;
      v /= 10;   // very costly
    } while (v);
  return result;
}

unsigned int digits_fast(unsigned long v) {
  unsigned int result = 1;

  // appears to be an infinite loop but will always terminate because one of the
  // return conditions below will eventually be true
  for (;;)
    {
      // assume that "most numbers are small". comparison is very cheap.
      if (v < 10) return result;
      if (v < 100) return result + 1;
      if (v < 1000) return result + 2;
      if (v < 10000) return result + 3;

      // Skip ahead by 4 orders of magnitude. division costs the same no matter
      // how large the number
      v /= 10000U;
      result += 4;
    }
  return result;
}



float time_digits_function(
    unsigned int (func)(unsigned long),
    int number_calls, unsigned long upper_bound)
{
  // create a list of random numbers. note that there is an upper bound on the
  //stack size that limits number_calls to a number less than 10,000,000
  //
  //unsigned long random_ints[number_calls];
  unsigned long* random_ints = (unsigned long*)malloc(number_calls*sizeof(unsigned long));
  srand(0);
  for (size_t i=0; i<number_calls; ++i)
    random_ints[i] = rand() % upper_bound;

  // time the function calls
  clock_t elapsed;
  float seconds;
  elapsed = clock();
  for (int i=0; i<number_calls; ++i)
    func(random_ints[i]);
  elapsed = clock() - elapsed;
  seconds = (float) elapsed / CLOCKS_PER_SEC;
  return seconds;
}


int main(int argc, char** argv)
{
  // get number of interations and upper bound from command line
  unsigned int number_calls = 100;
  unsigned long upper_bound = 1000000000;
  if (argc > 1)
    number_calls = atoi(argv[1]);
  if (argc > 2)
    upper_bound = atoi(argv[2]);

  float time_naive, time_fast;
  time_naive = time_digits_function(digits_naive, number_calls, upper_bound);
  time_fast = time_digits_function(digits_fast, number_calls, upper_bound);

  printf("naive: %f sec\n", time_naive);
  printf("fast:  %f sec\n", time_fast);
  printf("improvment factor: %f\n", time_naive/time_fast);
}
