#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

SceInt getVolume(SceVoid)
{
	SceInt volume = 0;
	SceInt regVolume = regMgrGetInt("/CONFIG/SOUND/", "main_volume");
	
	volume = (regVolume * 3.33333333);
	
	if (volume == 99)
		volume = 100;
	
	return volume;
}

SceInt getBrightness(SceVoid)
{
	SceInt brightness = 0;
	SceInt regBrightness = regMgrGetInt("/CONFIG/DISPLAY/", "brightness");
	
	brightness = (regBrightness * 0.00152590219);
	
	return brightness;
}

SceInt regMgrGetInt(const char * category, const char * name)
{
	int value = 0;
	
	if (R_SUCCEEDED(sceRegMgrGetKeyInt(category, name, &value)))
		return value;
	
	return 0;
}

char * regMgrGetStr(const char* category, const char* name)
{
	static char str[256];
	
	if (R_SUCCEEDED(sceRegMgrGetKeyStr(category, name, str, sizeof(str))))
		return str;
	
	return NULL;
}

vita2d_texture * vita2d_load_PNG_buffer_filter(const SceVoid * buffer)
{
	vita2d_texture * texture = vita2d_load_PNG_buffer(buffer);
	vita2d_texture_set_filters(texture, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
	
	return texture;
}

SceVoid endDrawing(SceVoid) 
{
	vita2d_end_drawing();
	vita2d_common_dialog_update();
	vita2d_swap_buffers();
	sceDisplayWaitVblankStart();
}

SceVoid getSizeString(char * string, SceULong64 size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	SceInt i = 0;
	static char * units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	
	while (double_size >= 1024.0f) 
	{
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

const char * concat(char * s1, char * s2)
{
    char * ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}