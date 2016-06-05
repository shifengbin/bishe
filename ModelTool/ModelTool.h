#ifndef __MODELTOOL_H__
#define __MODELTOOL_H__

/*      
	Model load class
	same as Java's reflect 
	Link with -ldl.
*/

typedef void(*OUTPUTFUNC)(char*,char*,int);

class Model
{
private:
	static Model *model;
	void *handle;
	Model( const char *filename );
public:
	OUTPUTFUNC output;
	static Model *getModel();
	~Model();
	OUTPUTFUNC getMethod( const char *funcName );
	int   isOpenSuccess();
	void init();
};


#endif
