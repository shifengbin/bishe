#ifndef __MODELTOOL_H__
#define __MODELTOOL_H__

#include <dlfcn.h>
#include <unistd.h>
/*      
	Model load class
	same as Java's reflect 
	Link with -ldl.
*/

class Model
{
private:
	void *handle;
public:
	Model( const char *filename );
	~Model();
	void *getMethod( const char *funcName );
	int   isOpenSuccess();
};

Model::Model( const char *filename )
{
	this->handle = dlopen( filename , RTLD_NOW );
}

Model::~Model()
{
	if ( this->handle != NULL )
	{
		dlclose( this->handle );
	}
}

void *Model::getMethod( const char *funcName )
{
	return dlsym( this->handle , funcName );
}

int Model::isOpenSuccess()
{
	if( this->handle == NULL )
		return 0;
	return 1;
}

#endif
