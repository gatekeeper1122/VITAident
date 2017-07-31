#ifndef _VITAIDENT_FS_H_
#define _VITAIDENT_FS_H_

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/devctl.h>

#include <string.h>

int fileExists(const char * path);
int dirExists(const char * path);
int writeFile(char * file, void * buf, int size);
SceOff getPartitionInfo(int storage, const char * partition);
char * getVitaModel(void);

#endif