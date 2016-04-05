#include <stdio.h>
#include "ModelTool.h"

typedef int (*ADD)(int,int);

int main()
{
	ADD pFun;
	Model m("./add.so");
	pFun = (ADD)(m.getMethod("add"));
	printf("is open:%d\n",m.isOpenSuccess());
	if ( pFun != NULL )
		printf("%d\n",pFun(1,2));
	return 0;
}
