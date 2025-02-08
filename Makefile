
CC = gcc

output: ray.o test.o camera.o vector.o colorType.o
	$(CC) colorType.o vector.o camera.o ray.o test.o -o test

test.o: test.c
	$(CC) -c test.c

ray.o: ray.c ray.h
	$(CC) -c ray.c

camera.o: camera.h camera.c
	$(CC)  -c camera.c

vector.o: vector.h vector.c
	$(CC) -c vector.c

colorType.o: colorType.h colorType.c
	$(CC) -c colorType.c

clean: 
	rm *.o test