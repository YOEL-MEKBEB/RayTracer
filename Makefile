
CC = gcc

output: ray.o raytracer1a.o camera.o vector.o colorType.o shapes.o light.o
	$(CC) shapes.o light.o colorType.o vector.o camera.o ray.o raytracer1a.o -o raytracer1a -lm

raytracer1a.o: raytracer1a.c
	$(CC) -c raytracer1a.c

ray.o: ray.c ray.h
	$(CC) -c ray.c

camera.o: camera.h camera.c
	$(CC)  -c camera.c

vector.o: vector.h vector.c
	$(CC) -c vector.c

colorType.o: colorType.h colorType.c
	$(CC) -c colorType.c

shapes.o: shapes.h shapes.c
	$(CC) -c shapes.c
light.o: light.h light.c
	$(CC) -c light.c
clean:
	rm *.o raytracer1a
run:
	make
	./raytracer1a
