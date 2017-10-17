#include <stdio.h>
#include <string.h>

#include <psp2/compat.h>
#include <psp2kern/bt.h>

#include "app.h"
#include "fs.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "touch.h"
#include "utils.h"

extern SceUChar8 _binary_res_VITAident_png_start;
extern SceUChar8 _binary_res_drive_png_start;

static char * devices[] = 
{
	"ur0:",
	"ux0:",
	"imc0:",
	"uma0:",
};

SceVoid kernelMenu(SceVoid)
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Kernel Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "Kernel Menu");
		
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Firmware version:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Firmware version:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", getFwVersion(SCE_FALSE));
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "System version:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "System version:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", getFwVersion(SCE_TRUE));
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "Model version:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Model version:") + 10), 345, COLOUR_VALUE, 1.1f, "%s %s (0x%08X)", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());
	
	vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "PS Vita unit:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "PS Vita unit:") + 10), 385, COLOUR_VALUE, 1.1f, "%s", getUnit());
	
	vita2d_pvf_draw_text(font, 364, 425, COLOUR_SUBJECT, 1.1f, "Motherboard:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Motherboard:") + 10), 425, COLOUR_VALUE, 1.1f, "%s", getBoard());
	
	vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "PS Vita CID:"); //Thanks Major_Tom
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "PS Vita CID:") + 10), 465, COLOUR_VALUE, 1.1f, "%s", getCID());
	
	vita2d_pvf_draw_text(font, 364, 505, COLOUR_SUBJECT, 1.1f, "PSID:"); //Thanks SMOKE
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "PSID:") + 10), 505, COLOUR_VALUE, 1.1f, "%02X", getPSID());
}

SceVoid systemMenu(SceVoid)
{
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "System Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "System Menu");
		
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Language:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Language:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", getLang());
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "MAC address:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "MAC address:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", getMacAddress());
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "ARM clock frequency:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "ARM clock frequency:") + 10), 345, COLOUR_VALUE, 1.1f, "%d MHz", getClockFrequency(clockFrequencyType_cpu));
	
	vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "BUS clock frequency:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "BUS clock frequency:") + 10), 385, COLOUR_VALUE, 1.1f, "%d MHz", getClockFrequency(clockFrequencyType_bus));
	
	vita2d_pvf_draw_text(font, 364, 425, COLOUR_SUBJECT, 1.1f, "GPU clock frequency:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "GPU clock frequency:") + 10), 425, COLOUR_VALUE, 1.1f, "%d MHz", getClockFrequency(clockFrequencyType_gpu));

	vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "GPU Xbar clock frequency:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "GPU Xbar clock frequency:") + 10), 465, COLOUR_VALUE, 1.1f, "%d MHz", getClockFrequency(clockFrequencyType_gpuXbar));
}

SceVoid batteryMenu(SceVoid)
{
	vita2d_pvf_draw_text(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Battery Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "Battery Menu");
		
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Battery percentage:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Battery percentage:") + 10), 265, COLOUR_VALUE, 1.1f, "%s (%s)", getBatteryPercentage(), getBatteryStatus());
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "Battery capacity:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Battery capacity:") + 10), 305, COLOUR_VALUE, 1.1f, "%s (remaining: %s)", getBatteryCapacity(), getBatteryRemainCapacity());
	
	SceInt batteryLifeTime = scePowerGetBatteryLifeTime();
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "Battery life time:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Battery life time:") + 10), 345, COLOUR_VALUE, 1.1f, "%02dh %02dm (SOH: %s)", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60), getBatterySOH());
	
	vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "Battery temperature:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Battery temperature:") + 10), 385, COLOUR_VALUE, 1.1f, "%s C (%s F)", getBatteryTemp(0), getBatteryTemp(1));
	
	vita2d_pvf_draw_text(font, 364, 425, COLOUR_SUBJECT, 1.1f, "Battery voltage:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Battery voltage:") + 10), 425, COLOUR_VALUE, 1.1f, "%s V (cycle count: %s)", getBatteryVoltage(), getBatteryCycleCount());
	
	vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "Udcd state:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Udcd state:") + 10), 465, COLOUR_VALUE, 1.1f, "%s (%s)", getUdcdCableState(), getUsbChargingState());
}

