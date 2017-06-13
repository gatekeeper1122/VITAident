#include "app.h"
#include "fs.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "utils.h"

extern unsigned char _binary_res_VITAident_png_start;

void kernelMenu()
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Kernel Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "Kernel Menu");
		
	//vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Firmware version: %.4s\n", getFwVersion(false));
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "System version: %.4s\n", getFwVersion(true));
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "Model version: %s %s (0x%08X)\n", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());
	vita2d_pvf_draw_textf(font, 364, 385, RGBA8(51, 51, 51, 255), 1.1f, "PS Vita unit: %s\n", getUnit());
	vita2d_pvf_draw_textf(font, 364, 425, RGBA8(51, 51, 51, 255), 1.1f, "Motherboard: %s\n", getBoard());
	vita2d_pvf_draw_textf(font, 364, 465, RGBA8(51, 51, 51, 255), 1.1f, "PS Vita CID: %s\n", getCID()); //Thanks Major_Tom
	vita2d_pvf_draw_textf(font, 364, 505, RGBA8(51, 51, 51, 255), 1.1f, "PSID: %02X\n", getPSID()); //Thanks SMOKE
}

void systemMenu()
{
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "System Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "System Menu");
		
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Language: %s\n", getLang());
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "MAC address: %s\n", getMacAddress());
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "IP address: %s\n", getIP());
	vita2d_pvf_draw_textf(font, 364, 385, RGBA8(51, 51, 51, 255), 1.1f, "Username: %s\n", getUser());
	vita2d_pvf_draw_textf(font, 364, 425, RGBA8(51, 51, 51, 255), 1.1f, "ARM clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Cpu));
	vita2d_pvf_draw_textf(font, 364, 465, RGBA8(51, 51, 51, 255), 1.1f, "BUS clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Bus));
	vita2d_pvf_draw_textf(font, 364, 505, RGBA8(51, 51, 51, 255), 1.1f, "GPU Xbar clock frequency: %d MHz\n\n", getClockFrequency(ClockFrequencyType_GpuXbar));
}

void batteryMenu()
{
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Battery Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "Battery Menu");
		
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Battery percentage: %s (%s)\n", getBatteryPercentage(), getBatteryStatus());
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "Battery capacity: %s (remaining: %s)\n", getBatteryCapacity(), getBatteryRemainCapacity());
	int batteryLifeTime = scePowerGetBatteryLifeTime();
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "Battery life time: %02dh %02dm (SOH: %s)\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60), getBatterySOH());
	vita2d_pvf_draw_textf(font, 364, 385, RGBA8(51, 51, 51, 255), 1.1f, "Battery temperature: %s C (%s F)\n", getBatteryTemp(0), getBatteryTemp(1));
	vita2d_pvf_draw_textf(font, 364, 425, RGBA8(51, 51, 51, 255), 1.1f, "Battery voltage: %s V (cycle count: %s)\n\n", getBatteryVoltage(), getBatteryCycleCount());
	vita2d_pvf_draw_textf(font, 364, 465, RGBA8(51, 51, 51, 255), 1.1f, "Udcd state: %s (%s)\n", getUdcdCableState(), getUsbChargingState());

}

void miscMenu()
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Misc Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "Misc Menu");
	
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Enter button: %s\n", getEnterButton()? "Cross (X)" : "Circle (O)");
	
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "Brightness: %d%%\n",  getBrightness());
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "Volume: %d%%\n",  getVolume());

	char free_size_string[16], max_size_string[16];
	SceOff freeSize = getPartitionInfo(0, "ur0:");
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	getSizeString(free_size_string, freeSize);
	getSizeString(max_size_string, maxSize);

	vita2d_pvf_draw_textf(font, 364, 385, RGBA8(51, 51, 51, 255), 1.1f, "Internal storage: %s\n", max_size_string);
	vita2d_pvf_draw_textf(font, 364, 425, RGBA8(51, 51, 51, 255), 1.1f, "Internal storage free: %s\n", free_size_string);
	
	if (vshRemovableMemoryGetCardInsertState() == 1)
	{
		vita2d_pvf_draw_textf(font, 364, 465, RGBA8(51, 51, 51, 255), 1.1f, "Memory card storage: %s\n", getStorageInfo(0));
		vita2d_pvf_draw_textf(font, 364, 505, RGBA8(51, 51, 51, 255), 1.1f, "Memory card storage free: %s\n", getStorageInfo(1));	
	}	
}

