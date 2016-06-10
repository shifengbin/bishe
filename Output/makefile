start:
	gcc -c -fPIC ../Persistence/sqlite3.c -shared
	gcc output.c *.o -shared -fPIC -o output.so
	mv *.so ../Debug
	rm *.o
debug:
	gcc -c ../Persistence/sqlite3.c
	gcc output.c sqlite3.o -lpcre2-posix -lpthread -ldl -g
	rm *.o
