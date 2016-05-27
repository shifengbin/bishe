#ifndef __MODELTOOL_H__
#define __MODELTOOL_H__

/*      
	Model load class
	same as Java's reflect 
	Link with -ldl.
*/

class Model
{
private:
	void *handle;
public:
	Model( const char *filename );
	~Model();
	void *getMethod( const char *funcName );
	int   isOpenSuccess();
};


#endif
