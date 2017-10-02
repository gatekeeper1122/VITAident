#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <vitasdk.h>

SceInt initAppUtil(SceVoid);
SceInt termAppUtil(SceVoid);
SceChar8 * getUser(SceVoid);
const char * getLang(SceVoid);
char * getStorageInfo(const char * dev, SceInt type);
SceBool getEnterButton(SceVoid);

#endif