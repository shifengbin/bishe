#ifndef BLOOM_H
#define BLOOM_H
#include <pthread.h>

#include "bloom.h"
class Bloom
{
private:
	static pthread_mutex_t lockadd;
	static pthread_mutex_t lockis;
public:
	void static addFilter( char *str );
	int  static isExist( char *str );
};


#endif
