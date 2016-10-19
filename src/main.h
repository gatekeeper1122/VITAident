#ifndef _VITAIDENT_MAIN_H_
#define _VITAIDENT_MAIN_H_

#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>

#include <stdio.h>
#include <string.h>

#include <vita2d.h>

#define selector_xDistance 0 //The distance between the X axis of the two selections
#define selector_yDistance 50 //The distance between the Y axis of the two selections

vita2d_texture *VITAident;
vita2d_pgf *font;

SceCtrlData pad, old_pad;
unsigned int pressed;

int kernelMenu();
int systemMenu();
int batteryMenu();
int miscMenu();
int controls();
int mainMenu();

#endif