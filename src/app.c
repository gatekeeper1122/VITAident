#include <stdio.h>
#include <string.h>

#include "app.h"
#include "utils.h"

SceInt initAppUtil(SceVoid)
{
	SceAppUtilInitParam init;
	SceAppUtilBootParam boot;
	memset(&init, 0, sizeof(SceAppUtilInitParam));
	memset(&boot, 0, sizeof(SceAppUtilBootParam));
	
	SceInt ret = 0;
	
	if (R_FAILED(ret = sceAppUtilInit(&init, &boot)))
		return ret;
	
	return 0;
}

SceInt termAppUtil(SceVoid)
{
	SceInt ret = 0;
	
	if (R_FAILED(ret = sceAppUtilShutdown()))
		return ret;
	
	return 0;
}

SceChar8 * getUser(SceVoid)
{
	static SceChar8 userName[SCE_SYSTEM_PARAM_USERNAME_MAXSIZE];
	
	if (R_SUCCEEDED(sceAppUtilSystemParamGetString(SCE_SYSTEM_PARAM_ID_USERNAME, userName, SCE_SYSTEM_PARAM_USERNAME_MAXSIZE)))
		return userName;
	
	return NULL;
}

const char * getLang(SceVoid)
{
	const char * languages[] = 
	{
		"Japanese",
		"English US",
		"French",
		"Spanish",
		"German",
		"Italian",
		"Dutch",
		"Portugese",
		"Russian",
		"Korean",
		"Traditional Chinese",
		"Simplified Chinese",
		"Finnish",
		"Swedish",
		"Danish",
		"Norwegian",
		"Polish",
		"Brazlian Portugese",
		"English UK"
	};

	int language = 0;
	
	if (R_SUCCEEDED(sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language)))
	{
		if (language < 0x12)
			return languages[language];
		else
			return languages[0x12];
	}
	
	return NULL;
}

// 0 = max, 1 = free
char * getStorageInfo(const char * dev, SceInt type)
{
	SceIoDevInfo info;
	static char free_size_string[0x10], max_size_string[0x10];
	
	if (R_SUCCEEDED(sceIoDevctl(dev, 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo))))
	{
		getSizeString(free_size_string, info.free_size);
		getSizeString(max_size_string, info.max_size);
	
		if (type == 0)
			return max_size_string;
		else 
			return free_size_string;
	}
	
	return NULL;
}

SceBool getEnterButton(SceVoid) // Circle = 0, cross = 1
{
	int enterButton = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enterButton);
	
	if (enterButton == SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS)
		return SCE_TRUE;
	
	return SCE_FALSE;
}