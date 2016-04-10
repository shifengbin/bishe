.SUFFIXES:.cpp .o
SRC=QueueMain.cpp 
OBJ=$(SRC:.cpp=.o)
#EXE=main
CC=g++

start:$(OBJ)
#	$(CC) $(OBJ) -o $(EXE)
	mv *.o ../Debug
.cpp.o:
	$(CC) -c $< -o $@

clean:
	rm *.o
