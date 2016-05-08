start:
	cd log;make
	cd dns;make
	cd Persistence;make
	cd bloom;make
	cd ConfigParser;make
	cd TaskControl;make
	cd parserurl;make
	cd URLManager;make
	cd Output;make
	cd HashList;make
	

	g++ main.cpp ./Debug/*.o -lpthread -ldl 
	mv a.out ./Debug
clean:
	cd Debug;make
