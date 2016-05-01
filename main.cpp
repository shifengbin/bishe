#include <stdio.h>

#include "./ConfigParser/configparser.h"
#include "./URLManager/URLManager.h"
#include "./URL/URL.h"
#include "./TaskControl/TaskControl.h"
#include "./log/mylog.h"

void test( void*args)
{
	URL *mURL = (URL*) args;
	printf("%s\n",mURL->getURLStr());
	mURL->setStateToDB( 100 );
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
	
	TaskControl tasks( config->getJobNum() , test);
	URL *tUrl = NULL;

	while( 1 )
	{
		urlm->loadURL();
		printf("URLMSize:%d\n",urlm->getCurrentSize());
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

		if ( config->getTimeout() != 0 )
		{
			sleep(config->getTimeout());
		}

	}
	
	
	return 0;
}
