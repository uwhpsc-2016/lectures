main.exe: libsubs.so 
	gcc -L. -lsubs main.c -o main.exe 

libsubs.so: sub1.o sub2.o 
	gcc -shared -o libsubs.so sub1.o sub2.o 

main.o: main.c
	gcc -c main.c 
sub1.o: sub1.c 
	gcc -c -fPIC sub1.c 
sub2.o: sub2.c 
	gcc -c -fPIC sub2.c
