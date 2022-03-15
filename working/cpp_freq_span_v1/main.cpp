/*
    change the frequency center, moving 500 MHz to 1.5 GHz in 40 MHz spans
*/

#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_API.h"

#define BIG_WIDTH 1024
#define DEBUG_CLI -888
#define getName(var) #var

char holder[BIG_WIDTH];

void error_check (RSA_API::ReturnStatus rs);
void print_device_info (int* deviceIDs, int numFound, const char** deviceSerial, const char** deviceType);
int search_connect (void);
RSA_API::Spectrum_Settings config_spectrum (double cf, double refLevel, double span, double rbw);
double* create_frequency_array (RSA_API::Spectrum_Settings specSet);
float* acquire_spectrum (RSA_API::Spectrum_Settings specSet);
int peak_power_detector (float* traceData, double* freq, RSA_API::Spectrum_Settings specSet);
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

	spectrum_example();  

#ifdef DEBUG_CLI
    printf("\n\t<<<  %s()  >>>\n", __func__);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
#endif

    return EXIT_SUCCESS;
}


////~~~~


/*
	called from   : search_connect()
	calls         : none
	API types     : ReturnStatus
	API values    : noError
	API functions : none
	notes         : ReturnStatus instance as input parameter
	                exits the program if an error is detected
*/
void error_check
(
	RSA_API::ReturnStatus rs
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	// noError = 0 is the only signal that indicates hardware is satisfactory
	// any other error code is a problem, and modifications are needed before proceeding
	if (rs != RSA_API::noError) 
	{
		std::cout << "\nError: " << rs << std::endl;
		std::exit(0);
	}
}


////~~~~


/*
	called from   : search_connect()
	calls         : none
	API types     : none
	API values    : none
	API functions : none
	notes         : evaluates values input from DEVICE_SearchInt()
	                data is error-checked before calling
*/
void print_device_info
(
	int* deviceIDs, 
	int numFound, 
	const char** deviceSerial, 
	const char** deviceType
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	std::cout << "Number of devices found: " << numFound << std::endl;
	for (int i = 0; i < numFound; i++)
	{
		std::cout << "Device ID: " << i;
		std::cout << ", Serial Number: " << deviceSerial[i];
		std::cout << ", Device Type: " << deviceType[i] << std::endl;
	}
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : error_check() 
	                print_device_info()
	API types     : ReturnStatus
	API values    : none
	API functions : DEVICE_GetAPIVersion() 
	                DEVICE_SearchInt() 
				    DEVICE_Connect()
	notes         : used as gateway for connecting
	                retunrs 0 if successful
*/
int search_connect
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	int numFound = 0;
	int* deviceIDs;
	const char** deviceSerial;
	const char** deviceType;
	char apiVersion[200];
	RSA_API::ReturnStatus rs;

	rs = RSA_API::DEVICE_GetAPIVersion(apiVersion);
	std::cout << "API Version: " << apiVersion << std::endl;
	rs = RSA_API::DEVICE_SearchInt(&numFound, &deviceIDs, &deviceSerial, &deviceType);
	if (numFound < 1)
	{
		std::cout << "No devices found, exiting script." << std::endl;
		std::exit(0);
	}
	else if (numFound == 1)
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		rs = RSA_API::DEVICE_Connect(deviceIDs[0]);
		error_check(rs);
	}
	else
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		int dev;
		std::cout << "Select device between 0 and " << (numFound - 1) << "\n> ";
		std::cin >> dev;
		rs = RSA_API::DEVICE_Connect(deviceIDs[dev]);
		error_check(rs);
		std::cout << "Connected to device " << dev;
		std::cout << ", Serial Number: " << deviceSerial[dev];
		std::cout << ", Device Type: " << deviceType[dev] << std::endl;
	}
	return 0;
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : Spectrum_Settings
	API values    : none
	API functions : SPECTRUM_SetEnable() 
				    CONFIG_SetCenterFreq() 
				    CONFIG_SetReferenceLevel()
				    SPECTRUM_SetDefault() 
				    SPECTRUM_GetSettings() x2
				    SPECTRUM_SetSettings()
	notes         : check scope of Spectrum_Settings instance returned ?
