#ifndef _VITAIDENT_MAIN_H_
#define _VITAIDENT_MAIN_H_

#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>

#include <stdio.h>
#include <string.h>

#include <vita2d.h>

#define selector_yDistance 40 // The distance between the Y axis of the two selections
#define MAX_ITEMS 7

vita2d_texture * VITAident;
vita2d_pvf * font;

SceCtrlData pad, old_pad;
unsigned int pressed;

void kernelMenu();
void systemMenu();
void batteryMenu();
void miscMenu();
int controls();
int mainMenu();

#endif