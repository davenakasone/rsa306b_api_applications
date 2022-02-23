/*
    gets a spectrum
    focus here is getting the complete reading
    writes data to a file

    kept to single file for unit testing, turn on macros as needed

    $ cd read_write_C
    $ make
    $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
    $ ./rwC

    TODO:
        worker thread with a mutex or semaphore
        error handling (program will seg fault if the reading gets behind the stream)
        real-time adjustments
        select data to get (there is a lot)
*/


#include <errno.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "RSA_API.h"

#define REPZ 500 // don't make too big, computer can't keep up with bit stream ?
#define SPEC_PATH "logs_spectrum/"
#define BIG_BUF 1024
#define STATUS_GOOD 1776
#define STATUS_BAD 1917

//#define DEBUG_ENABLE -9999 // turn these off when operating, they consume a lot of resources
#define DEBUG_CLI 1111
#define DEBUG_LOG 2222
#define DEBUG_RET 3333
#define DEBUG_ERRNO 4444

#ifdef DEBUG_ENABLE
    #define DB_BEGIN 123
    #define DB_REPORT 456
    #define DB_END 789
    #define DB_CLEAR "no db notes provided"

    char db_notes[BIG_BUF];
    int db_errno_int;
    char db_errno_str[BIG_BUF];

    #ifdef DEBUG_LOG
        #define DB_PATH "logs_debug/"
        char db_file_name[BIG_BUF];
        FILE* db_fp = NULL;
    #endif

    void debug_handler(int db_request);
#endif

#define getName(var) #var

int g_ret;
char g_helper_str[BIG_BUF];
char g_holder_str[BIG_BUF];
char g_dts[BIG_BUF];
FILE* g_fptr = NULL;
clock_t g_cpu_clk;

void recording_stop(void); //  no gvar: FILE* recording_stop(FILE* fp);
void recording_start(void); // no gvar: FILE* recording_stop(FILE* fp);

int get_dts (void);
void spectrum_example (void);
int search_connect (void);
void print_device_info (int* deviceIDs, int numFound, const char** deviceSerial, const char** deviceType);
void err_check (ReturnStatus rs);
Spectrum_Settings config_spectrum (double cf, double refLevel, double span, double rbw);
float* acquire_spectrum (Spectrum_Settings specSet);
double* create_frequency_array (Spectrum_Settings specSet);
int peak_power_detector (float* traceData, double* freq, Spectrum_Settings specSet);


int main
(
    void
)
{
    #ifdef DEBUG_ENABLE 
        debug_handler(DB_BEGIN);
    #endif

    #ifdef DEBUG_ENABLE
        db_errno_int = errno; 
        snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
        snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
            __LINE__, __FILE__, __func__, DB_CLEAR);
        debug_handler(DB_REPORT);
    #endif

    get_dts();
    snprintf(g_helper_str, BIG_BUF, "%s%s.txt", SPEC_PATH, g_dts);
    g_fptr = fopen(g_helper_str, "w");
    if (g_fptr == NULL) {return EXIT_FAILURE;}
    snprintf(g_holder_str, BIG_BUF, "\t\t~ ~ ~ LOG OPEN ~ ~ ~%s\n\n", g_helper_str);
    fputs(g_holder_str, g_fptr);

    spectrum_example();

    get_dts();
    snprintf(g_helper_str, BIG_BUF, "\n\n\t\t ~ ~ ~ LOG CLOSED ~ ~ ~ %s\n\n", g_dts);
    fputs(g_helper_str, g_fptr);
    fclose(g_fptr);
    g_fptr = NULL;
    #ifdef DEBUG_ENABLE 
        debug_handler(DB_END);
    #endif
    return EXIT_SUCCESS;
}


////~~~~


int get_dts
(
    void
)
{   
    if (g_dts == NULL) {return STATUS_BAD;}
    memset(g_dts, '\0', BIG_BUF);

    time_t currentTime;
    struct tm * ptr = NULL;
    currentTime = time(&currentTime);
    ptr = gmtime(&currentTime);          

    if (currentTime != -1 && ptr != NULL)
    {    
        strftime(g_dts, BIG_BUF,
            "_%Y_%m_%d_%A_%H_%M_%S_%Z", ptr);
        return STATUS_GOOD;
    }
    else
    {
        return STATUS_BAD;
    }
}


////~~~~


