#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

#include <psp2/power.h>
#include <psp2/udcd.h>

#include <stdio.h>
#include <string.h>

typedef enum 
{
	clockFrequencyType_cpu,
	clockFrequencyType_bus,
	clockFrequencyType_gpu,
	clockFrequencyType_gpuXbar
} clockFrequencyType;

//int scePowerGetBatteryElec(void); Crashes the VITA
int scePowerGetUsingWireless(void);

int getClockFrequency(clockFrequencyType type);
const char * getBatteryStatus(void);
char * getBatteryPercentage(void);
char * getUsingWireless(void);
char * getBatterySOH(void);
char * getBatteryCycleCount(void);
char * getBatteryCapacity(void);
char * getBatteryRemainCapacity(void);
char * getBatteryTemp(int type);
char * getBatteryVoltage(void);
char * getUdcdCableState(void);
char * getUsbChargingState(void);

#endif