#include "app.h"
#include "fs.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "screenshot.h"
#include "utils.h"

int kernelMenu()
{
	while (1) 
	{
		vita2d_start_drawing();
		vita2d_clear_screen();
	
		vita2d_draw_texture(VITAident, 0, -6);
		
		vita2d_pgf_draw_textf(font, 785, 25, RGBA8(93, 93, 93, 255), 1.0f, "Kernel Menu");
		
		vita2d_pgf_draw_textf(font, 5, 525, RGBA8(93, 93, 93, 255), 1.0f, "< Misc menu (L)");
		vita2d_pgf_draw_textf(font, 705, 525, RGBA8(93, 93, 93, 255), 1.0f, "(R) System menu >");
		
		vita2d_pgf_draw_textf(font, 20, 200, RGBA8(11, 199, 41, 255), 1.0f, "Firmware version: %.4s\n", getFwVersion());
		vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "Model version: 0x%08X | %s\n", getModel(), getDeviceType());
		vita2d_pgf_draw_textf(font, 20, 280, RGBA8(11, 199, 41, 255), 1.0f, "PS Vita CID: %s\n", getCID()); //Thanks Major_Tom
		//vita2d_pgf_draw_textf(font, 20, 320, RGBA8(11, 199, 41, 255), 1.0f, "PS Vita MCID: %.8s\n", getmCID());
		vita2d_pgf_draw_textf(font, 20, 320, RGBA8(11, 199, 41, 255), 1.0f, "PSID: %02X\n", getPSID()); //Thanks SMOKE
		vita2d_pgf_draw_textf(font, 20, 360, RGBA8(11, 199, 41, 255), 1.0f, "PS Vita unit: %s\n", getUnit());
		
		endDrawing();
		
		controls();
		
		if (pressed & SCE_CTRL_CIRCLE)
			mainMenu();
		
		if (pressed & SCE_CTRL_LTRIGGER)
			miscMenu();
		else if (pressed & SCE_CTRL_RTRIGGER)
			systemMenu();
	}
	
	return 0;
}