#ifdef DEBUG_ENABLE
void debug_handler
(
    int db_request
)
{
    
    if (db_request == DB_BEGIN)
    {
        #ifdef DEBUG_LOG
            get_dts();
            snprintf(db_file_name, BIG_BUF, "%s%s.txt", DB_PATH, g_dts);
            db_fp = fopen(db_file_name, "w");
            snprintf(g_helper_str, BIG_BUF, "\t\t ~ ~ ~ DEBUG Begin  >>>  %s\n\n", db_file_name);
        #endif
        return;
    } 
    
    if (db_request == DB_REPORT)
    {
        get_dts();
        #ifdef DEBUG_CLI
            printf("%s  ,  %s\n", db_notes, g_dts);
            #ifdef DEBUG_ERRNO
                printf("\terrno=  %d  ,  %s\n", 
                    db_errno_int, db_errno_str);
            #endif
            #ifdef DEBUG_RET
                printf("\treturned:  %d\n", g_ret);
            #endif
            printf("\n");
        #endif
        #ifdef DEBUG_LOG
            snprintf(g_helper_str, BIG_BUF, "%s  ,  %s\n", db_notes, g_dts);
            fputs(g_helper_str, db_fp);
            #ifdef DEBUG_ERRNO
                snprintf(g_helper_str, BIG_BUF, "\terrno=  %d  ,  %s\n", 
                    db_errno_int, db_errno_str);
                fputs(g_helper_str, db_fp);
            #endif
            #ifdef DEBUG_RET
                snprintf(g_helper_str, BIG_BUF, "\treturned:  %d\n", g_ret);
                fputs(g_helper_str, db_fp);
            #endif
            snprintf(g_helper_str, BIG_BUF, "\n");
            fputs(g_helper_str, db_fp);
        #endif
        return;
    } 
    
    if (db_request == DB_END)
    {
        get_dts();
        #ifdef __clang_major__
            sbprintf(g_helper_str, BIG_BUF, "\ncompiler:  clang  ,  v %d.%d\n",
                __clang_major__,__clang_minor__);
        #endif
        #ifdef __GNUC__
            snprintf(g_helper_str, BIG_BUF, "compiler:  gcc  ,  v %d.%d",
                __GNUC__, __GNUC_MINOR__);
        #endif
        snprintf(g_holder_str, BIG_BUF, "\n\n\t\t ~ ~ ~ PROGAM COMPLETE ~ ~ ~\n\n\t\t\t%s  ,  %s\n\n", 
            g_helper_str, g_dts);
        #ifdef DEBUG_CLI
            printf("%s", g_holder_str);
        #endif
        #ifdef DEBUG_LOG
            fputs(g_holder_str, db_fp);
            snprintf(db_notes, BIG_BUF, " ~ ~ ~ LOG CLOSED ~ ~ ~\n\n");
            fputs(db_notes, db_fp);
            fclose(db_fp);
            db_fp = NULL;
        #endif
        return;
    } 
    
    printf("\n\t[%d]%s  %s()  ,  something is wrong\n", 
        __LINE__, __FILE__,  __func__);
}
#endif


////~~~~


void spectrum_example
(
	void
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	double cf = 1e9;
	double refLevel = -30;
	double span = 40e6;
	double rbw = 300e3;
	Spectrum_Settings specSet;
	double* freq = NULL;
	float* traceData = NULL;
	int peakIndex = 0;

	search_connect();
	CONFIG_Preset();
	CONFIG_SetCenterFreq(cf);
	CONFIG_SetReferenceLevel(refLevel);
	specSet = config_spectrum(cf, refLevel, span, rbw);

    for (int ii = 0; ii < REPZ; ii++)
    {
        traceData = acquire_spectrum(specSet);
	    freq = create_frequency_array(specSet);
	    peakIndex = peak_power_detector(traceData, freq, specSet);
        snprintf(g_helper_str, BIG_BUF, "f_start[ %lf ]  f_center[ %lf ]  f_stop[ %lf ]\n",
            freq[ii], freq[specSet.traceLength-1]/2, freq[specSet.traceLength-1]);
        snprintf(g_holder_str, BIG_BUF, "max_amp:  %f  dBm  ,  f_max_amp:  %lf  Hz\n\n",
            traceData[peakIndex], freq[peakIndex]);
        fputs(g_helper_str, g_fptr);
        fputs(g_holder_str, g_fptr);
    }
    /*
	traceData = acquire_spectrum(specSet);
	freq = create_frequency_array(specSet);
	peakIndex = peak_power_detector(traceData, freq, specSet);
	
    printf("Start frequency:  %lf\n", freq[0]);
	printf("Center frequency:  %lf\n", freq[(specSet.traceLength - 1) / 2]);
	printf("Stop frequency:  %lf\n", freq[specSet.traceLength - 1]);
    printf("Max amplitude:  %f  dBm\n", traceData[peakIndex]);
    printf("Frequency at max amplitude:  %lf  Hz\n", freq[peakIndex]);
    */

    printf("\n\tdisconnecting....\n");
	DEVICE_Disconnect();
	free(freq);
	free(traceData);
	freq = NULL;
	traceData = NULL;

    printf("\nspectrum_example complete  ,  any key to continue:  ");
	g_helper_str[0] = getchar();
}


