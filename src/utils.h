#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/registrymgr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

SceInt getVolume(SceVoid);
SceInt getBrightness(SceVoid);
SceInt regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char * category, const char * name);
vita2d_texture * vita2d_load_PNG_buffer_filter(const SceVoid *buffer);
SceVoid endDrawing(SceVoid);
SceVoid getSizeString(char *string, SceULong64 size);
const char * concat(char * s1, char * s2);

#endif