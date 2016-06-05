#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include "ModelTool.h"

Model *Model::model = NULL;

Model *Model::getModel()
{
	if (model == NULL)
	{
		model = new Model("./output.so");
	}
	return model;
}

Model::Model( const char *filename )
{
	output = NULL;
	this->handle = dlopen( filename , RTLD_NOW );
	if ( this->handle == NULL )
	{
		puts(dlerror());
	}
}

Model::~Model()
{
	if ( this->handle != NULL )
	{
		dlclose( this->handle );
	}
}

OUTPUTFUNC Model::getMethod( const char *funcName )
{
	output = (OUTPUTFUNC)dlsym( this->handle, funcName);
	if ( output == NULL  )
	{
		puts("getMethod Error``````````````");
	}
	return output;
}

int Model::isOpenSuccess()
{
	if( this->handle == NULL )
		return 0;
	return 1;
}

void Model::init()
{
	if (output != NULL )
	{
		return;
	}
	this->getMethod("output");
}