////~~~~


int search_connect
(
	void
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	int numFound = 0;
	int* deviceIDs;
	const char** deviceSerial;
	const char** deviceType;
	char apiVersion[200];
	ReturnStatus rs;

	rs = DEVICE_GetAPIVersion(apiVersion);
    printf("API Version:  %s\n", apiVersion);
	rs = DEVICE_SearchInt(&numFound, &deviceIDs, &deviceSerial, &deviceType);
	if (numFound < 1)
	{
        printf("No devices found, exiting script...\n");
		exit(0);
	}
	else if (numFound == 1)
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		rs = DEVICE_Connect(deviceIDs[0]);
		err_check(rs);
	}
	else
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		int dev;
        printf("Select device between 0 and %d\n", numFound-1);
		scanf("%d", &dev);
		rs = DEVICE_Connect(deviceIDs[dev]);
		err_check(rs);
        printf("Connected to device#  %d  ,  Serial#  %s  ,  Type#  %s\n", 
            dev, deviceSerial[dev], deviceType[dev]);
	}
	return 0;
}


////~~~~


void print_device_info
(
	int* deviceIDs, 
	int numFound, 
	const char** deviceSerial, 
	const char** deviceType
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	printf("Number of devices found:  %d\n", numFound);
	for (int ii = 0; ii < numFound; ii++)
	{
		printf("Device ID:  %d  ,  ", ii);
		printf("Serial Number:  %s  ,  ", deviceSerial[ii]);
		printf("Device Type:  %s\n", deviceType[ii]);
	}
}


////~~~~


void err_check
(
	ReturnStatus rs
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	// noError = 0 is the only signal that indicates hardware is satisfactory
	// any other error code is a problem, and modifications are needed before proceeding
	if (rs != noError) 
	{
        printf("\n\tDevice error=  %d\n", rs);
		exit(0);
	}
}


////~~~~


Spectrum_Settings config_spectrum
(
	double cf, 
	double refLevel, 
	double span, 
	double rbw
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	SPECTRUM_SetEnable(true);
	CONFIG_SetCenterFreq(cf);
	CONFIG_SetReferenceLevel(refLevel);
	
	SPECTRUM_SetDefault();
	Spectrum_Settings specSet;
	SPECTRUM_GetSettings(&specSet);
	specSet.span = span;
	specSet.rbw = rbw;
	SPECTRUM_SetSettings(specSet);
	SPECTRUM_GetSettings(&specSet);
	
	return specSet;
}


////~~~~


float* acquire_spectrum
(
	Spectrum_Settings specSet
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	bool ready = false;
	int timeoutMsec = 0;

	SpectrumTraces trace = SpectrumTrace1;
	int maxTracePoints = specSet.traceLength;
	int outTracePoints = 0;
	float* traceData = NULL;
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
    
    printf("Trace Data Status:  %d\n", traceInfo.acqDataStatus);
	return traceData;
}


////~~~~


double* create_frequency_array
(
	Spectrum_Settings specSet
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	double* freq = NULL;
	int n = specSet.traceLength;
	freq = (double*)malloc(n*sizeof(double));
	for (int i=0; i < specSet.traceLength; i++)
	{
		freq[i] = specSet.actualStartFreq + specSet.actualFreqStepSize*i;
	}
	return freq;
}


////~~~~


int peak_power_detector
(
	float* traceData,
	double* freq, 
	Spectrum_Settings specSet
)
{
#ifdef DEBUG_ENABLE
    db_errno_int = errno; 
    snprintf(db_errno_str, BIG_BUF, "%s", strerror(db_errno_int));
    snprintf(db_notes, BIG_BUF, "\n<DEBUG> [%d] %s / %s()  ,  %s",
        __LINE__, __FILE__, __func__, DB_CLEAR);
    debug_handler(DB_REPORT);
#endif

	int peakIndex = 0;
	for (int ii = 0; ii < specSet.traceLength; ii++)
	{
		if (traceData[ii] > traceData[peakIndex])
		{
			peakIndex = ii;
		}
	}

	return peakIndex;
}


////////~~~~~~~~END>  rw_C.c
