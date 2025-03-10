
CC = gcc

output: ray.o raytracer1b.o camera.o vector.o colorType.o shapes.o light.o vecList.o ppmReader.o
	$(CC) shapes.o light.o colorType.o vector.o camera.o ray.o vecList.o ppmReader.o raytracer1b.o -o raytracer1b -lm

raytracer1b.o: raytracer1b.c
	$(CC) -c raytracer1b.c

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
ppmReader.o: ppmReader.c ppmReader.h
	$(CC) -c ppmReader.c
clean:
	rm *.o raytracer1b
run:
	make
	./raytracer1b

vecList.o: vecList.h vecList.c
	$(CC) -c vecList.c

test.o: test.c
	$(CC) -c test.c

test: test.o vector.o vecList.o
	$(CC) test.o vector.o vecList.o -o test -lm
	
