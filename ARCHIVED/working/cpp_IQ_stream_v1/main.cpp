/*
    IQ stream may be faster
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_API.h"

#define BIG_WIDTH 1024
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

double g_cf = 2.4453e9;                             // from original iq_stream_example()
double g_refLevel = -30;	                        // from original iq_stream_example()
double g_bw = 40e6;                                 // from original iq_stream_example()
RSA_API::IQSOUTDEST g_dest;                         // from original iq_stream_example()
int g_suffixCtl = -2;                               // from original iq_stream_example()
int g_durationMsec = 2000;                          // from original iq_stream_example()
int g_waitTime = 10;                                // from original iq_stream_example()
char g_fileName[BIG_WIDTH] = "./test_IQ_stream";    // from original iq_stream_example()
RSA_API::IQSTRMFILEINFO g_iqStreamInfo;             // from original iq_stream_example()

double g_bwActual = 0;      // from original config_iq_stream()
double g_sampleRate = 0;    // from original config_iq_stream()

void error_check (void);
void iq_stream_example (void);
void config_iq_stream (void);
void iqstream_status_parser (void);


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    // search_connect()
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

	iq_stream_example();

    std::cout << "\nIQ stream example complete  ,  any key to continue:  ";
	std::cin >> holder;
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


void iq_stream_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	g_dest = RSA_API::IQSOD_FILE_SIQ;
	bool complete = false;
	bool writing = false;

	config_iq_stream();
	RSA_API::DEVICE_Run();
	RSA_API::IQSTREAM_Start();
	while (complete == false)
	{
		sleep(g_waitTime); // unistd has this in seconds, that is a lot of data
		RSA_API::IQSTREAM_GetDiskFileWriteStatus(&complete, &writing);
	}
	RSA_API::IQSTREAM_Stop();
	std::cout << "Streaming finished." << std::endl;
	RSA_API::IQSTREAM_GetDiskFileInfo(&g_iqStreamInfo);
	iqstream_status_parser();
	RSA_API::DEVICE_Stop();
}


////~~~~


void config_iq_stream
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);

	RSA_API::IQSTREAM_SetAcqBandwidth(g_bw);
	RSA_API::IQSTREAM_SetOutputConfiguration(g_dest, RSA_API::IQSODT_INT16);
	RSA_API::IQSTREAM_SetDiskFilenameBase(g_fileName);
	RSA_API::IQSTREAM_SetDiskFilenameSuffix(g_suffixCtl);
	RSA_API::IQSTREAM_SetDiskFileLength(g_durationMsec);
	RSA_API::IQSTREAM_GetAcqParameters(&g_bwActual, &g_sampleRate);
}


////~~~~


void iqstream_status_parser
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	if (g_iqStreamInfo.acqStatus == 0)
		printf("No errors in IQ streaming detected.\n");
	else
	{
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_OVERRANGE)
		{
			std::cout << "Input overrange." << std::endl;
		}
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY)
		{
			std::cout << "Streaming discontinuity, loss of data has occurred." << std::endl;
		}
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT)
		{
			std::cout << "Input buffer > 75% full." << std::endl;
		}
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT)
		{
			std::cout << "Input buffer overflow, IQStream processing too slow, data loss has occurred." << std::endl;
		}
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT)
		{
			std::cout << "Output buffer > 75% full." << std::endl;
		}
		if (g_iqStreamInfo.acqStatus & RSA_API::IQSTRM_STATUS_OBUFFOVFLOW)
		{
			std::cout << "Output buffer overflow, file writing too slow, data loss has occurred." << std::endl;
		}
	}
}


////////~~~~~~~~END>  main.cpp