void configMenu()
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Config Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "Config Menu");
	
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Airplane mode: %s\n", regMgrGetInt("/CONFIG/SYSTEM/", "flight_mode")? "enabled" : "disabled");
	
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "Bluetooth: %s\n",  regMgrGetInt("/CONFIG/BT/", "bt_enable")? "enabled" : "disabled");
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "WiFi power save: %s\n",  regMgrGetInt("/CONFIG/NET/", "wifi_power_save")? "enabled" : "disabled");
	vita2d_pvf_draw_textf(font, 364, 385, RGBA8(51, 51, 51, 255), 1.1f, "Screen lock passcode: %s\n",  regMgrGetStr("/CONFIG/SECURITY/SCREEN_LOCK/", "passcode"));
}

void psnMenu()
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "PSN Menu")) / 2) + 344), 225, RGBA8(0, 0, 0, 255), 1.1f, "PSN Menu");
	
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "NP: %s\n", regMgrGetInt("/CONFIG/NP/", "enable_np")? "enabled" : "disabled");
	
	//vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "Account ID: %s\n",  regMgrGetBin("/CONFIG/NP/", "account_id"));
	vita2d_pvf_draw_textf(font, 364, 305, RGBA8(51, 51, 51, 255), 1.1f, "Login ID: %s\n",  regMgrGetStr("/CONFIG/NP/", "login_id"));
	vita2d_pvf_draw_textf(font, 364, 345, RGBA8(51, 51, 51, 255), 1.1f, "Password: %s\n",  regMgrGetStr("/CONFIG/NP/", "password"));
	vita2d_pvf_draw_textf(font, 364, 505, RGBA8(51, 51, 51, 255), 1.1f, "Press X to dump your CID into ux0:/ %s", (fileExists("ux0:/cid.txt"))? "(Dumped)" : "");
}

