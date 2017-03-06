#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>
#include <psp2/io/fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

unsigned int fontColor;

int sceRegMgrGetKeyInt(const char* category, const char* name, int* buf);
int sceRegMgrGetKeyStr(const char* category, const char* name, char* buf, const int size); 
int sceRegMgrGetKeyBin(const char *category, const char *name, void *buf, int size);

int getVolume();
int getBrightness();
int regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char* category, const char* name);
vita2d_texture * loadPngWithFilter(const char * path);
void endDrawing();
void getSizeString(char *string, uint64_t size);
const char *concat(char* s1, char* s2);
char * readID_dat();

#endif