start:
	gcc -c threadpool.c 
	ar cvr libthreadpool.a threadpool.o
	gcc main.c -L. -lthreadpool -lpthread  -o main

clean:
	rm *.o
	rm *.a
	rm main
