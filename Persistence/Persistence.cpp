#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "sqlite3.h"
#include "Persistence.h"
#include "../log/mylog.h"


Persistence *Persistence::pdb = NULL;


Persistence::Persistence( const char *dbfile )
{
	int ret;	
	unlink(dbfile);//remove old dbfile

//	this->lock = PTHREAD_MUTEX_INITIALIZER; 
	pthread_mutex_init( &(this->lock) , NULL );
	ret = sqlite3_open( dbfile , &(this->db) );
	if ( ret != SQLITE_OK )
	{
		mylog( ERROR , "create database error");
		exit(-1);
	}
}

Persistence *Persistence::getPersistence()
{
	if ( pdb == NULL )
	{
		pdb = new Persistence(DBFILE);
	}
	return pdb;
}

Persistence::~Persistence()
{
	if (this->err != NULL )
		sqlite3_free( this->err );

	sqlite3_close( this->db );

	delete pdb;
	
	pthread_mutex_destroy(&(this->lock));
}

int Persistence::exec( const char *sql )// insert update delete create table etc without select 
{
	int ret = 0;	
	pthread_mutex_lock(&(this->lock));

	if (this->err != NULL )
		sqlite3_free( this->err );
	ret = sqlite3_exec(this->db,sql,0,0,&(this->err));
	if (ret != SQLITE_OK )
	{
		mylog(ERROR,sql);
		mylog(ERROR,this->err);
	}
	pthread_mutex_unlock(&(this->lock));
	return ret;
}

int Persistence::query( const char *sql , callback fun, void *data)//all select insert update delete
{
	int ret = 0;	
	pthread_mutex_lock(&(this->lock));

	if (this->err != NULL )
		sqlite3_free( this->err );
	ret = sqlite3_exec(this->db,sql,fun,data,&(this->err));
	if (ret != SQLITE_OK )
	{
		mylog(ERROR,sql);
		mylog(ERROR,this->err);
	}
	pthread_mutex_unlock(&(this->lock));
	return ret;
}

char *Persistence::getErr()
{
	return this->err;
}
