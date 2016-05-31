#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "./ConfigParser/configparser.h"
#include "./URLManager/URLManager.h"
#include "./URL/URL.h"
#include "./TaskControl/TaskControl.h"
#include "./log/mylog.h"
#include "./dns/DNSCache.h"
#include "./Download/Download.h"
#include "./HTTP/HTTP.h"

#include "./parserurl/URLParser.h"

/*void test( void * a)
{
	DNSCache *dnsc = DNSCache::getDNSCache();
	char buf[16] = { 0 };
	struct sockaddr_in *saddr;
	URL *t = (URL*)a;
	char *host = URLParser::getHost(t->getURLStr());
//	printf("%s\n",t->getURLStr());
	t->setStateToDB(1);
	saddr = dnsc->DNS(host,"80");
	printf("|%s|\n",host);
	int fd = socket( AF_INET , SOCK_STREAM , 0 );
	puts(inet_ntop( AF_INET , &(saddr->sin_addr) , buf , 16 ) );
	char header[1024] ={ 0 } ;
	sprintf(header, "GET / HTTP/1.1\r\nHost: %s\r\nUser-Agent:Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; TencentTraveler 4.0)\r\n\r\n",host);
	puts(header);
	connect( fd , (struct sockaddr*)saddr , sizeof(struct sockaddr_in));
	write( fd , header , strlen(header));
	HTTP *h = new HTTP(fd);
//	puts(h->getBody());
	if ( h->getState() / 200 != 1 )
		printf("State:%d\n",h->getState());
		return;
	printf("State:%d\n",h->getState());
	char filename[100] = { 0 };
	sprintf( filename ,"%s%s",host,".html" );
	puts(filename);
	int ffd = open( filename ,O_CREAT|O_RDWR ,0666);
	if (ffd == -1 )
	{
		puts("Open Error!");
		return;
	}
	puts(h->getBody());
	write( ffd , h->getBody() , strlen( h->getBody()));
	close(ffd);
	puts( header );
	close(fd);
	return ;
}
*/

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
	
	TaskControl tasks( config->getJobNum() , download );
	//TaskControl tasks( config->getJobNum() , test );
	URL *tUrl = NULL;


	while( 1 )
	{
		urlm->loadURL();
		if (!tasks.getCurrentRun() && !urlm->getCurrentSize() )
		{
			puts("END");
			break;
		}
		
		//printf("run:%d count:%d\n",tasks.getCurrentRun(),urlm->getCurrentSize());
		if ( tasks.isAllTaskDone() )
		{
			for ( int i = 0 ; i < config->getJobNum() && (tUrl = urlm->popURL()) !=NULL; i++)
			{
//				puts("addTask");
				tasks.addTaskToQueue( tUrl);
			}
		}

		if ( config->getDuration() != 0 )
		{
			sleep(config->getDuration());
		}
		else
		{
			sleep(1);
		}

	}
	
	
	return 0;
}
