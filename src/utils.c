#include "utils.h"

int getVolume()
{
	int calculatedVolume = 0;
	int volume = regMgrGetInt("/CONFIG/SOUND/", "main_volume");
	
	calculatedVolume = (volume * 3.33333333);
	
	return calculatedVolume;
}

int getBrightness()
{
	int calculatedBrightness = 0;
	int brightness = regMgrGetInt("/CONFIG/DISPLAY/", "brightness");
	
	calculatedBrightness = (brightness * 0.00152590219);
	
	return calculatedBrightness;
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

void endDrawing() 
{
	vita2d_end_drawing();
	vita2d_common_dialog_update();
	vita2d_swap_buffers();
	sceDisplayWaitVblankStart();
}

void getSizeString(char *string, uint64_t size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	int i = 0;
	static char *units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	while (double_size >= 1024.0f) {
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

const char * concat(char* s1, char* s2)
{
    char *ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}

char * readID_dat()
{
	SceUID file;
	static char writePath[250];
	char str[256];
	
	file = sceIoOpen("ux0:id.dat", SCE_O_RDONLY, 0777);
	
	sceIoLseek(file, 0, SCE_SEEK_SET);
	sceIoRead(file, &str, 187);
		
	sprintf(writePath, "%s", str);
	
	return writePath;
}