.SUFFIXES:.c .o
SRC=bloom.c hash.c 
SRC1=main.cpp
OBJ=$(SRC:.c=.o)
OBJ1=$(SRC1:.cpp=.o);
EXE=main
CC=gcc
start:$(OBJ) $(OBJ1)
	g++ $(OBJ) -o $(EXE)
.c.o:
	$(CC) -c $< -o $@
.cpp.o:
	g++ -c $< -o $@

clean:
	rm *.o	
