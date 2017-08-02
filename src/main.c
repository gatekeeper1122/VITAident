#include "app.h"
#include "fs.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "utils.h"

extern SceUChar8 _binary_res_VITAident_png_start;

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

SceVoid miscMenu(SceVoid)
{		
	vita2d_pvf_draw_textf(font, (((616 - vita2d_pvf_text_width(font, 1.1f, "Misc Menu")) / 2) + 344), 225, COLOUR_MENU, 1.1f, "Misc Menu");
	
	vita2d_pvf_draw_text(font, 364, 265, COLOUR_SUBJECT, 1.1f, "Username:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Username:") + 10), 265, COLOUR_VALUE, 1.1f, "%s", getUser());
	
	vita2d_pvf_draw_text(font, 364, 305, COLOUR_SUBJECT, 1.1f, "IP address:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "IP address:") + 10), 305, COLOUR_VALUE, 1.1f, "%s", getIP());
	
	vita2d_pvf_draw_text(font, 364, 345, COLOUR_SUBJECT, 1.1f, "Enter button:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Enter button:") + 10), 345, COLOUR_VALUE, 1.1f, "%s", getEnterButton()? "Cross (X)" : "Circle (O)");

	char free_size_string[16], max_size_string[16];
	SceOff freeSize = getPartitionInfo(0, "ur0:");
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	getSizeString(free_size_string, freeSize);
	getSizeString(max_size_string, maxSize);

	vita2d_pvf_draw_text(font, 364, 385, COLOUR_SUBJECT, 1.1f, "Internal storage:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Internal storage:") + 10), 385, COLOUR_VALUE, 1.1f, "%s", max_size_string);
	
	vita2d_pvf_draw_text(font, 364, 425, COLOUR_SUBJECT, 1.1f, "Internal storage free:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Internal storage free:") + 10), 425, COLOUR_VALUE, 1.1f, "%s", free_size_string);
	
	if (vshRemovableMemoryGetCardInsertState() == 1)
	{
		vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "Memory card storage:");
		vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Memory card storage:") + 10), 465, COLOUR_VALUE, 1.1f, "%s", getStorageInfo(0));
		
		vita2d_pvf_draw_text(font, 364, 505, COLOUR_SUBJECT, 1.1f, "Memory card storage free:");	
		vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Memory card storage free:") + 10), 505, COLOUR_VALUE, 1.1f, "%s", getStorageInfo(1));
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
	
	vita2d_pvf_draw_text(font, 364, 465, COLOUR_SUBJECT, 1.1f, "Volume:");
	vita2d_pvf_draw_textf(font, (364 + vita2d_pvf_text_width(font, 1.1f, "Volume:") + 10), 465, COLOUR_VALUE, 1.1f, "%d%%", getVolume());
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
		
		if (MenuSelection == 1)
			vita2d_pvf_draw_textf(font, 25, 92, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "Kernel Information");
		else 
			vita2d_pvf_draw_textf(font, 25, 92, COLOUR_MAINMENU, 1.1f, "Kernel Information");
		
		if (MenuSelection == 2)
			vita2d_pvf_draw_textf(font, 25, 132, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "System Information");
		else
			vita2d_pvf_draw_textf(font, 25, 132, COLOUR_MAINMENU, 1.1f, "System Information");
		
		if (MenuSelection == 3)
			vita2d_pvf_draw_textf(font, 25, 172, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "Battery Information");
		else
			vita2d_pvf_draw_textf(font, 25, 172, COLOUR_MAINMENU, 1.1f, "Battery Information");
		
		if (MenuSelection == 4)
			vita2d_pvf_draw_textf(font, 25, 212, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "Miscelleanous");
		else
			vita2d_pvf_draw_textf(font, 25, 212, COLOUR_MAINMENU, 1.1f, "Miscelleanous");
		
		if (MenuSelection == 5)
			vita2d_pvf_draw_textf(font, 25, 252, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "Config");
		else
			vita2d_pvf_draw_textf(font, 25, 252, COLOUR_MAINMENU, 1.1f, "Config");
		
		if (MenuSelection == 6)
			vita2d_pvf_draw_textf(font, 25, 292, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "PSN");
		else
			vita2d_pvf_draw_textf(font, 25, 292, COLOUR_MAINMENU, 1.1f, "PSN");
		
		if (MenuSelection == 7)
			vita2d_pvf_draw_textf(font, 25, 332, COLOUR_MAINMENU_HIGHLIGHT, 1.1f, "Exit");
		else
			vita2d_pvf_draw_textf(font, 25, 332, COLOUR_MAINMENU, 1.1f, "Exit");
		
		controls();
		
		if(pressed & SCE_CTRL_DOWN)
			MenuSelection++; //Moves the selector down
        else if(pressed & SCE_CTRL_UP)
			MenuSelection--; //Moves the selector up
        
        if (MenuSelection > MAX_ITEMS) 
			MenuSelection = 1; //Sets the selection to the first
        if (MenuSelection < 1) 
			MenuSelection = MAX_ITEMS; //Sets the selection back to last
		
		if (MenuSelection == 1)
			kernelMenu();
		else if (MenuSelection == 2)
			systemMenu();
		else if (MenuSelection == 3)
			batteryMenu();
		else if (MenuSelection == 4) 
			miscMenu();
		else if (MenuSelection == 5) 
			configMenu();
		else if (MenuSelection == 6) 
			psnMenu();
		else if (MenuSelection == 7)
		{
			if ((getEnterButton() == SCE_FALSE) && (pressed & SCE_CTRL_CIRCLE))
				sceKernelExitProcess(0);
			else if (pressed & SCE_CTRL_CROSS)
				sceKernelExitProcess(0);
		}
		
		endDrawing();
	}
}

int main(int argc, char *argv[]) 
{
	initAppUtil();
	initNet();
	vita2d_init();
	
	vita2d_set_clear_color(COLOUR_MENU);
	
	VITAident = vita2d_load_PNG_buffer_filter(&_binary_res_VITAident_png_start);
	
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