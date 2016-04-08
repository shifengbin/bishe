start:
	gcc -c sqlite3.c
	g++ -c Persistence.cpp
	g++ -c test.cpp
	g++ Persistence.o test.o sqlite3.o ../log/mylog.o -lpthread -ldl
clean:
	rm *.o
	rm spider.*
