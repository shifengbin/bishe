#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#ifdef __cplusplus
extern "C" {
#endif
void initModel();
void loaddll( int sig );
void download( void * args);
#ifdef __cplusplus
}
#endif

#endif