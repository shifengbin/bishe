.SUFFIXES:.c .o
SRC=hashlist.c main.c
OBJ=$(SRC:.c=.o)
EXE=main
CC=gcc

start:$(OBJ)
	$(CC) $(OBJ) -o $(EXE)
.c.o:
	$(CC) -c $< -o $@

clean:
	rm *.o
