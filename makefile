SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: main.o body.o
	gcc main.o body.o -o program $(SDLFLAGS)
	./program

main.o: main.c main.h
	gcc -c main.c $(shell sdl2-config --cflags)

body.o: body.c body.h
	gcc -c body.c $(shell sdl2-config --cflags)


test: test.c
	gcc test.c -o test $(SDLFLAGS)
	./test
	

