
double square(double number)
{
  return number*number;
}

// squares all of the elements of an array
void squares(double* array, int N)
{
  for (int i=0; i<N; ++i)
    array[i] = square(array[i]);
}
