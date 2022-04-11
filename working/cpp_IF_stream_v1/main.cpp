/*
    IQ stream may be faster
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_API.h"

#define BIG_WIDTH 1024
#define SMALL_WIDTH 128
//#define DEBUG_CLI -888

const char my_data[] = "./iq_outputs.txt";
char holder[BIG_WIDTH];
FILE* g_fptr = NULL;

RSA_API::ReturnStatus g_rs;     // from original search_connect()
int g_numFound = 0;             // from original search_connect()
int* g_deviceIDs;               // from original search_connect()
const char** g_deviceSerial;    // from original search_connect()
const char** g_deviceType;      // from original search_connect()
char g_apiVersion[200];         // from original search_connect()

double g_cf = 2.4453e9;                              // from original if_stream_example()
double g_refLevel = -30;                             // from original if_stream_example()
char g_fileDir [SMALL_WIDTH] = "./";                 // from original if_stream_example()
char g_fileName [SMALL_WIDTH] = "if_stream_test";    // from original if_stream_example()
int g_durationMsec = 1000;                           // from original if_stream_example()
int g_waitTime = 10;                                 // from original if_stream_example()

void search_and_connect (void);
void error_check (void);
void if_stream_example (void);
void if_playback (void);


int main
(
    int argc,
    char** argv,
    char** envp
)
{
	search_and_connect();
	if_stream_example();
	search_and_connect();
    
    std::cout << "Disconnecting...get rid of that output file" << std::endl;
    RSA_API::DEVICE_Disconnect();
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


void error_check
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	// noError = 0 is the only signal that indicates hardware is satisfactory
	// any other error code is a problem, and modifications are needed before proceeding
	if (g_rs != RSA_API::noError) 
	{
		std::cout << "\nError: " << g_rs << std::endl;
		std::exit(0);
	}
}


////~~~~


void search_and_connect
(
	void
)
{
	g_rs = RSA_API::DEVICE_GetAPIVersion(g_apiVersion);
	std::cout << "API Version: " << g_apiVersion << std::endl;
	g_rs = RSA_API::DEVICE_SearchInt(&g_numFound, &g_deviceIDs, &g_deviceSerial, &g_deviceType);
	if (g_numFound == 1)
	{
		// print_device_info()
		std::cout << "Device ID: " << 0;
		std::cout << ", Serial Number: " << g_deviceSerial[0];
		std::cout << ", Device Type: " << g_deviceType[0] << std::endl << std::endl;
		
		g_rs = RSA_API::DEVICE_Connect(g_deviceIDs[0]);
		error_check();
	}
	else
	{
		std::cout << "no devices or too many devices, exiting script." << std::endl;
		std::exit(0);
	}
}


////~~~~


void if_stream_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	bool writing = true;
	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);
	RSA_API::IFSTREAM_SetDiskFilePath(g_fileDir);
	RSA_API::IFSTREAM_SetDiskFilenameBase(g_fileName);
	RSA_API::IFSTREAM_SetDiskFilenameSuffix(-2);
	RSA_API::IFSTREAM_SetDiskFileLength(g_durationMsec);
	RSA_API::IFSTREAM_SetDiskFileMode(RSA_API::StreamingModeFramed);
	RSA_API::IFSTREAM_SetDiskFileCount(1);

	RSA_API::DEVICE_Run();
	RSA_API::IFSTREAM_SetEnable(true);
	while (writing == true)
	{
		sleep(g_waitTime/1000);
		RSA_API::IFSTREAM_GetActiveStatus(&writing);
	}
	RSA_API::DEVICE_Stop();

	std::cout << "\nIF stream aquried,  a big output file was made ,  any key to continue:  ";
	std::cin >> holder;
	RSA_API::DEVICE_Disconnect();
}


void if_playback
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_and_connect();
	snprintf(holder, BIG_WIDTH-1, "%s%s", g_fileDir, g_fileName);
	FILE* fp = fopen(holder, "rb");
	if (fp == NULL)
	{
		printf("Error Opening File: %s\n", holder);
	}
	
	int start = 0;
	int stop = 100;
	double skip = 0;
	bool loop = false;
	bool rt = true;
	bool complete = false;

	RSA_API::PLAYBACK_OpenDiskFile(holder, start, stop, skip, loop, rt);
	RSA_API::DEVICE_Run();
	while (complete == false)
	{
		RSA_API::PLAYBACK_GetReplayComplete(&complete);
	}
	RSA_API::DEVICE_Stop();

	std::cout << "Playback Complete, any key to continue: " << complete << std::endl;
	std::cin >> holder;
}


////////~~~~~~~~END>  main.cpp
