start:
	g++ -c configparser.cpp
	g++ -c modepair.cpp
	g++ -c main.cpp 
	g++ main.o configparser.o modepair.o ../log/mylog.o ../Persistence/Persistence.o ../Persistence/sqlite3.o -ldl -lpthread
clean:
	rm *.o
	rm spider.*
