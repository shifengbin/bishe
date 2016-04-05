start:
	cd log;make
	cd dns;make
	cd Persistence;make
	cd bloom;make
	cd ConfigParser;make

clean:
	cd log;make clean
	cd ConfigParser;make clean
	cd dns;make clean
	cd Persistence;make clean
	cd bloom;make clean