SceVoid storageMenu(SceVoid)
{
	vita2d_draw_rectangle(345, 50, 615, 494, RGBA8(242, 241, 239, 255));
	
	vita2d_draw_texture(drive, 380, 64);
	vita2d_draw_rectangle(490, 148, 430, 16, RGBA8(120, 118, 115, 255));
	vita2d_draw_rectangle(492, 150, 426, 12, RGBA8(242, 241, 239, 255));
	vita2d_draw_rectangle(492, 150, (((double)getUsedSize(devices[0]) / (double)getMaxSize(devices[0])) * 426.00), 12, RGBA8(242, 119, 62, 255));
	vita2d_pvf_draw_text(font, 490, 84, COLOUR_VALUE, 1.1f, devices[0]);
	vita2d_pvf_draw_text(font, 490, 110, COLOUR_SUBJECT, 1.1f, "Free size:");
	vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Free size:") + 10), 110, COLOUR_VALUE, 1.1f, getStorageInfo(devices[0], 1));
	vita2d_pvf_draw_text(font, 490, 135, COLOUR_SUBJECT, 1.1f, "Max size:");
	vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Max size:") + 10), 135, COLOUR_VALUE, 1.1f, getStorageInfo(devices[0], 0));
	
	if (vshRemovableMemoryGetCardInsertState()) // if mem card is inserted
	{
		vita2d_draw_texture(drive, 380, 184);
		vita2d_draw_rectangle(490, 268, 430, 16, RGBA8(120, 118, 115, 255));
		vita2d_draw_rectangle(492, 270, 426, 12, RGBA8(242, 241, 239, 255));
		vita2d_draw_rectangle(492, 270, (((double)getUsedSize(devices[1]) / (double)getMaxSize(devices[1])) * 426.00), 12, RGBA8(242, 119, 62, 255));
		vita2d_pvf_draw_text(font, 490, 204, COLOUR_VALUE, 1.1f, devices[1]);
		vita2d_pvf_draw_text(font, 490, 230, COLOUR_SUBJECT, 1.1f, "Free size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Free size:") + 10), 230, COLOUR_VALUE, 1.1f, getStorageInfo(devices[1], 1));
		vita2d_pvf_draw_text(font, 490, 255, COLOUR_SUBJECT, 1.1f, "Max size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Max size:") + 10), 255, COLOUR_VALUE, 1.1f, getStorageInfo(devices[1], 0));
	}
	
	else if ((!vshRemovableMemoryGetCardInsertState()) && ((strcmp(getVitaModel(), "1000") == 0) || (isVTE1000)))
	{
		vita2d_draw_texture(drive, 380, 184);
		vita2d_draw_rectangle(490, 268, 430, 16, RGBA8(120, 118, 115, 255));
		vita2d_draw_rectangle(492, 270, 426, 12, RGBA8(242, 241, 239, 255));
		vita2d_draw_rectangle(492, 270, (((double)getUsedSize(devices[2]) / (double)getMaxSize(devices[2])) * 426.00), 12, RGBA8(242, 119, 62, 255));
		vita2d_pvf_draw_text(font, 490, 204, COLOUR_VALUE, 1.1f, devices[2]);
		vita2d_pvf_draw_text(font, 490, 230, COLOUR_SUBJECT, 1.1f, "Free size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Free size:") + 10), 230, COLOUR_VALUE, 1.1f, getStorageInfo(devices[2], 1));
		vita2d_pvf_draw_text(font, 490, 255, COLOUR_SUBJECT, 1.1f, "Max size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Max size:") + 10), 255, COLOUR_VALUE, 1.1f, getStorageInfo(devices[2], 0));
	}
	
	if (getMaxSize(devices[3]))
	{
		vita2d_draw_texture(drive, 380, 304);
		vita2d_draw_rectangle(490, 388, 430, 16, RGBA8(120, 118, 115, 255));
		vita2d_draw_rectangle(492, 390, 426, 12, RGBA8(242, 241, 239, 255));
		vita2d_draw_rectangle(492, 390, (((double)getUsedSize(devices[3]) / (double)getMaxSize(devices[3])) * 426.00), 12, RGBA8(242, 119, 62, 255));
		vita2d_pvf_draw_text(font, 490, 324, COLOUR_VALUE, 1.1f, devices[3]);
		vita2d_pvf_draw_text(font, 490, 350, COLOUR_SUBJECT, 1.1f, "Free size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Free size:") + 10), 350, COLOUR_VALUE, 1.1f, getStorageInfo(devices[3], 1));
		vita2d_pvf_draw_text(font, 490, 375, COLOUR_SUBJECT, 1.1f, "Max size:");
		vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Max size:") + 10), 375, COLOUR_VALUE, 1.1f, getStorageInfo(devices[3], 0));
	}
	
	/*vita2d_draw_texture(drive, 380, 424);
	vita2d_draw_rectangle(490, 508, 430, 16, RGBA8(120, 118, 115, 255));
	vita2d_draw_rectangle(492, 510, 426, 12, RGBA8(242, 241, 239, 255));
	vita2d_draw_rectangle(492, 510, (((double)getUsedSize(devices[3]) / (double)getMaxSize(devices[3])) * 426.00), 12, RGBA8(242, 119, 62, 255));
	vita2d_pvf_draw_text(font, 490, 444, COLOUR_VALUE, 1.1f, devices[3]);
	vita2d_pvf_draw_text(font, 490, 470, COLOUR_SUBJECT, 1.1f, "Free size:");
	vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Free size:") + 10), 470, COLOUR_VALUE, 1.1f, getStorageInfo(devices[3], 1));
	vita2d_pvf_draw_text(font, 490, 495, COLOUR_SUBJECT, 1.1f, "Max size:");
	vita2d_pvf_draw_textf(font, (490 + vita2d_pvf_text_width(font, 1.1f, "Max size:") + 10), 495, COLOUR_VALUE, 1.1f, getStorageInfo(devices[3], 0));*/
}

