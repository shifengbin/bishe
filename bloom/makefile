.SUFFIXES:.c .o
SRC=bloom.c hash.c main.c
OBJ=$(SRC:.c=.o)
EXE=main
CC=gcc
start:$(OBJ)
	$(CC) $(OBJ) -o $(EXE)
.c.o:
	$(CC) -c $< -o $@

clean:
	rm *.o	