int mainMenu()
{
	int MenuSelection = 1; // Pretty obvious
	int selector_x = 17; //The x position of the first selection
	int selector_y = 26; //The y position of the first selection
	int numMenuItems = 7; //Amount of items in the menu
	int selector_image_x = 0; //Determines the starting x position of the selection
	int selector_image_y = 0; //Determines the starting y position of the selection
	
	static char version[16] = "";
	strcpy(version, getFwVersion(false)); //For saftey purposes, I don't want this in a while loop.
	
	while (1) 
	{	
		selector_image_x = selector_x + (selector_xDistance * MenuSelection); //Determines where the selection image is drawn for each selection
        selector_image_y = selector_y + (selector_yDistance * MenuSelection); //Determines where the selection image is drawn for each selection
		
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		vita2d_draw_texture(VITAident, 0, 0);
		
		vita2d_draw_rectangle(selector_image_x, selector_image_y, 328, 40, RGBA8(242, 119, 62, 255));
		
		vita2d_pvf_draw_textf(font, 15, 30, RGBA8(255, 255, 255, 255), 1.1f, "VITAident 0.7.3");
		
		if (MenuSelection == 1)
			vita2d_pvf_draw_textf(font, 25, 92, RGBA8(255, 255, 255, 255), 1.1f, "Kernel Information");
		else 
			vita2d_pvf_draw_textf(font, 25, 92, RGBA8(78, 74, 67, 255), 1.1f, "Kernel Information");
		
		if (MenuSelection == 2)
			vita2d_pvf_draw_textf(font, 25, 132, RGBA8(255, 255, 255, 255), 1.1f, "System Information");
		else
			vita2d_pvf_draw_textf(font, 25, 132, RGBA8(78, 74, 67, 255), 1.1f, "System Information");
		
		if (MenuSelection == 3)
			vita2d_pvf_draw_textf(font, 25, 172, RGBA8(255, 255, 255, 255), 1.1f, "Battery Information");
		else
			vita2d_pvf_draw_textf(font, 25, 172, RGBA8(78, 74, 67, 255), 1.1f, "Battery Information");
		
		if (MenuSelection == 4)
			vita2d_pvf_draw_textf(font, 25, 212, RGBA8(255, 255, 255, 255), 1.1f, "Miscelleanous");
		else
			vita2d_pvf_draw_textf(font, 25, 212, RGBA8(78, 74, 67, 255), 1.1f, "Miscelleanous");
		
		if (MenuSelection == 5)
			vita2d_pvf_draw_textf(font, 25, 252, RGBA8(255, 255, 255, 255), 1.1f, "Config");
		else
			vita2d_pvf_draw_textf(font, 25, 252, RGBA8(78, 74, 67, 255), 1.1f, "Config");
		
		if (MenuSelection == 6)
			vita2d_pvf_draw_textf(font, 25, 292, RGBA8(255, 255, 255, 255), 1.1f, "PSN");
		else
			vita2d_pvf_draw_textf(font, 25, 292, RGBA8(78, 74, 67, 255), 1.1f, "PSN");
		
		if (MenuSelection == 7)
			vita2d_pvf_draw_textf(font, 25, 332, RGBA8(255, 255, 255, 255), 1.1f, "Exit");
		else
			vita2d_pvf_draw_textf(font, 25, 332, RGBA8(78, 74, 67, 255), 1.1f, "Exit");
		
		controls();
		
		if(pressed & SCE_CTRL_DOWN)
			MenuSelection++; //Moves the selector down
        else if(pressed & SCE_CTRL_UP)
			MenuSelection--; //Moves the selector up
        
        if (MenuSelection > numMenuItems) 
			MenuSelection = 1; //Sets the selection to the first
        if (MenuSelection < 1) 
			MenuSelection = numMenuItems; //Sets the selection back to last
		
		if (MenuSelection == 1)
		{
			kernelMenu();
			vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Firmware version: %.4s\n", version);
		}
		
		else if (MenuSelection == 2)
			systemMenu();
		
		else if (MenuSelection == 3)
			batteryMenu();
		
		else if (MenuSelection == 4) 
			miscMenu();
		
		else if (MenuSelection == 5) 
			configMenu();
		
		else if (MenuSelection == 6) 
		{
			psnMenu();
			
			if (pressed & SCE_CTRL_CROSS)
			{
				char buf[32];
				strcpy(buf, getCID());
				writeFile("ux0:/cid.txt", buf, strlen(buf) + 1);
			}	
		}
		
		else if (MenuSelection == 7)
		{
			if (getEnterButton() == 0)
			{
				if (pressed & SCE_CTRL_CIRCLE)
					sceKernelExitProcess(0);
			}
			else
			{
				if (pressed & SCE_CTRL_CROSS)
					sceKernelExitProcess(0);
			}
		}
		
		endDrawing();
	}	
	
	return 0;
}

int controls()
{
	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	pressed = pad.buttons & ~old_pad.buttons;
	
	old_pad = pad;
	return 0;
}

int main(int argc, char *argv[]) 
{
	initAppUtil();
	initNet();
	vita2d_init();
	
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
	
	VITAident = loadPngWithFilter(&_binary_res_VITAident_png_start);
	
	font = vita2d_load_default_pvf();
	
	while(1)
        mainMenu();
	
	vita2d_fini();
	vita2d_free_texture(VITAident);
	vita2d_free_pvf(font);
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
