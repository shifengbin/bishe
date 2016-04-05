.SUFFIXES:.c .o
SRC=dns.c main.c
OBJ=$(SRC:.c=.o)
EXE=main
start:$(OBJ)
	gcc $(OBJ) -o $(EXE) -g
.c.o:
	gcc -c $< -o $@ -g
clean:
	rm *.o
