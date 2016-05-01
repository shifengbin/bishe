.SUFFIXES:.c .o
SRC=bloom.c 
#SRC1=BloomMain.cpp
OBJ=$(SRC:.c=.o)
#OBJ1=$(SRC1:.cpp=.o)
#EXE=main
CC=gcc
CXX=g++
start:$(OBJ)
#	$(CXX) $(OBJ) $(OBJ1) -o $(EXE) -L../Debug
	mv *.o ../Debug
.c.o:
	$(CC) -c $< -o $@
#.cpp.o:
#	$(CXX) -c $< -o $@

clean:
	rm *.o	
