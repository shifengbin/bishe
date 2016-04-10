start:
	g++ -c configparser.cpp
	g++ -c modepair.cpp
	g++ -c ConfigParserMain.cpp 
#	g++ main.o configparser.o modepair.o ../log/mylog.o ../Persistence/Persistence.o ../Persistence/sqlite3.o -ldl -lpthread
	mv *.o ../Debug
	cp config.cfg ../Debug
clean:
	rm *.o
	rm spider.*