static SceInt wifiPage = 0;

SceVoid wifiMenu(SceVoid)
{		
	vita2d_draw_rectangle(345, 50, 615, 494, RGBA8(242, 241, 239, 255));
	
	switch(wifiPage)
	{
		case 0:
			if (strcmp(regMgrGetStr("/CONFIG/NET/01/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 65, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 67, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 84, COLOUR_VALUE, 1.1f, "Profile 1:");
				vita2d_pvf_draw_text(font, 364, 110, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 110, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/01/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 136, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 136, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/01/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/01/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/02/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 163, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 165, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 182, COLOUR_VALUE, 1.1f, "Profile 2:");
				vita2d_pvf_draw_text(font, 364, 208, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 208, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/02/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 234, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 234, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/02/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/02/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/03/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 261, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 263, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 280, COLOUR_VALUE, 1.1f, "Profile 3:");
				vita2d_pvf_draw_text(font, 364, 306, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 306, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/03/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 332, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 332, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/03/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/03/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/04/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 359, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 361, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 378, COLOUR_VALUE, 1.1f, "Profile 4:");
				vita2d_pvf_draw_text(font, 364, 404, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 404, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/04/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 430, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 430, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/04/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/04/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/05/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 457, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 459, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 476, COLOUR_VALUE, 1.1f, "Profile 5:");
				vita2d_pvf_draw_text(font, 364, 502, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 502, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/05/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 528, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 528, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/05/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/05/WIFI/", "wpa_key"));
			}
			break;
			
		case 1:
			if (strcmp(regMgrGetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 65, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 67, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 84, COLOUR_VALUE, 1.1f, "Profile 6:");
				vita2d_pvf_draw_text(font, 364, 110, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 110, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/06/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 136, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 136, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/06/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/06/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/07/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 163, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 165, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 182, COLOUR_VALUE, 1.1f, "Profile 7:");
				vita2d_pvf_draw_text(font, 364, 208, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 208, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/07/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 234, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 234, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/07/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/07/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/08/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 261, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 263, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 280, COLOUR_VALUE, 1.1f, "Profile 8:");
				vita2d_pvf_draw_text(font, 364, 306, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 306, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/08/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 332, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 332, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/08/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/08/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/09/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 359, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 361, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 378, COLOUR_VALUE, 1.1f, "Profile 9:");
				vita2d_pvf_draw_text(font, 364, 409, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 409, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/09/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 430, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 430, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/09/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/09/WIFI/", "wpa_key"));
			}
	
			if (strcmp(regMgrGetStr("/CONFIG/NET/10/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(360, 457, 585, 80, RGBA8(180, 180, 178, 255));
				vita2d_draw_rectangle(362, 459, 581, 76, RGBA8(255, 255, 253, 255));
		
				vita2d_pvf_draw_text(font, 364, 476, COLOUR_VALUE, 1.1f, "Profile 10:");
				vita2d_pvf_draw_text(font, 364, 502, COLOUR_SUBJECT, 1.1f, "SSID:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "SSID:") + 10), 502, COLOUR_VALUE, 1.1f, "%s %s", regMgrGetStr("/CONFIG/NET/10/WIFI/", "ssid"), 
					regMgrGetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				vita2d_pvf_draw_text(font, 364, 528, COLOUR_SUBJECT, 1.1f, "Pass:");
				vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Pass:") + 10), 528, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? 
					regMgrGetStr("/CONFIG/NET/10/WIFI/", "wep_key") : regMgrGetStr("/CONFIG/NET/10/WIFI/", "wpa_key"));
			}
			break;
	}
}

SceVoid miscMenu(SceVoid)
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Misc Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "Misc Menu");
	
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Username:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Username:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", getUser());
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "IP address:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "IP address:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", getIP());
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "Enter button:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Enter button:") + 10), 345, COLOUR_VALUE, 1.1f, "%s", getEnterButton()? "cross (X)" : "circle (O)");

	SceInt fw = 0;
	if (R_SUCCEEDED(fw = sceCompatGetPspSystemSoftwareVersion()))
	{
		vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "PSP firmware version:");
		vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "PSP firmware version:") + 10), 385, COLOUR_VALUE, 1.1f, "%d.%.2d", fw / 100, fw % 100);
	}
}

