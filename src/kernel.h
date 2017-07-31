#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/openpsid.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define isPCHX000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))
#define isVTE1000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineDolce()))
#define isPDEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()) && (vshSblAimgrIsTool()))
#define isPTEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))

int _vshSblAimgrGetConsoleId(char CID[32]);
int _vshAppMgrCloudDataGetMcId(char mCID[32]);

int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsGenuineVITA(void);
int vshSblAimgrIsGenuineDolce(void);
int vshSblAimgrIsTest(void);
int vshSblAimgrIsTool(void);

int vshSysconIsIduMode(void);
int vshSysconIsShowMode(void);
int vshSysconHasWWAN(void);

int vshRemovableMemoryGetCardInsertState(void);

char * getFwVersion(bool spoofed);
char getHenkakuVersion(void);
int getModel(void);
char * getCID(void);
char * getmCID(void);
SceKernelOpenPsId getPSID(void);
char * getUnit(void);
const char * getDeviceModel(void);
const char * getBoard(void);
const char * getSysrootKernelModes(int data);

#endif