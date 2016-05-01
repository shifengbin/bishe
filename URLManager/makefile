.SUFFIXES:.cpp .o
SRC= URLManager.cpp
# URLManagerMain.cpp
OBJ=$(SRC:.cpp=.o)
CC=g++
start:$(OBJ)
	mv *.o ../Debug
.cpp.o:
	$(CC) -c $< -o $@	
