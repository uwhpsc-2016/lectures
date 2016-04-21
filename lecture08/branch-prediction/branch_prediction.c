#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline int compare(const void * a, const void * b)
{
  const long* da = (const long*)a;
  const long* db = (const long*)b;
  return (*da - *db);
}

int main(int argc, char** argv)
{
  printf("\n===== Branch Prediction Example =====\n");

  /* // create a random array */
  /* size_t size = 32; */
  /* if (argc > 1) */
  /*   size = atoi(argv[1]); */
  /* long* array = malloc(size * sizeof(long)); */
  const size_t size = 262144; // = 2**18
  long array[size];
  srand(0);
  for (int n=0; n<size; ++n)
    array[n] = (long)rand() % 256;

  // count the number of elements above a certain threshold
  // 1) UNSORTED
  long threshold = 0;
  long sum = 0;
  clock_t time_start, time_end;
  float seconds;
  time_start = clock();
  for (size_t n=0; n<size; ++n)
    if (array[n] <= 128)
      {
        threshold += 1;
        sum += array[n];
      }
  time_end = clock();
  seconds = (double)(time_end - time_start)/CLOCKS_PER_SEC;
  printf("Num below threshold: %ld\n", threshold);
  printf("Sum:                 %ld\n", sum);
  printf("Elapsed time:        %fs\n", seconds);

  // 2) SORTED
  threshold = 0;
  sum = 0;
  qsort(array, size, sizeof(long), compare);
  time_start = clock();
  for (size_t n=0; n<size; ++n)
    if (array[n] <= 128)
      {
        threshold += 1;
        sum += array[n];
      }
  time_end = clock();
  seconds = (double)(time_end - time_start)/CLOCKS_PER_SEC;
  printf("Num below threshold: %ld\n", threshold);
  printf("Sum:                 %ld\n", sum);
  printf("Elapsed time:        %fs\n", seconds);

  return 0;
}


