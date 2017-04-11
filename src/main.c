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
	vita2d_pvf_draw_textf(font, 585, 225, RGBA8(0, 0, 0, 255), 1.1f, "Kernel Menu");
		
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
	vita2d_pvf_draw_textf(font, 585, 225, RGBA8(0, 0, 0, 255), 1.1f, "System Menu");
		
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
	vita2d_pvf_draw_textf(font, 585, 225, RGBA8(0, 0, 0, 255), 1.1f, "Battery Menu");
		
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
	vita2d_pvf_draw_textf(font, 585, 225, RGBA8(0, 0, 0, 255), 1.1f, "Misc Menu");
	
	vita2d_pvf_draw_textf(font, 364, 265, RGBA8(51, 51, 51, 255), 1.1f, "Enter button: %s\n", getEnterButton());
	
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

int mainMenu()
{
	int MenuSelection = 1; // Pretty obvious
	int selector_x = 17; //The x position of the first selection
	int selector_y = 26; //The y position of the first selection
	int numMenuItems = 5; //Amount of items in the menu
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
		
		vita2d_pvf_draw_textf(font, 15, 30, RGBA8(255, 255, 255, 255), 1.1f, "VITAident 0.7.1");
		
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
			vita2d_pvf_draw_textf(font, 25, 252, RGBA8(255, 255, 255, 255), 1.1f, "Exit");
		else
			vita2d_pvf_draw_textf(font, 25, 252, RGBA8(78, 74, 67, 255), 1.1f, "Exit");
		
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
		
		else if ((MenuSelection == 5) && (pressed & SCE_CTRL_CROSS))
			sceKernelExitProcess(0);
		
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
	{
        mainMenu();
	}
	
	vita2d_fini();
	vita2d_free_texture(VITAident);
	vita2d_free_pvf(font);
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
