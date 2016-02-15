# Demonstrating the Use of `enable_if`

## Compiling

To compile and run this demo:

```C++
$ g++ --std=c++11 ./main.cpp
$ ./a.out
0 1 1 0 0 0 0 0 0 0
1 5 0 2 0 8 2 2 8 2
0.0850324 0.891611 0.18969 0.398008 0.743512 0.56039 0.809567 0.511713 0.995085 0.966611
```

## Explanation

This demo shows how to use the metafunction `enable_if` to manipulate
[SFINAE](http://en.cppreference.com/w/cpp/language/sfinae) as a function of
template type traits.

In the demo we create three different vectors of different types. In the case
when the type is integral we want to return a uniform random vector with numbers
from 0 to 9. In the case when the type is floating point we return a uniform
random vector with numbers in the inteval `[0,1]`.

The tricky part is that the choice of distribution is not generic. That is, to
construct distributions on integer types you use `uniform_int_distribution`
whereas real distribution are defined using `uniform_real_distribution`. Here,
we choose a different version of `create_random_vector` based on the type by
writing

```C++
template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
create_random_vector(size_t length, unsigned seed = 0)
{
  uniform_int_distribution<T> u(0,9);
  ...
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::vector<T>>::type
create_random_vector(size_t length, unsigned seed = 0)
{
  uniform_real_distribution<T> u(0,1);
  ...
}
```

So if the user requests a random vector of type `double` then the second version
of the function is used. There are better ways to write an equivalent behavior.
However, the purpose of this program is to learn how to use `enable_if`.
