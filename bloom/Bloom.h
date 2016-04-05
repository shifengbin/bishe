#ifndef BLOOM_H
#define BLOOM_H
#include "bloom.h"
class Bloom
{
public:
	void static addBloomFilter( char *str );
	int  static isExist( char *str );
};


void Bloom::addBloomFilter( char *str )
{
	add(str);
}

int Bloom::isExist( char *str )
{
	return search( str );
}
#endif