SceVoid configMenu(SceVoid)
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Config Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "Config Menu");
	
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Airplane mode:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Airplane mode:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/SYSTEM/", "flight_mode")? "enabled" : "disabled");
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "Bluetooth:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Bluetooth:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/BT/", "bt_enable")? "enabled" : "disabled");
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "WiFi power save:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "WiFi power save:") + 10), 345, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NET/", "wifi_power_save")? "enabled" : "disabled");
	
	vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "Screen lock passcode:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Screen lock passcode:") + 10), 385, COLOUR_VALUE, 1.1f, "%s", regMgrGetStr("/CONFIG/SECURITY/SCREEN_LOCK/", "passcode"));
	
	vita2d_pvf_draw_text(font, 364, 425, COLOUR_SUBJECT, 1.1f, "Brightness:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Brightness:") + 10), 425, COLOUR_VALUE, 1.1f, "%d%%", getBrightness());
	
	int volume = 0;
	if (R_SUCCEEDED(sceAVConfigGetSystemVol(&volume)))
	{
		vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "Volume:");
		vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Volume:") + 10), 465, COLOUR_VALUE, 1.1f, "%d", volume);
	}
}

SceVoid psnMenu(SceVoid)
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "PSN Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "PSN Menu");
	
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "NP:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "NP:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", regMgrGetInt("/CONFIG/NP/", "enable_np")? "enabled" : "disabled");
	
	//vita2d_pvf_draw_textf(font, 364, 305, COLOUR_SUBJECT, 1.1f, "Account ID:");
	//vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Account ID:") + 10), 305, COLOUR_VALUE, 1.1f, "%s",  regMgrGetBin("/CONFIG/NP/", "account_id"));
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "Login ID:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Login ID:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", regMgrGetStr("/CONFIG/NP/", "login_id"));
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "Password:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Password:") + 10), 345, COLOUR_VALUE, 1.1f, "%s", regMgrGetStr("/CONFIG/NP/", "password"));
}

static SceInt controls(SceVoid)
{
	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	pressed = pad.buttons & ~old_pad.buttons;
	
	old_pad = pad;
	return 0;
}

int touchButton(int selection)
{
	if (touchCheckIsPressed()) 
	{
		if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 66 && touchGetY() <= 106)
			selection = 1;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 106 && touchGetY() <= 146)
			selection = 2;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 146 && touchGetY() <= 186)
			selection = 3;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 186 && touchGetY() <= 226)
			selection = 4;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 226 && touchGetY() <= 266)
			selection = 5;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 266 && touchGetY() <= 306)
			selection = 6;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 306 && touchGetY() <= 346)
			selection = 7;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 346 && touchGetY() <= 386)
			selection = 8;
		else if (touchGetX() >= 17 && touchGetX() <= 345 && touchGetY() >= 386 && touchGetY() <= 426)
			selection = 9;
	}
	
	return selection;
}

