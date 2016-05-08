.SUFFIXES:.c .o
.SUFFIXES:.cpp .o

SRC=sockutils.c
#SRC1=SockToolMain.cpp
OBJ=$(SRC:.c=.o)
#OBJ1=$(SRC1:.cpp=.o)
#EXE=SockToolMain

start:$(OBJ)
# $(OBJ1)
#	g++ $(OBJ) $(OBJ1) -o $(EXE) -g
	mv *.o ../Debug
.c.o:
	gcc -c $< -o $@ -g
.cpp.o:
	g++ -c $< -o $@ -g

clean:
	rm *.o
