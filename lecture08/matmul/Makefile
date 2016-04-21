# matmul makefile

default:
	gcc matmul.c main.c -o main.exe

main.exe: libmatmul.so
	gcc -I. -c main.c -o main.o
	gcc main.o -o main.exe -lmatmul -L. 

plot: libmatmul.so
	python timings.py

libmatmul.so:
	gcc -fPIC -shared matmul.c -o libmatmul.so

clean:
	rm -f ./main.exe ./main.o
	rm -f ./libmatmul.so
	rm -f ./*~
