# Notes for Demo

1. Run from americano
2. Oneliner, single machine

   ```
   $ mpiexec -H americano.amath.washington.edu ./hello
   $ mpiexec -H latte.amath.washington.edu ./hello
   ```
      
3. Oneliner, multiple machines

   ```
   $ mpiexec -n 2 -H americano.amath.washington.edu,latte.amath.washington.edu ./hello
   $ mpiexec -n 4 -H americano.amath.washington.edu,latte.amath.washington.edu ./hello
   ```
      
4. Using hostfile

   ```
   #hostfile
   americano.amath.washington.edu
   latte.amath.washington.edu
   ```

5. (One more time with shift demo.)
