#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

unsigned int fontColor;

unsigned int getColor();
char * getFontColor();
vita2d_texture * loadPngWithFilter(const char * path);
void endDrawing();
void getSizeString(char *string, uint64_t size);
const char *concat(char* s1, char* s2);

#endif