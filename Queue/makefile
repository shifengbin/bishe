.SUFFIXES:.cpp .o
SRC=main.cpp 
OBJ=$(SRC:.cpp=.o)
EXE=main
CC=g++

start:$(OBJ)
	$(CC) $(OBJ) -o $(EXE)
.cpp.o:
	$(CC) -c $< -o $@

clean:
	rm *.o