int systemMenu()
{
	while (1) 
	{
		vita2d_start_drawing();
		vita2d_clear_screen();
	
		vita2d_draw_texture(VITAident, 0, -6);
		
		vita2d_pgf_draw_textf(font, 775, 25, RGBA8(93, 93, 93, 255), 1.0f, "System Menu");
		
		vita2d_pgf_draw_textf(font, 5, 525, RGBA8(93, 93, 93, 255), 1.0f, "< Kernel menu (L)");
		vita2d_pgf_draw_textf(font, 703, 525, RGBA8(93, 93, 93, 255), 1.0f, "(R) Battery menu >");
		
		vita2d_pgf_draw_textf(font, 20, 200, RGBA8(11, 199, 41, 255), 1.0f, "Language: %s\n", getLang());
		vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "MAC address: %s\n", getMacAddress());
		vita2d_pgf_draw_textf(font, 20, 280, RGBA8(11, 199, 41, 255), 1.0f, "IP address: %s\n", getIP());
		vita2d_pgf_draw_textf(font, 20, 320, RGBA8(11, 199, 41, 255), 1.0f, "ARM clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Cpu));
		vita2d_pgf_draw_textf(font, 20, 360, RGBA8(11, 199, 41, 255), 1.0f, "BUS clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Bus));
		vita2d_pgf_draw_textf(font, 20, 400, RGBA8(11, 199, 41, 255), 1.0f, "GPU clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Gpu));
		vita2d_pgf_draw_textf(font, 20, 440, RGBA8(11, 199, 41, 255), 1.0f, "GPU Xbar clock frequency: %d MHz\n\n", getClockFrequency(ClockFrequencyType_GpuXbar));
		
		endDrawing();	
		
		controls();
		
		if (pressed & SCE_CTRL_CIRCLE)
			mainMenu();
		
		if (pressed & SCE_CTRL_LTRIGGER)
			kernelMenu();
		else if (pressed & SCE_CTRL_RTRIGGER)
			batteryMenu();
	}
	
	return 0;
}

int batteryMenu()
{
	while (1) 
	{
		vita2d_start_drawing();
		vita2d_clear_screen();
	
		vita2d_draw_texture(VITAident, 0, -6);
		
		vita2d_pgf_draw_textf(font, 772, 25, RGBA8(93, 93, 93, 255), 1.0f, "Battery Menu");
		
		vita2d_pgf_draw_textf(font, 5, 525, RGBA8(93, 93, 93, 255), 1.0f, "< System menu (L)");
		vita2d_pgf_draw_textf(font, 734, 525, RGBA8(93, 93, 93, 255), 1.0f, "(R) Misc menu >");
		
		vita2d_pgf_draw_textf(font, 20, 200, RGBA8(11, 199, 41, 255), 1.0f, "Battery percentage: %s\n", displayBatteryPercentage());
		vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "Battery remaining Capacity: %s\n", GetBatteryRemainCapacity());
		int batteryLifeTime = scePowerGetBatteryLifeTime();
		vita2d_pgf_draw_textf(font, 20, 280, RGBA8(11, 199, 41, 255), 1.0f, "Battery life time: %02dh %02dm\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
		vita2d_pgf_draw_textf(font, 20, 320, RGBA8(11, 199, 41, 255), 1.0f, "Battery temperature: %s C (%s F)\n", getBatteryTemp(0), getBatteryTemp(1));
		vita2d_pgf_draw_textf(font, 20, 360, RGBA8(11, 199, 41, 255), 1.0f, "Battery voltage: %s V\n\n", getBatteryVoltage());
		
		endDrawing();
		
		controls();
		
		if (pressed & SCE_CTRL_CIRCLE)
			mainMenu();
		
		if (pressed & SCE_CTRL_LTRIGGER)
			systemMenu();
		else if (pressed & SCE_CTRL_RTRIGGER)
			miscMenu();
	}
	
	return 0;
}

int miscMenu()
{
	while (1) 
	{
		vita2d_start_drawing();
		vita2d_clear_screen();
	
		vita2d_draw_texture(VITAident, 0, -6);
		
		vita2d_pgf_draw_textf(font, 805, 25, RGBA8(93, 93, 93, 255), 1.0f, "Misc Menu");
		
		vita2d_pgf_draw_textf(font, 5, 525, RGBA8(93, 93, 93, 255), 1.0f, "< Battery menu (L)");
		vita2d_pgf_draw_textf(font, 715, 525, RGBA8(93, 93, 93, 255), 1.0f, "(R) Kernel menu >");
		
		vita2d_pgf_draw_textf(font, 20, 200, RGBA8(11, 199, 41, 255), 1.0f, "Username: %s\n", getUser());
		
		if (vshRemovableMemoryGetCardInsertState() == 1)
		{
			vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "Memory card storage: %s\n", getStorageInfo(0));
			vita2d_pgf_draw_textf(font, 20, 280, RGBA8(11, 199, 41, 255), 1.0f, "Memory card storage free: %s\n", getStorageInfo(1));	
		}
		else if (vshRemovableMemoryGetCardInsertState() == 0)
		{
			vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "Internal storage: %s\n", getStorageInfo(0));
			vita2d_pgf_draw_textf(font, 20, 280, RGBA8(11, 199, 41, 255), 1.0f, "Internal storage free: %s\n", getStorageInfo(1));
		}
		/*else
			vita2d_pgf_draw_textf(font, 20, 240, RGBA8(11, 199, 41, 255), 1.0f, "Memory card not inserted."); //Although this is basically impossible on PCH-1000*/
		
		endDrawing();
		
		controls();
		
		if (pressed & SCE_CTRL_CIRCLE)
			mainMenu();
		
		if (pressed & SCE_CTRL_LTRIGGER)
			batteryMenu();
		else if (pressed & SCE_CTRL_RTRIGGER)
			kernelMenu();
	}
	
	return 0;
}