SceVoid mainMenu(SceVoid)
{
	SceInt MenuSelection = 1; // Pretty obvious
	SceInt selector_y = 26; // The y position of the first selection
	SceInt selector_image_y = 0; // Determines the starting y position of the selection
	
	while (1) 
	{
        selector_image_y = selector_y + (selector_yDistance * MenuSelection); //Determines where the selection image is drawn for each selection
		
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		vita2d_draw_texture(VITAident, 0, 0);
		
		vita2d_draw_rectangle(17, selector_image_y, 328, 40, RGBA8(242, 119, 62, 255));
		
		vita2d_pvf_draw_textf(font, 15, 30, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "VITAident 0.7.4");
		
		vita2d_pvf_draw_textf(font, 25, 92, MenuSelection == 1? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Kernel Information");
		vita2d_pvf_draw_textf(font, 25, 132, MenuSelection == 2? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "System Information");
		vita2d_pvf_draw_textf(font, 25, 172, MenuSelection == 3? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Battery Information");
		vita2d_pvf_draw_textf(font, 25, 212, MenuSelection == 4? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Storage Information");
		vita2d_pvf_draw_textf(font, 25, 252, MenuSelection == 5? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "WiFi Profiles");
		vita2d_pvf_draw_textf(font, 25, 292, MenuSelection == 6? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Miscelleanous");
		vita2d_pvf_draw_textf(font, 25, 332, MenuSelection == 7? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Config");
		vita2d_pvf_draw_textf(font, 25, 372, MenuSelection == 8? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "PSN");
		vita2d_pvf_draw_textf(font, 25, 412, MenuSelection == 9? COLOUR_MAINMENU_HIGHLIGHT : COLOUR_MAINMENU, 1.1f, "Exit");
		
		controls();
		touchUpdate();
		
		MenuSelection = touchButton(MenuSelection);
		
		if(pressed & SCE_CTRL_DOWN)
			MenuSelection++; //Moves the selector down
        else if(pressed & SCE_CTRL_UP)
			MenuSelection--; //Moves the selector up
        
        if (MenuSelection > MAX_ITEMS) 
			MenuSelection = 1; //Sets the selection to the first
        if (MenuSelection < 1) 
			MenuSelection = MAX_ITEMS; //Sets the selection back to last
		
		switch (MenuSelection)
		{
			case 1:
				kernelMenu();
				break;
				
			case 2:
				systemMenu();
				break;
				
			case 3:
				batteryMenu();
				break;
				
			case 4:
				storageMenu();
				break;
				
			case 5:
				wifiMenu();
				
				if (pressed & SCE_CTRL_LTRIGGER)
				{
					if (wifiPage == 1)
						wifiPage = 0;
				}
				else if (pressed & SCE_CTRL_RTRIGGER)
				{
					if ((wifiPage == 0) && (strcmp(regMgrGetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0))
						wifiPage = 1;
				}
				
				break;
				
			case 6:
				miscMenu();
				break;
				
			case 7:
				configMenu();
				break;
				
			case 8:
				psnMenu();
				break;
				
			case 9:
				if ((getEnterButton() == SCE_FALSE) && (pressed & SCE_CTRL_CIRCLE))
					sceKernelExitProcess(0);
				else if (pressed & SCE_CTRL_CROSS)
					sceKernelExitProcess(0);
				break;
		}
		
		endDrawing();
	}
}

int main(int argc, char *argv[]) 
{
	initAppUtil();
	initNet();
	sceCompatInitEx(0);
	sceCompatStart();
	vita2d_init();
	initTouch();
	
	vita2d_set_clear_color(COLOUR_MENU);
	
	VITAident = vita2d_load_PNG_buffer_filter(&_binary_res_VITAident_png_start);
	drive = vita2d_load_PNG_buffer_filter(&_binary_res_drive_png_start);
	
	font = vita2d_load_default_pvf();
	
	while(1)
		mainMenu();
	
	vita2d_fini();
	vita2d_free_texture(VITAident);
	vita2d_free_texture(drive);
	vita2d_free_pvf(font);
	sceCompatStop();
	sceCompatUninit();
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}