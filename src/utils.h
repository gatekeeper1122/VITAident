#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/registrymgr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

int getVolume(void);
int getBrightness(void);
int regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char * category, const char * name);
vita2d_texture * loadPngWithFilter(const void *buffer);
void endDrawing(void);
void getSizeString(char *string, uint64_t size);
const char * concat(char * s1, char * s2);

#endif