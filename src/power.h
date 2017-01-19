#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

#include <psp2/power.h>
#include <psp2/udcd.h>

#include <stdio.h>
#include <string.h>

typedef enum {
	ClockFrequencyType_Cpu = 0,
	ClockFrequencyType_Bus,
	ClockFrequencyType_Gpu,
	ClockFrequencyType_GpuXbar
} ClockFrequencyType;

int scePowerGetBatteryTemp();
int scePowerGetBatteryVolt();
int scePowerGetBatterySOH();
int scePowerGetBatteryCycleCount();

int scePowerGetGpuXbarClockFrequency();

int getClockFrequency(ClockFrequencyType type);
const char * getBatteryStatus();
char * getBatteryPercentage();
char * getBatterySOH();
char * getBatteryCycleCount();
char * getBatteryCapacity();
char * getBatteryRemainCapacity();
char * getBatteryTemp(int type);
char * getBatteryVoltage();
char * getUdcdCableState();
char * getUdcdChargingState();

#endif