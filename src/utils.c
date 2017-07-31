#include "utils.h"

int getVolume(void)
{
	int volume = 0;
	int sceVolume = regMgrGetInt("/CONFIG/SOUND/", "main_volume");
	
	volume = (sceVolume * 3.33333333);
	
	if (volume == 99)
		volume = 100;
	
	return volume;
}

int getBrightness(void)
{
	int brightness = 0;
	int sceBrightness = regMgrGetInt("/CONFIG/DISPLAY/", "brightness");
	
	brightness = (sceBrightness * 0.00152590219);
	
	return brightness;
}

int regMgrGetInt(const char * category, const char * name)
{
	int value = -1;
	
	int ret = sceRegMgrGetKeyInt(category, name, &value);
	
	if (ret < 0)
		return 0;
	else
		return value;
}

char * regMgrGetStr(const char* category, const char* name)
{
	static char str[256];
	
	int ret = sceRegMgrGetKeyStr(category, name, str, sizeof(str)); 
	
	if (ret < 0)
		return NULL;
	else
		return str;
}

void setBilinearFilter(int enabled, vita2d_texture * texture)
{
	if (enabled == 1)
		vita2d_texture_set_filters(texture, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
}

vita2d_texture * loadPngWithFilter(const void *buffer)
{
	vita2d_texture *texture = vita2d_load_PNG_buffer(buffer);
	setBilinearFilter(1, texture);
	
	return texture;
}

void endDrawing(void) 
{
	vita2d_end_drawing();
	vita2d_common_dialog_update();
	vita2d_swap_buffers();
	sceDisplayWaitVblankStart();
}

void getSizeString(char * string, uint64_t size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	int i = 0;
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