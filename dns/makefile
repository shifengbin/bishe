.SUFFIXES:.c .o
SRC=dns.c DNSMain.c
OBJ=$(SRC:.c=.o)
EXE=main
start:$(OBJ)
#	gcc $(OBJ) -o $(EXE) -g
	mv *.o ../Debug
.c.o:
	gcc -c $< -o $@ -g
clean:
	rm *.o
