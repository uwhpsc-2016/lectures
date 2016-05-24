#include <stdio.h>
#include <omp.h>

#define MAX_LEVEL 3

void report(int level)
{
  // force the contents to be performed only by a single thread within the
  // current thread group
  #pragma omp single
  {
    // get number of threads in current group
    int num_threads = omp_get_num_threads();
    int max_threads = omp_get_max_threads();
    for(int i=0; i<level; ++i)
      printf(" ");
    printf("Level: %d -- Threads in group: %d/%d\n", level, num_threads,
           max_threads);
  }
}

void nest(int level)
{
  // no-op if we reach the max level
  if (level == MAX_LEVEL)
    return;

  // spawn two threads and
  #pragma omp parallel num_threads(2)
  {
    report(level);
    nest(level + 1);
  }
}

int main()
{
  printf("===== nested.c =====\n");
  int max_threads = omp_get_max_threads();

  omp_set_dynamic(0);
  omp_set_nested(1);
  nest(0);
}
