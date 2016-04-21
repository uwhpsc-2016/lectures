# matmul makefile

main: libmatmul.so
	gcc -I. -L. -lmatmul main.c -o main

plot: libmatmul.so
	python timings.py

libmatmul.so:
	gcc -fPIC -shared matmul.c -o libmatmul.so
