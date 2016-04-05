start:
	gcc -c threadpool.c 
	ar cvr libthreadpool.a threadpool.o
	g++ main.cpp -L. -lthreadpool -lpthread  -o main

clean:
	rm *.o
	rm *.a
	rm main
