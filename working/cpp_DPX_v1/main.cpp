/*
    DPX is very heavy
	may not be the best data to get, but it is worth looking at
*/

#include <iostream>
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

double g_cf = 2.4453e9;           // from original dpx_example()
double g_refLevel = -30;          // from original dpx_example()
double g_span = 40e6;             // from original dpx_example()
double g_rbw = 300e3;             // from original dpx_example()
RSA_API::DPX_FrameBuffer g_fb;    // from original dpx_example()

void error_check (void);
void dpx_example (void);
void config_dpx (void);
void acquire_dpx (void);


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

	dpx_example();

    std::cout << "\nDPX example complete  ,  any key to continue:  ";
	std::cin >> holder;
    std::cout << "Disconnecting..." << std::endl;
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


void dpx_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif
	config_dpx();
	acquire_dpx();
	std::cout << "\nFFTs in frame: " << g_fb.fftCount << std::endl;
	std::cout << "DPX FrameBuffers acquired: " << g_fb.frameCount << std::endl;
	std::cout << "DPX Bitmap is "<< g_fb.spectrumBitmapWidth << 
		" x " << g_fb.spectrumBitmapHeight << " pixels." << std::endl;
	std::cout << "DPX Spectrogram is " << g_fb.sogramBitmapWidth <<
		" x " << g_fb.sogramBitmapHeight << " pixels." << std::endl;
	std::cout << "Valid traces in spectrogram: " << g_fb.sogramBitmapNumValidLines << std::endl;
}


////~~~~


void config_dpx
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double yTop = g_refLevel;
	double yBottom = yTop - 100;
	double timeResolution = 1e-3;
	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);

	RSA_API::DPX_SetEnable(true);
	RSA_API::DPX_SetParameters(g_span, g_rbw, 801, 1, RSA_API::VerticalUnit_dBm, yTop, yBottom, false, 1.0, false);
	RSA_API::DPX_SetSogramParameters(timeResolution, timeResolution, yTop, yBottom);
	RSA_API::DPX_Configure(true, true);
	RSA_API::DPX_SetSpectrumTraceType(0, RSA_API::TraceTypeMaxHold);
	RSA_API::DPX_SetSpectrumTraceType(1, RSA_API::TraceTypeAverage);
	RSA_API::DPX_SetSpectrumTraceType(2, RSA_API::TraceTypeMinHold);
}


////~~~~


void acquire_dpx
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	bool frameAvailable = false;
	bool ready = false;

	RSA_API::DEVICE_Run();
	while (frameAvailable == false)
	{
		RSA_API::DPX_IsFrameBufferAvailable(&frameAvailable);
	}
	while (ready == false)
	{
		RSA_API::DPX_WaitForDataReady(100, &ready);
	}
	RSA_API::DPX_GetFrameBuffer(&g_fb);
	RSA_API::DPX_FinishFrameBuffer();
	RSA_API::DEVICE_Stop();
}


////////~~~~~~~~END>  main.cpp
