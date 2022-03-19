/*
    isolating the block IQ capabilties
    all the API functions have a ReturnStatus type, probably should error check more
    gutting the functions to make a class, g_vars are temporary
*/

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

double g_cf = 1e9;                   // from original block_iq_example()
double g_refLevel = 0;               // from original block_iq_example()
double g_iqBw = 40e6;                // from original block_iq_example()
int g_recordLength = 1000;           // from original block_iq_example()
double* g_time = NULL;               // from original block_iq_example()
RSA_API::Cplx32* g_iqData = NULL;    // from original block_iq_example()

double g_iqSampleRate;    // from original config_block_iq()

void block_iq_example (void);
void error_check (void);
void config_block_iq (void);
void acquire_block_iq (void);


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

    block_iq_example();

    std::cout << "\nblock_iq_example complete  ,  any key to continue:  ";
	std::cin >> holder;
    std::cout << "Disconnecting...check the output file that was made" << std::endl;
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


void block_iq_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	config_block_iq();
	acquire_block_iq(); 

    g_fptr = fopen(my_data, "w");
    snprintf(holder, BIG_WIDTH-1, "center frequency:  %lf  Hz\n", g_cf);
    fputs(holder, g_fptr);
    snprintf(holder, BIG_WIDTH-1, "reference level:  %lf  dB\n", g_refLevel);
    fputs(holder, g_fptr);
    snprintf(holder, BIG_WIDTH-1, "IQ band width:  %lf  Hz\n", g_iqBw);
    fputs(holder, g_fptr);
    snprintf(holder, BIG_WIDTH-1, "Block IQ data >>\n\n");
    fputs(holder, g_fptr);
    snprintf(holder, BIG_WIDTH-1, "    time         |        i          |           q  \n");
    fputs(holder, g_fptr);
    snprintf(holder, BIG_WIDTH-1, "-------------------------------------------------------\n");
    fputs(holder, g_fptr);

    for (int ii = 0; ii < g_recordLength; ii++)
    {
        snprintf(holder, BIG_WIDTH-1, "% 0.12lf  |  % 0.12f  |  % 0.12f\n",
            g_time[ii], g_iqData[ii].i, g_iqData[ii].q);
        fputs(holder, g_fptr);
    }

    fclose(g_fptr);
    g_fptr = NULL;
	delete[] g_time;
	delete[] g_iqData;
	g_time = NULL;
	g_iqData = NULL;
}


////~~~~


void config_block_iq
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	g_time = new double[g_recordLength];

	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);

	RSA_API::IQBLK_SetIQBandwidth(g_iqBw);
	RSA_API::IQBLK_SetIQRecordLength(g_recordLength);
	g_rs = RSA_API::IQBLK_GetIQSampleRate(&g_iqSampleRate);
	error_check();

	double step = g_recordLength / g_iqSampleRate / (g_recordLength-1);
	for (int ii = 0; ii < g_recordLength; ii++)
	{
		g_time[ii] = ii * step;
	}
}


////~~~~


void acquire_block_iq
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	g_iqData = new RSA_API::Cplx32[g_recordLength]; 
	bool ready = false;
	int timeoutMsec = 100;
	int outLength = 0;

	RSA_API::DEVICE_Run();
	RSA_API::IQBLK_AcquireIQData();
	while (ready == false)
	{
		RSA_API::IQBLK_WaitForIQDataReady(timeoutMsec, &ready);
	}
	RSA_API::IQBLK_GetIQDataCplx(g_iqData, &outLength, g_recordLength);
	RSA_API::DEVICE_Stop();
}


////////~~~~~~~~END>  main.cpp
