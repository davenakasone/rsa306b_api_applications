#include <stdio.h>
#include <stdlib.h>
#include "RSA_API.h"



int main()
{
	ReturnStatus ret;
	
	char apiVersion[DEVINFO_MAX_STRLEN];
	ret = DEVICE_GetAPIVersion(apiVersion);
	printf("API Version : %s\n", apiVersion);

	int numDev = 1;
	int devID[DEVSRCH_MAX_NUM_DEVICES];
	char devSN[DEVSRCH_MAX_NUM_DEVICES][DEVSRCH_SERIAL_MAX_STRLEN];
	char devType[DEVSRCH_MAX_NUM_DEVICES][DEVSRCH_TYPE_MAX_STRLEN];
	ret = DEVICE_Search(&numDev, devID, devSN, devType);
	
	if (ret)
	{
		printf("\n ERROR: %s\n", DEVICE_GetErrorString(ret));	
		return 1;
	}

	printf("\nDetected Devices:\n");
	for(int i = 0; i < numDev; i++)
	{
		printf("deviceID: %i,\t SN: %s,\t Type: %s\n", devID[i], devSN[i], devType[i]);	
	}
	
	if(numDev > 0)
	{
		printf("\nConnecting to Device ID %i\n", devID[0]);
		ret = DEVICE_Connect(devID[0]);
		if (ret)
		{
			printf("\n ERROR: %s\n", DEVICE_GetErrorString(ret));	
			return 1;
		}
		
		char sn[DEVINFO_MAX_STRLEN];
		ret = DEVICE_GetSerialNumber(sn);

		printf("Device Serial Number: %s\n", sn);
	}
	else
	{
		printf("No Devices Found\n");
		return 0;
	}
}

