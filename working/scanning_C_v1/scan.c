/*
    this is the attemp to scan a spectrum in 40 MHz spans
    the real-time adjustments will come later using:
    signal --> from CLI
        update start, stop, center
    also will add CLI argc, argv later

    the goal now is to ensure that the RSA-306B can be
    programmed to span and scan

    the functions will be updated latter

    $ cd scanning_C_v1
    $ make
    $ ./scan
*/


#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "RSA_API.h"

// adjust the RSA-306B settings here, capbable of 9 kHz to 6.2 GHz
double set_cf = 1e6;           // value for center frequency
double set_ref_level = -30;    // maximum expected signal power in dB [-130 : 30]
double set_span = 40e6;        // 40 MHz maximum frequency range for this device
double set_rbw = 300e3;        // resolution bandwidth in Hz [10 : 10M]

const int SHIFTZ = 5;             // shift the spectrum span this number of times
const int  REPZ = 3;             // collect this many traces per span
const double STEP_SIZE = 30e6;    // Hz to shift spectrum, with room for overlap

#define getName(var) #var

#define A_BUF 32
#define B_BUF 64
#define C_BUF 128
#define D_BUF 256
#define E_BUF 512
#define F_BUF 1024

const char MY_FILES[] = "data_scanned/";    // output file directory name

// global variables
char g_helper_str[D_BUF];           // general purpose string
char g_holder_str[F_BUF];           // big general purpose string
char g_dts_str[B_BUF];              // string for date-time-stamp
char g_time_split_str[A_BUF];       // string for time-split in micro seconds
char g_time_duration_str[A_BUF];    // string for total program running time in micro seconds
FILE* g_fptr = NULL;                // file pointer for spectrum data
clock_t g_cpu_clk_split;            // reference to start of the time split
clock_t g_cpu_clk_duration;         // starting time of the program in micro seconds

// helpers
void get_dts (void);            // fills g_dts_str with current date-time-stamp
void recording_start (void);    // opens and prepares a file for data aquisition
void recording_stop (void);     // logs and closes a file after data aquisition
void get_times (void);          // fills g_run_time with current running time less start time

// applications of the API, enters form get_spectrum()
void get_spectrum (double cf, double refLevel, double span, double rbw);
void set_up_rsa(void);


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    g_cpu_clk_duration = clock();    // program time starts
    set_up_rsa();                    // set up the RSA-306B, connections and error check

    for (int ii = 0; ii < SHIFTZ; ii++)
    {
        set_cf = set_cf + ii * STEP_SIZE;

        for (int jj = 0; jj < REPZ; jj++)
        {
            get_spectrum (set_cf, set_ref_level, set_span, set_rbw);
        }
    }
    
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


void get_dts
(
    void
)
{   
    if (g_dts_str == NULL) 
    {
        printf("<%d> %s / %s()  ,  %s not allocated\n", 
            __LINE__, __FILE__, __func__, getName(g_dts_str));
        exit(0);
    }
    memset(g_dts_str, '\0', B_BUF);

    time_t currentTime;
    struct tm * ptr = NULL;
    currentTime = time(&currentTime);
    ptr = gmtime(&currentTime);          

    if (currentTime != -1 && ptr != NULL)
    {    
        strftime(g_dts_str, B_BUF,
            "_%Y_%m_%d_%A_%H_%M_%S_%Z", ptr);
    }
    else
    {
        printf("<%d> %s / %s()  ,  failed get DTS string\n", 
            __LINE__, __FILE__, __func__);
        exit(0);
    }
}


////~~~~


void recording_start
(
    void
)
{
    g_cpu_clk_split = clock();    // time split begins
    get_dts();
    get_times();
    snprintf(g_helper_str, D_BUF, "%s%s_%s_.txt", 
        MY_FILES, g_dts_str, g_time_duration_str);
    g_fptr = fopen(g_helper_str, "w");
    if (g_fptr == NULL) 
    {
        printf("<%d> %s / %s()  ,  failed open a file\n", 
            __LINE__, __FILE__, __func__);
        exit(0);
    }
    snprintf(g_holder_str, F_BUF, "\t\t~ ~ ~ LOG OPEN ~ ~ ~%s\n\n", g_helper_str);
    fputs(g_holder_str, g_fptr);
}


////~~~~


void recording_stop
(
    void
)
{
    get_dts();
    get_times();
    snprintf(g_helper_str, D_BUF, 
        "\n\n\t\t ~ ~ ~ LOG CLOSED ~ ~ ~ %s_us_%s\n\n", 
        g_dts_str, g_time_duration_str);
    fputs(g_helper_str, g_fptr);
    snprintf(g_helper_str, D_BUF, "time split:  %s  us\n",
        g_time_split_str);
    fputs(g_helper_str, g_fptr);
    fclose(g_fptr);
    g_fptr = NULL;
    printf("data aquisition complete  ,  time-split:  %s  us\n", 
        g_time_split_str);
}


