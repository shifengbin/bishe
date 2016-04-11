#ifndef HASHLIST_H
#define HASHLIST_H
#include "hashlist.h"

class HashLink
{
private:
	HashList hl;
public:
	HashLink()
	{
		initHashList(&hl);
	}

	~HashLink()
	{
		destroyHashList(&hl);
	}	

	int set( const char *key, void *value)
	{
		return addElement(&hl,key,value);
	}

	void* remove( const char *key)
	{
		return delElement(&hl,key);
	}

	void* get( const char *key )
	{
		return getElement( &hl,key);
	}

	int getSize()
	{
		return getLength(&hl);
	}
};

#endif