*/
RSA_API::Spectrum_Settings config_spectrum
(
	double cf, 
	double refLevel, 
	double span, 
	double rbw
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::SPECTRUM_SetEnable(true);
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);
	
	RSA_API::SPECTRUM_SetDefault();
	RSA_API::Spectrum_Settings specSet;      // object
	RSA_API::SPECTRUM_GetSettings(&specSet); // apply defaults
	specSet.span = span;
	specSet.rbw = rbw;
	RSA_API::SPECTRUM_SetSettings(specSet); // apply user specification
	RSA_API::SPECTRUM_GetSettings(&specSet); 
	
	return specSet; // see if this instance persists after leaving call stack
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : Spectrum_Settings
	API values    : none
	API functions : none
	notes         : frequency is completley itterated
					Spectrum_Settings isntance as input
					dynamic float array made in here
*/
double* create_frequency_array
(
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double* freq = NULL;
	int n = specSet.traceLength;
	freq = new double[n];    // deallocated in spectrum_example()
	for (int i=0; i < specSet.traceLength; i++)
	{
		freq[i] = specSet.actualStartFreq + specSet.actualFreqStepSize*i;
	}

	return freq;
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
					SPECTRUM_GetTraceInfo()
					DEVICE_Stop()
	notes         : infinite loop until aquisition ready
					dynamic float array is allocated
*/
float* acquire_spectrum
(
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	bool ready = false;
	int timeoutMsec = 0;

	RSA_API::SpectrumTraces trace = RSA_API::SpectrumTrace1;
	int maxTracePoints = specSet.traceLength;
	int outTracePoints = 0;
	float* traceData = NULL;
	int n = maxTracePoints;
	traceData = new float[n];    // deallocated in spectrum_example()
	
	RSA_API::DEVICE_Run();
	RSA_API::SPECTRUM_AcquireTrace();
	while (ready == false)
	{
		RSA_API::SPECTRUM_WaitForTraceReady(timeoutMsec, &ready);
	}
	RSA_API::SPECTRUM_GetTrace(trace, maxTracePoints, traceData, &outTracePoints);
	RSA_API::Spectrum_TraceInfo traceInfo;
	RSA_API::SPECTRUM_GetTraceInfo(&traceInfo);
	RSA_API::DEVICE_Stop();

	std::cout << "Trace Data Status: " << traceInfo.acqDataStatus << std::endl;

	return traceData;
}


////~~~~


/*
	called from   : spectrum_example()
	calls         : none
	API types     : Spectrum_Settings
	API values    : none
	API functions : none
	notes         : iterates aquired trace to find peak frequency index
	                not sure why it needs the double* freq
*/
int peak_power_detector
(
	float* traceData,
	double* freq, 
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	int peakIndex = 0;
	for (int i = 0; i < specSet.traceLength; i++)
	{
		if (traceData[i] > traceData[peakIndex])
		{
			peakIndex = i;
		}
	}

	return peakIndex;
}


////~~~~


/*
	called from   : main()
	calls         : search_connect()
					config_spectrum()
					acquire_spectrum()
					create_frequency_array()
					peak_power_detector()
	API types     : Spectrum_Settings
	API values    : none
	API functions : CONFIG_Preset()
					CONFIG_SetCenterFreq()
					CONFIG_SetReferenceLevel()
					DEVICE_Disconnect()
	notes         : deallocates 2x new calls for float arrays
*/
void spectrum_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double cf = 1e9;
	double refLevel = -30;
	double span = 40e6;
	double rbw = 300e3;
	RSA_API::Spectrum_Settings specSet;
	double* freq = NULL;
	float* traceData = NULL;
	int peakIndex = 0;

	search_connect();
	RSA_API::CONFIG_Preset();
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	specSet = config_spectrum(cf, refLevel, span, rbw);	
for (int repz = 0; repz < 5000; repz++)
{
	traceData = acquire_spectrum(specSet);
	freq = create_frequency_array(specSet);
	peakIndex = peak_power_detector(traceData, freq, specSet);
	
	std::cout << "Start frequency: " << freq[0] << std::endl;
	std::cout << "Center frequency: " << freq[(specSet.traceLength - 1) / 2] << std::endl;
	std::cout << "Stop frequency: " << freq[specSet.traceLength - 1] << std::endl;
	std::cout << "Maximum value: " << traceData[peakIndex] << " dBm" << std::endl;
	std::cout << "Frequency of max amplitude: " << freq[peakIndex] << " Hz" << std::endl;

	delete[] freq;
	delete[] traceData;
	freq = NULL;
	traceData = NULL;
}
	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();

	std::cout << "\nspectrum_example complete  ,  any key to continue:  ";
	std::cin >> holder;
}


/////////~~~~~~~~END>  main.cpp
