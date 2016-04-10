start:
	gcc -c threadpool.c 
#	ar cvr libthreadpool.a threadpool.o
#	g++ main.cpp -L. -lthreadpool -lpthread  -o main
	gcc -c TaskControlMainC.c
	g++ -c TaskControlMainCPP.cpp
	
	mv *.o ../Debug

clean:
	rm *.o
	rm *.a
	rm main
