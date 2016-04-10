#include <stdio.h>
#include "URLManager.h"


int main()
{
	URLManager *uma = URLManager::getURLManager();
	URL *u;
	uma->loadURL();
	puts("start");
	while(uma->getCurrentSize())
	{
		u = uma->popURL();	
		if ( u!= NULL )
		{
			printf("id:%d URL:%s deep:%d state:%d type:%d\n",u->getId(),u->getURLStr(),u->getDeep(),u->getState(),u->getType());
		}
	}
	return 0;
}
