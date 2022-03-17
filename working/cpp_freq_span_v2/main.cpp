/*
    change the frequency center, moving 500 MHz to 1.5 GHz in 40 MHz spans
	the basic use functions are unpacked, operating on global variables
	this is the first step to producing modular objects (classes)
	notice that you could run 1 million loops with no seg-fault
	the past programs have failed because they try to do too much between aquisitions
	if you try to do too much, the computer can't keep the stream and seg-faults
*/

#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_API.h"

#define STEPZ 9
#define REPZ 9
#define BIG_WIDTH 1024
//#define DEBUG_CLI -888
#define getName(var) #var

const double INCREASE = 39e6;

char holder[BIG_WIDTH];

RSA_API::ReturnStatus g_rs;     // from original search_connect()
int g_numFound = 0;             // from original search_connect()
int* g_deviceIDs;               // from original search_connect()
const char** g_deviceSerial;    // from original search_connect()
const char** g_deviceType;      // from original search_connect()
char g_apiVersion[200];         // from original search_connect()

double g_cf;                             // from original spectrum_example()
double g_refLevel;                       // from original spectrum_example()
double g_span;                           // from original spectrum_example()
double g_rbw;                            // from original spectrum_example()
RSA_API::Spectrum_Settings g_specSet;    // from original spectrum_example()
double* g_freq = NULL;                   // from original spectrum_example()
float* g_traceData = NULL;               // from original spectrum_example()
int g_peakIndex = 0;                     // from original spectrum_example()

void error_check (void);
void config_spectrum (void);
void create_frequency_array (void);
void acquire_spectrum (void);
void peak_power_detector (void);
void spectrum_example (void);


int main
(
    int argc, 
    char** argv, 
    char** envp
)
{
#ifdef DEBUG_CLI
    printf("\n\t<<<  %s()  >>>\n", __func__);
#endif
	
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
	
	/*
	// original
	g_cf = 1e9;
	g_refLevel = -30;                
	g_span = 40e6;                    
	g_rbw = 300e3;
	*/
	// trying FM radio
	g_cf = 100e6;
	g_refLevel = -10;                
	g_span = 1e6;                    
	g_rbw = 1e3;

	for (int ii = 0; ii < STEPZ; ii++)
	{
		for (int jj = 0; jj < REPZ; jj++)
		{
			spectrum_example();
		}
		g_cf = g_cf + INCREASE;
	}  

	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();
	std::cout << "\nspectrum_example complete  ,  any key to continue:  ";
	std::cin >> holder;
	printf("\n\t<<<  %s()  >>>\n", __func__);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


/*
	called from   : search_connect()
	calls         : none
	API types     : none
	API values    : noError
	API functions : none
	notes         : exits the program if an error is detected
*/
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



/*
	called from   : spectrum_example()
	calls         : none
	API types     : none
	API values    : none
	API functions : SPECTRUM_SetEnable() 
				    CONFIG_SetCenterFreq() 
				    CONFIG_SetReferenceLevel()
				    SPECTRUM_SetDefault() 
				    SPECTRUM_GetSettings() x2
				    SPECTRUM_SetSettings()
	notes         : device is stopped, configurations occur
*/
void config_spectrum
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::CONFIG_Preset();
	RSA_API::SPECTRUM_SetEnable(true);
	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);
	
	RSA_API::SPECTRUM_SetDefault();
	RSA_API::SPECTRUM_GetSettings(&g_specSet); // apply defaults
	g_specSet.span = g_span;
	g_specSet.rbw = g_rbw;
	RSA_API::SPECTRUM_SetSettings(g_specSet); // apply user specification
	RSA_API::SPECTRUM_GetSettings(&g_specSet); 
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : none
	API values    : none
	API functions : none
	notes         : frequency is completley itterated
					dynamic double array is allocated
*/
void create_frequency_array
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	g_freq = NULL;
	int n = g_specSet.traceLength;
	g_freq = new double[n];  
	for (int ii = 0; ii < g_specSet.traceLength; ii++)
	{
		g_freq[ii] = g_specSet.actualStartFreq + g_specSet.actualFreqStepSize * ii;
	}
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : Spectrum_Settings
					SpectrumTraces
	API values    : none
	API functions : DEVICE_Run()
				    SPECTRUM_AquireTrace()
				    SPECTRUM_WaitForTraceReady()
					SPECTRUM_GetTrace()
					DEVICE_Stop()
	notes         : infinite loop until aquisition ready
					dynamic float array is allocated
*/
void acquire_spectrum
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	bool ready = false;
	int timeoutMsec = 0;

	RSA_API::SpectrumTraces trace = RSA_API::SpectrumTrace1;
	int maxTracePoints = g_specSet.traceLength;
	int outTracePoints = 0;
	int n = maxTracePoints;
	g_traceData = new float[n];    // deallocated in spectrum_example()
	
	RSA_API::DEVICE_Run();
	RSA_API::SPECTRUM_AcquireTrace();
	while (ready == false)
	{
		RSA_API::SPECTRUM_WaitForTraceReady(timeoutMsec, &ready);
	}
	RSA_API::SPECTRUM_GetTrace(trace, maxTracePoints, g_traceData, &outTracePoints);
	RSA_API::DEVICE_Stop();
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : none
	API values    : none
	API functions : none
	notes         : iterates aquired trace, finding index of highest power
					using the index, frequency bin can be infered
*/
void peak_power_detector
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	g_peakIndex = 0;
	for (int ii = 0; ii < g_specSet.traceLength; ii++)
	{
		if (g_traceData[ii] > g_traceData[g_peakIndex])
		{
			g_peakIndex = ii;
		}
	}
}


////~~~~


/*
	called from   : main()
	calls         : search_connect()
					config_spectrum()
					acquire_spectrum()
					create_frequency_array()
					peak_power_detector()
	API types     : none
	API values    : none
	API functions : none
	notes         : deallocates 2x
*/
void spectrum_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	config_spectrum();	
	acquire_spectrum();
	create_frequency_array();
	peak_power_detector();
	
	std::cout << "\nStart frequency: " << g_freq[0] << std::endl;
	std::cout << "Center frequency: " << g_freq[(g_specSet.traceLength - 1) / 2] << std::endl;
	std::cout << "Stop frequency: " << g_freq[g_specSet.traceLength - 1] << std::endl;
	std::cout << "Maximum value: " << g_traceData[g_peakIndex] << " dBm" << std::endl;
	std::cout << "Frequency of max amplitude: " << g_freq[g_peakIndex] << " Hz\n" << std::endl;

	delete[] g_freq;
	delete[] g_traceData;
	g_freq = NULL;
	g_traceData = NULL;
}


/////////~~~~~~~~END>  main.cpp
