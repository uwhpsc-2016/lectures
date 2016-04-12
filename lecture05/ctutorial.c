#include <stdio.h>
#include <stdlib.h>


// when writing an executable (C code that runs from the command line) the
// function named "main" is the entry point
int main(int argc, char** argv)
{
  // hello world
  printf("Hello, world!\n");

  // defining several variables
  int num_threads = 2;
  long problem_size = 200L;
  float delta_t = 0.1;
  double temperature = 123.456;

  // printing to stdout (the terminal). the "printf()" function is defined in
  // the stdio.h header. the %x parts are called "format specifiers" and allow
  // you to print variable values
  //
  printf("the number of threads: %d\n", num_threads);
  printf("the problem size: %ld\n", problem_size);
  printf("delta_t value: %f\n", delta_t);
  printf("current temperature: %f\n", temperature);
  printf("current temperature: %e\n", temperature); // scientific notation
  // (after we talk about pointers: %p for pointer addresses)

  // conditional statements:
  // if (condition)
  // {
  //   code;
  // }
  // else if (condition)
  // {
  //   code;
  // }
  // else
  // {
  //   code;
  // }
  if (num_threads > 2) {
    printf("more than two threads\n");
  } else if (delta_t <= 0.1) {
    printf("small delta t\n");
  } else {
    printf("got nothing\n");
  }

  // operations
  // things will be coerced to target type, if possible
  double something = temperature * delta_t + num_threads;
  printf("something = %f\n", something);
  long index = 1;
  index += 1; // equal to 2
  ++index;    // equal to 3 (prefix)
  index++;    // equal to 4 (postfix)
  printf("index = %ld\n", index);

  // for loops
  //
  // for (initializer; test; incrementer)
  // {
  //   code;
  // }
  //
  // you can initialize new variables in the "initializer" as well
  printf("\nTesting a for loop:\n");
  for (int j=0; j<3*index; j=j+2) {
    printf("\tj = %d\n", j);
  }

  // while loops
  //
  // while (condition)
  // {
  //   code;
  // }
  //
  // be very careful of infinite loops!
  // if necessary, use whitespace to make statements clearer
  printf("\nTesting a while loop:\n");
  while (
         ((delta_t < 1.1) && (index > 0))
         ||
         !(temperature < 10000000)
         )
    {
      printf("\tdt = %f\n", delta_t);
      delta_t += 0.2;
    }

  // a note on conditionals: c1 && c2 is "and", c1 || c2 is "or". "not" is given
  // by !(c1)


  // compile-time arrays
  //
  // if the size of the array is known at compile-time then creating an array is
  // as simple as follows
  double vector[6];

  // populate vector
  for (int i=0; i<6; ++i)
    vector[i] = ((double)i) / 2.0;

  // print vector elements
  printf("\nmy vector: ");
  printf("[");
  for (int i=0; i<6; ++i)
    printf(" %f,", vector[i]);
  printf("]\n");

  // we can also initialize using an "initializer list". however, there is no
  // such thing as "len()" in C
  int ages[] = {41, 27, 30, 18, 72};
  for (int i=0; i<5; ++i)
    printf("age[%d] = %d\n", i, ages[i]);
}
