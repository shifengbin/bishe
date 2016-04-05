start:
	cd log;make
	cd ConfigParser;make
	cd dns;make
	cd Persistence;make
	cd bloom;make
clean:
	cd log;make clean
	cd ConfigParser;make clean
	cd dns;make clean
	cd Persistence;make clean
	cd bloom;make clean
