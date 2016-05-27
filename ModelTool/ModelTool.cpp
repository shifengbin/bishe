#include <dlfcn.h>
#include <unistd.h>
#include "ModelTool.h"

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

