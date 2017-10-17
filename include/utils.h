#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <vitasdk.h>

#include <vita2d.h>

/// Checks whether a result code indicates success.
#define R_SUCCEEDED(res)   ((res)>=0)
/// Checks whether a result code indicates failure.
#define R_FAILED(res)      ((res)<0)
/// Returns the level of a result code.

SceInt getBrightness(SceVoid);
SceInt regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char * category, const char * name);
vita2d_texture * vita2d_load_PNG_buffer_filter(const SceVoid * buffer);
SceVoid endDrawing(SceVoid);
SceVoid getSizeString(char *string, SceULong64 size);
const char * concat(char * s1, char * s2);

#endif