#include <stdio.h>
#include <cuda.h>

__global__ void cuda_hello(void)
{
  // print a character buffer from the GPU!
  printf("Hello, world, from thread %d, block %d!\n",
         threadIdx.x, blockIdx.x);
}

int main(void)
{
  printf("Calling cuda_hello...\n");

  // call the CUDA kernel from the GPU
  cuda_hello<<<2,4>>>();

  // wait for the kernel to finish
  cudaError_t cudaerr = cudaDeviceSynchronize();
  if (cudaerr)
    printf("error message: \"%s\".\n", cudaGetErrorString(cudaerr));

  printf("...device synchronized.\n");

  return 0;
}
