#ifndef HTTP_H
#define HTTP_H

#define BODYSIZE (1024*1024*3)

typedef struct Header
{
	int state;
	int length;
}Header;


class HTTP
{
private:
	Header header;
	static pthread_mutex_t lock;
	char* body;
public:
	HTTP( int );
	~HTTP();
	int getState();
	int getLength();
	char *getBody();
};

#endif
