#ifndef __PERSISTENCE_H__
#define __PERSISTENCE_H__
#include <pthread.h>
#include "sqlite3.h"

#define DBFILE "spider.db"

typedef int (*callback)( void *, int , char ** , char **);

class Persistence
{
public:
	~Persistence();
	int exec( const char *sql );
	int query( const char *sql , callback fun, void *data);
	char *getErr();
	static Persistence *getPersistence();
private:
	Persistence( const char *dbfile);
	static Persistence *pdb;
	pthread_mutex_t lock;
	sqlite3 *db;
	char *err;
};

#endif
