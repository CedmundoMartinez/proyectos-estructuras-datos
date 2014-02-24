# La siguiente no es necesariamente requerida, se agrega para
# mostrar como funciona.

.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) $<

CC = gcc
CFLAGS = -g -Wall -O2 -DUSE_STATIC_STACK -DSTACK_TYPE=char -DSTACK_STATIC_SIZE=16
SRC = main.c stacky.c postfixy.c
OBJ = main.o stacky.o postfixy.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

clean:
	$(RM) $(OBJ) main

stacky.o: stacky.c stacky.h
postfixy.o: postfixy.c postfixy.h
main.o: main.c stacky.h postfixy.h