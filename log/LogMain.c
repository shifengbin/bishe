#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "mylog.h"

int main()
{
	writelog( STDOUT_FILENO , DEBUG, DEBUG,"writelog");
	writelog( STDOUT_FILENO , WARNING, DEBUG,"writelog");
	writelog( STDOUT_FILENO , WARNING, ERROR,"writelog");
	writelog( STDOUT_FILENO , WARNING, WARNING,"writelog");
	writelog( STDOUT_FILENO , ERROR, DEBUG,"writelog");
	writelog( STDOUT_FILENO , ERROR, ERROR,"writelog");
	writelog( STDOUT_FILENO , ERROR, DEBUG,"writelog");
	writelog( STDOUT_FILENO , -1, DEBUG,"writelog");
	writelog( STDOUT_FILENO , 4, DEBUG,"writelog");
	return 0;
}
