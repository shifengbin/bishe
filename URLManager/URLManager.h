#ifndef __URLMANAGER_H__
#define __URLMANAGER_H__

#include "../URL/URL.h"
#include "../Queue/Queue.h"

#define URLMAXSIZE 10
#define URLLESSIZE 2

class URLManager
{
private:
	static URLManager *um;
	Queue<URL> *urlQue;
	URLManager();
public:
	static URLManager *getURLManager();
	int getCurrentSize();
	int loadURL();
	URL *popURL();
	~URLManager();
};

#endif
