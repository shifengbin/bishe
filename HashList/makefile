.SUFFIXES:.c .o
SRC=hash.c hashlist.c 
#HashlistMain.c
OBJ=$(SRC:.c=.o)
#EXE=hashlistMain
CC=gcc

start:$(OBJ)
#	$(CC) $(OBJ) -o $(EXE)
	mv *.o ../Debug
.c.o:
	$(CC) -c $< -o $@

clean:
	rm *.o
