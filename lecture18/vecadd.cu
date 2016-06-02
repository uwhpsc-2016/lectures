#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

/*
  print_array

  Helper function for printing integer arrays of specified length.
*/
void print_array(int* array, size_t length)
{
  printf("[");
  for (size_t i=0; i<length; ++i)
    printf(" %d,", array[i]);
  printf("]\n");
}

/*
  vec_add

  Kernel (device-side) function for computing the sum of two arrays.
 */
__global__ void vec_add(int* out, int* v, int* w)
{
  size_t index = threadIdx.x;
  out[index] = v[index] + w[index];
}



int main(void)
{
  printf("Allocating host-side arrays...");
  size_t N = 16;
  size_t size = N*sizeof(int);
  int* v = (int*) malloc(size);
  int* w = (int*) malloc(size);
  int* out = (int*) malloc(size);

  for (size_t i=0; i<N; ++i)
    {
      v[i] = i;
      w[i] = N-i;
    }
  printf("...done.\n");


  printf("Allocating device-side arrays...");
  int* dev_v;
  int* dev_w;
  int* dev_out;
  cudaMalloc((void**) &dev_v, size);
  cudaMalloc((void**) &dev_w, size);
  cudaMalloc((void**) &dev_out, size);
  printf("...done.\n");


  printf("Copying input host-side arrays to device-side arrays...");
  cudaMemcpy(dev_v, v, size, cudaMemcpyHostToDevice);
  cudaMemcpy(dev_w, w, size, cudaMemcpyHostToDevice);
  printf("...done.\n");


  printf("Calling vec_add kernel...");
  vec_add<<<1,N>>>(dev_out, dev_v, dev_w);
  printf("...done.\n");


  // wait for the kernel to finish
  cudaError_t cudaerr = cudaDeviceSynchronize();
  printf("\t[error message: \"%s\".]\n",
         cudaGetErrorString(cudaerr));


  printf("Copying device-side result to host-side array...");
  cudaMemcpy(out, dev_out, size, cudaMemcpyDeviceToHost);
  printf("...done.\n");


  printf("Printing host-side result...\n\n");
  print_array(out, N);
  printf("\n...done.\n");


  printf("Freeing device-side arrays...");
  cudaFree(dev_v);
  cudaFree(dev_w);
  cudaFree(dev_out);
  printf("...done.\n");


  printf("Freeing host-side arrays...");
  free(v);
  free(w);
  free(out);
  printf("...done.\n");

  return 0;
}
