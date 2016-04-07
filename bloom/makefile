.SUFFIXES:.c .o
SRC=bloom.c 
SRC1=main.cpp
OBJ=$(SRC:.c=.o)
OBJ1=$(SRC1:.cpp=.o)
EXE=main
CC=gcc
CXX=g++
start:$(OBJ) $(OBJ1)
	$(CXX) $(OBJ) $(OBJ1) -o $(EXE)
.c.o:
	$(CC) -c $< -o $@
.cpp.o:
	$(CXX) -c $< -o $@

clean:
	rm *.o	
