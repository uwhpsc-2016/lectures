# Branch Prediction

[Branch prediction](https://en.wikipedia.org/wiki/Branch_predictor) is a
technique used by modern CPUs and compilers to attempt to guess the outcome of a
conditional statement in order to improve the flow of the CPU's
[instruction pipeline](https://en.wikipedia.org/wiki/Instruction_pipelining).

This simple example demonstrates the benefits of organizing your data to take
advantage of instruction pipelining. To run:

```
$ gcc ./main.c && ./a.out
```

Note that it takes less time (about a quarter the amount of time on my machine)
to "process" the sorted array than the unsorted one. This is because the
conditional statement

```c
if (array[n] <= 128)
  {
  ...
  }
```

is true for about half the data and false for about half. Whenever the result of
the conditional is `true` the CPU will assume that it's `true` for the next
iteration of the loop. It will load the instruction that follows in the `true`
case while simultaneously checking if the conditional is indeed `true`.

Now here's something interesting: turn on level-3 optimization when compiling
and see what happens:

```
$ gcc -O3 ./main.c && ./a.out
```

You should observe that the unsorted and sorted loops run in approximately the
same amount of time. This is because, in addition to the other optimizations
applied, the conditional "if `array[n] <= 128` then do X" is transformed into a
"branchless instruction".
