#ifndef _VITAIDENT_MAIN_H_
#define _VITAIDENT_MAIN_H_

#include <vitasdk.h>
#include <vita2d.h>

#define selector_yDistance 40 // The distance between the Y axis of the two selections
#define MAX_ITEMS 8

#define COLOUR_MAINMENU                 RGBA8(78, 74, 67, 255)
#define COLOUR_MAINMENU_HIGHLIGHT       RGBA8(255, 255, 255, 255)
#define COLOUR_MENU                     RGBA8(0, 0, 0, 255)
#define COLOUR_SUBJECT                  RGBA8(120, 118, 115, 255)
#define COLOUR_VALUE                    RGBA8(67, 72, 66, 255)

vita2d_texture *VITAident, *drive;
vita2d_pvf *font;

SceCtrlData pad, old_pad;
SceUInt32 pressed;

#endif