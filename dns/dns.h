#ifndef __DNS_H__
#define __DNS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>

struct sockaddr_in *dns( char *hostname, char *port);


#ifdef __cplusplus
}
#endif

#endif
