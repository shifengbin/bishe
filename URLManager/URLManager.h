#ifndef __URLMANAGER_H__
#define __URLMANAGER_H__

#include "../URL/URL.h"
#include "../Queue/Queue.h"

#define URLMAXSIZE 100
#define URLLESSIZE 20

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
