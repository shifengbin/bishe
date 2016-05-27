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
	cd SockTool;make
	cd Download;make
	cd Hex2I;make	
	cd HTTP;make
	cd ModelTool;make

	g++ main.cpp ./Debug/*.o -lpthread -ldl -g
	mv a.out ./Debug
clean:
	cd Debug;rm *.o
