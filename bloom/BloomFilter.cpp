#include <pthread.h>

#include "BloomFilter.h"
#include "bloom.h"
pthread_mutex_t Bloom::lockadd = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Bloom::lockis = PTHREAD_MUTEX_INITIALIZER;

void Bloom::addFilter( char *str )
{
	pthread_mutex_lock(&lockadd);
	add(str);
	pthread_mutex_unlock(&lockadd);
}

int Bloom::isExist( char *str )
{
	int ret;
	pthread_mutex_lock(&lockis);
	ret = search(str);
	pthread_mutex_unlock(&lockis);
	return ret;
}
