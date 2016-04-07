#ifndef BLOOM_H
#define BLOOM_H
#include "bloom.h"
class Bloom
{
	public:
		void static addFilter( char *str );
		int  static isExist( char *str );
};


void Bloom::addFilter( char *str )
{
	add(str);
}

int Bloom::isExist( char *str )
{
	return search( str );
}
#endif
