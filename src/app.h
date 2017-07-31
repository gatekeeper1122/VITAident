#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <psp2/apputil.h>
#include <psp2/appmgr.h>
#include <psp2/system_param.h>

#include <stdio.h>
#include <string.h>

void initAppUtil(void);
void termAppUtil(void);
SceChar8 * getUser(void);
const char * getLang(void);
char * getStorageInfo(int type);
int getEnterButton(void);

#endif