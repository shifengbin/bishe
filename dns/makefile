.SUFFIXES:.c .o
.SUFFIXES:.cpp .o
SRC=dns.c 
SRC1=DNSCache.cpp
#DNSMain.c
OBJ=$(SRC:.c=.o) 
OBJ1=$(SRC1:.cpp=.o)
EXE=main
start:$(OBJ) $(OBJ1)
#	gcc $(OBJ) -o $(EXE) -g
	mv *.o ../Debug
.c.o:
	gcc -c $< -o $@ -g

.cpp.o:
	g++ -c $< -o $@ -g
clean:
	rm *.o