////~~~~


void get_times
(
    void
)
{
    clock_t cpu_clk_now = clock();                            // get current time
    double temp_time = 0;
    temp_time = ((double)cpu_clk_now - (double)g_cpu_clk_split) 
        / CLOCKS_PER_SEC;
    temp_time = temp_time * 1000000;                           // convert seconds to micro seconds
    int micro_seconds = (int) temp_time;                       // truncate
    snprintf(g_time_split_str, A_BUF, "%d", micro_seconds);    // split recorded

    temp_time = ((double)cpu_clk_now - (double)g_cpu_clk_duration)
        / CLOCKS_PER_SEC;
    temp_time = temp_time * 1000000;                              // convert seconds to micro seconds
    micro_seconds = (int) temp_time;                              // truncate
    snprintf(g_time_duration_str, A_BUF, "%d", micro_seconds);    // duration recorded
}


////~~~~


void set_up_rsa
(
    void
)
{
    int numFound;
	int* device_IDs;
	const char** deviceSerial;
	const char** deviceType;
	char apiVersion[D_BUF];
	ReturnStatus rs;

	rs = DEVICE_GetAPIVersion(apiVersion);
    printf("\nAPI Version:  %s\n", apiVersion);
	rs = DEVICE_SearchInt(&numFound, &device_IDs, &deviceSerial, &deviceType);
	if (numFound != 1)
	{
        printf("check hardware...\n");
		exit(0);
	}	
    printf("Device ID:  %d  ,  ", device_IDs[0]);
	printf("Serial Number:  %s  ,  ", deviceSerial[0]);
	printf("Device Type:  %s\n", deviceType[0]);
    
    rs = DEVICE_Connect(device_IDs[0]);
    if (rs != noError) 
	{
        printf("\n\tDevice error=  %d\n", rs);
		exit(0);
	}
}


////~~~~


void get_spectrum
(
	double cf,
    double refLevel,
    double span,
    double rbw
)
{
	Spectrum_Settings specSet;
	double* freq = NULL;
	float* traceData = NULL;
	//int peakIndex = 0;
    bool ready = false;
	int timeoutMsec = 0;
	
	CONFIG_Preset();  // device uses free-run trigger
	CONFIG_SetCenterFreq(cf); // device sets center frequency in Hz
	CONFIG_SetReferenceLevel(refLevel); // device sets highest reference level in dB
	
    SPECTRUM_SetEnable(true); // enables hardware for measurement
	CONFIG_SetCenterFreq(cf);
	CONFIG_SetReferenceLevel(refLevel);
	
	SPECTRUM_SetDefault();
	SPECTRUM_GetSettings(&specSet);
	specSet.span = span;
	specSet.rbw = rbw;
	SPECTRUM_SetSettings(specSet);
	SPECTRUM_GetSettings(&specSet);
    
recording_start();
    // aquire spectrum
	SpectrumTraces trace = SpectrumTrace1;
	int maxTracePoints = specSet.traceLength;
	int outTracePoints = 0;
	int n = maxTracePoints;
    traceData = (float*)malloc(n*sizeof(float));
	
	DEVICE_Run();
	SPECTRUM_AcquireTrace();
	while (ready == false)
	{
		SPECTRUM_WaitForTraceReady(timeoutMsec, &ready);
	}
	SPECTRUM_GetTrace(trace, maxTracePoints, traceData, &outTracePoints);
	Spectrum_TraceInfo traceInfo;
	SPECTRUM_GetTraceInfo(&traceInfo);
	DEVICE_Stop();

    // make an array
    snprintf(g_helper_str, D_BUF, "start:  %lf  ,  center:  %lf  ,  stop:  %lf\n",
        cf - span/2, cf, cf + span/2);
    fputs(g_helper_str, g_fptr);
    int nn = specSet.traceLength;
	freq = (double*)malloc(nn*sizeof(double));
	for (int ii = 0; ii < nn; ii++)
	{
		freq[ii] = specSet.actualStartFreq + specSet.actualFreqStepSize * ii;
        snprintf(g_helper_str, D_BUF, "%f\n", freq[ii]);
        fputs(g_helper_str, g_fptr);
	}
recording_stop();
   
	free(freq);
	free(traceData);
	freq = NULL;
	traceData = NULL;
    printf("\n\tdisconnecting....\n");
	DEVICE_Disconnect();
}


/////////~~~~~~~~END> scan.c
