#ifndef __URL_H__
#define __URL_H__

typedef struct URL
{
	int id;
	char *urlStr;
	int type;
	int deep;
	int state;
}URL;

#endif
