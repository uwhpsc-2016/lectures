#include <stdio.h>

int main(int argc, char** argv)
{
  // pointers...pointers...pointers
  //
  // probably the most important construct in C or any compiled programming
  // language. (PLEASE REFER TO NOTES AND REFERENCES)
  int a = 4;      // value:4,  address:&a
  int b = -1;     // value:-1, address:&b
  int* ptr = &a;  // value:&a, address:&ptr

  printf("a    = %d\n", a);
  printf("&a   = %p\n", &a);
  printf("ptr  = %p\n", ptr);
  printf("&ptr = %p\n", &ptr);
  printf("*ptr = %d\n\n", *ptr);

  *ptr = -1; // "that which is pointed to by ptr is now equal to -1"

  printf("*ptr = %d\n", *ptr);
  printf("a    = %d\n\n", a);

  // arrays and pointers
  int arr[4] = {27, 7, -12, 10};
  printf("arr[0] = %d\n", arr[0]);
  printf("arr[1] = %d\n", arr[1]);
  printf("arr[2] = %d\n", arr[2]);
  printf("arr[3] = %d\n\n", arr[3]);

  printf("arr = %p\n", arr);
  printf("arr+1 = %p\n", arr+1);
  printf("arr+2 = %p\n", arr+2);
  printf("arr+3 = %p\n\n", arr+3);

  printf("*(arr) = %d\n", *(arr));
  printf("*(arr+1) = %d\n", *(arr+1));
  printf("*(arr+2) = %d\n", *(arr+2));
  printf("*(arr+3) = %d\n\n", *(arr+3));

  // dark arts magic:
  printf("2[arr] = %d\n", 2[arr]);
  printf("arr  = %p\n", arr);
  printf("&arr = %p\n", &arr);
}
