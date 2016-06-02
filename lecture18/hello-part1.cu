#include <stdio.h>
#include <cuda.h>

__global__ void cuda_hello(void)
{
  // print a character buffer from the GPU!
  printf("Hello, world!\n");
}

int main(void)
{
  printf("Calling cuda_hello...\n");

  // call the CUDA kernel from the GPU
  cuda_hello<<<1,1>>>();

  // wait for the kernel to finish
  cudaDeviceSynchronize();
  printf("...device synchronized.\n");

  return 0;
}
