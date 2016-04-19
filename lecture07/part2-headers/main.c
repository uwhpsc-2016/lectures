
#include <stdio.h>
#include "sub1.c"
#include "sub2.c"

int main()
{
  printf("In main\n");
  sub1();
  sub2();
  return 0;
}

