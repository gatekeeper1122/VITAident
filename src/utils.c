#include "utils.h"

unsigned int getColor()
{
	int fontColor = 0;
	unsigned int color = 0;
	
	FILE * file = fopen("ux0:/data/VID000016/fontColor.bin", "r");
	fscanf(file, "%d", &fontColor);
	fclose(file);
	
	if (fontColor == 0)
		color = RGBA8(11, 199, 41, 255);
	else if (fontColor == 1)
		color = RGBA8(220, 20, 60, 255);
	else if (fontColor == 2)
		color = RGBA8(70, 130, 180, 255);
	else if (fontColor == 3)
		color = RGBA8(255, 215, 0, 255);
	else if (fontColor == 4)
		color = RGBA8(148, 0, 211, 255);
	else if (fontColor == 5)
		color = RGBA8(219, 112, 147, 255);
	else if (fontColor == 6)
		color = RGBA8(0, 191, 255, 255);
	else if (fontColor == 7)
		color = RGBA8(139, 69, 19, 255);
	else if (fontColor == 8)
		color = RGBA8(255, 250, 250, 255);

   return color;
}

char * getFontColor()
{
	static char colorStr[10];
	int fontColor = 0;
	
	FILE * file = fopen("ux0:/data/VID000016/fontColor.bin", "r");
	fscanf(file, "%d", &fontColor);
	fclose(file);
	
	if (fontColor == 0)
		strcpy(colorStr, "Green");
	else if (fontColor == 1)
		strcpy(colorStr, "Red");
	else if (fontColor == 2)
		strcpy(colorStr, "Blue");
	else if (fontColor == 3)
		strcpy(colorStr, "Gold");
	else if (fontColor == 4)
		strcpy(colorStr, "Purple");
	else if (fontColor == 5)
		strcpy(colorStr, "Pink");
	else if (fontColor == 6)
		strcpy(colorStr, "Cyan");
	else if (fontColor == 7)
		strcpy(colorStr, "Brown");
	else if (fontColor == 8)
		strcpy(colorStr, "White");
   
   return colorStr;
}

void setBilinearFilter(int enabled, vita2d_texture * texture)
{
	if (enabled == 1)
	{
		vita2d_texture_set_filters(texture, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
	}
}

vita2d_texture * loadPngWithFilter(const char * path)
{
	vita2d_texture *texture = vita2d_load_PNG_file(path);
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