#include <stdio.h>
#include <arpa/inet.h>

#include "./ConfigParser/configparser.h"
#include "./URLManager/URLManager.h"
#include "./URL/URL.h"
#include "./TaskControl/TaskControl.h"
#include "./log/mylog.h"
#include "./dns/DNSCache.h"
//#include "./Download/Download.h"

void test( void * a)
{
	DNSCache *dnsc = DNSCache::getDNSCache();	
	char buf[16] = { 0 };
	struct sockaddr_in *saddr;
	URL *t = (URL*)a;
	printf("%s\n",t->getURLStr());
	t->setStateToDB(1);
	saddr = dnsc->DNS(t->getURLStr(),"80");
	puts(inet_ntop( AF_INET , &(saddr->sin_addr) , buf , 16 ) );
	return ;
}

int main()
{

	ConfigParser *config = ConfigParser::getConfigParser();
	if ( config == NULL )
	{
		mylog( ERROR, "Config Error!");
		return -1;
	}

	URLManager *urlm = URLManager::getURLManager();
	if ( urlm == NULL )
	{
		mylog( ERROR, "URLManager Error!");
		return -1;
	}
	
	TaskControl tasks( config->getJobNum() , test );
	URL *tUrl = NULL;

//	raise( SIGRTMIN );

	while( 1 )
	{
		urlm->loadURL();
		if (!tasks.getCurrentRun() && !urlm->getCurrentSize() )
		{
			break;
		}

		if ( tasks.isAllTaskDone() )
		{
			for ( int i = 0 ; i < config->getJobNum() && (tUrl = urlm->popURL()) !=NULL; i++)
			{
				tasks.addTaskToQueue( tUrl);
			}
		}

		if ( config->getDuration() != 0 )
		{
			sleep(config->getDuration());
		}

	}
	
	
	return 0;
}