int mainMenu()
{
	int MenuSelection = 1; // Pretty obvious
	int selector_x = 0; //The x position of the first selection
	int selector_y = 120; //The y position of the first selection
	int numMenuItems = 5; //Amount of items in the menu
	int selector_image_x = 0; //Determines the starting x position of the selection
	int selector_image_y = 0; //Determines the starting y position of the selection
	
	while (1) 
	{	
		selector_image_x = selector_x + (selector_xDistance * MenuSelection); //Determines where the selection image is drawn for each selection
        selector_image_y = selector_y + (selector_yDistance * MenuSelection); //Determines where the selection image is drawn for each selection
		
		vita2d_start_drawing();
		vita2d_clear_screen();
	
		vita2d_draw_texture(VITAident, 0, -6);
		vita2d_draw_rectangle(selector_image_x, selector_image_y, 960, 40, RGBA8(80, 80, 80, 255));
		
		vita2d_pgf_draw_textf(font, 780, 524, RGBA8(11, 199, 41, 255), 1.0, "VITAident 0.3\n\n");
		
		vita2d_pgf_draw_textf(font, 20, 200, RGBA8(11, 199, 41, 255), 1.0, "Kernel Information");
		
		vita2d_pgf_draw_textf(font, 20, 250, RGBA8(11, 199, 41, 255), 1.0, "System Information");
		
		vita2d_pgf_draw_textf(font, 20, 300, RGBA8(11, 199, 41, 255), 1.0, "Battery Information");
		
		vita2d_pgf_draw_textf(font, 20, 350, RGBA8(11, 199, 41, 255), 1.0, "Miscelleanous");
		
		vita2d_pgf_draw_textf(font, 20, 400, RGBA8(11, 199, 41, 255), 1.0, "Exit");
		
		controls();
		
		if(pressed & SCE_CTRL_DOWN)
			MenuSelection++; //Moves the selector down
        else if(pressed & SCE_CTRL_UP)
			MenuSelection--; //Moves the selector up
        
        if (MenuSelection > numMenuItems) 
			MenuSelection = 1; //Sets the selection to the first
        if (MenuSelection < 1) 
			MenuSelection = numMenuItems; //Sets the selection back to last
		
		endDrawing();
		
		if ((MenuSelection == 1) && (pressed & SCE_CTRL_CROSS))
		{
			kernelMenu();
        }
		
		else if ((MenuSelection == 2) && (pressed & SCE_CTRL_CROSS))
		{
			systemMenu();
        }
		
		else if ((MenuSelection == 3) && (pressed & SCE_CTRL_CROSS))
		{
			batteryMenu();
        }
		
		else if ((MenuSelection == 4) && (pressed & SCE_CTRL_CROSS))
		{
			miscMenu();
        }
		
		else if ((MenuSelection == 5) && (pressed & SCE_CTRL_CROSS))
		{
			sceKernelExitProcess(0);
        }
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
	
	VITAident = loadPngWithFilter("ux0:/data/VID000016/res/VITAident.png");
	
	font = vita2d_load_custom_pgf("ux0:/data/VID000016/fonts/font.pgf");
	
	while(1)
	{
        mainMenu();
	
		/*if (pressed & SCE_CTRL_START)
		{
			if (!(dirExists("ux0:/data/VID000016")))
			{
				SceUID dir;
				
				dir = sceIoDopen("ux0:/data/VID000016");
				sceIoMkdir("ux0:/data/VID000016", 0777);
				sceIoDclose(dir);
				
				dir = sceIoDopen("ux0:/data/VID000016/screenshots");
				sceIoMkdir("ux0:/data/VID000016/screenshots", 0777);
				sceIoDclose(dir);
			}
			
			captureScreenshot("ux0:/data/VID000016/screenshots/VITAident.bmp");
			break;
		}*/
	}
	
	vita2d_fini();
	vita2d_free_texture(VITAident);
	vita2d_free_pgf(font);
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
