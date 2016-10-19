#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>

#include <stdio.h>

#include <vita2d.h>

vita2d_texture * loadPngWithFilter(const char * path);
void endDrawing();

void getSizeString(char *string, uint64_t size);

#endif