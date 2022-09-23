/*
    macros of the program are restricted to this header file (except testing macros)
    these macros determine the flow and control of the core program

    libraries and other resources are consolidated here

    std=c++17 appears to be safe, but don't try to use > c++17 on the RSA_API

    {ON|OFF}  means that the macro should be commented on or off when building
*/

#ifndef H_resourcez
#define H_resourcez

constexpr char UNLV_RSA_VERSION[] = "unlv_rsa_2022_09";    // program version:  unlv_rsa_<year YYYY>_<month MM>

// for C++ use cases
#include <chrono>
#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <vector>

// for interfacing with the C ABI
#include <dirent.h>
#include <float.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include "RSA_API.h"    // has <time.h>, <stdint.h>, <thread.h>, ...


#define DE_BUG           1    // {ON|OFF} if activated, debug features are applied, good to have at least this and  "DEBUG_MIN" activated
#define LOOP_TIMEOUT     2    // {ON|OFF} if activated, any acquisitions that require polling in a loop will have time-out applied
#define SAFETY_CHECKS    3    // {ON|OFF} if activated, applies checks needed for proper device operation (but slows program)
#define BUILD_PYTHON     4    // {ON|OFF} if activated, compiles with C++ to python3 interfacing, should be on to make a proper library
#define UNIT_TESTINGG    5    // {ON|OFF} if activated, compiles with unit testing, select build target accordingly
    #ifdef UNIT_TESTINGG
        #define WAIT_ENTER_CLEAR 11    // {ON|OFF} if activated, calls wait_enter_clear(), for selected tasks and unit tests
    #endif

#ifdef DE_BUG
    // pick: none, one, or all
    #define DEBUGS_WILL_PRINT 11    // {ON|OFF} if activated, debug activity is displayed to stdout
    #define DEBUGS_WILL_WRITE 111    // {ON|OFF} if activated, debug activity is writen

        // {ON|OFF} tracks:  essential information, force-prints to stdout, errors that would crash the program
        #define DEBUG_MIN               1917                  
        
        // {ON|OFF} tracks:  additional information, not always an error; usually valuable diagnostic information
        #define DEBUG_MAX               1787                  

        // {ON|OFF} tracks:  acqStatus and acqDataStatus of all status code verifications, after data is acquired
        #define DEBUG_ACQ_STATUS        2022    

        // {ON|OFF} tracks:  call sequence of the executing program, for major calls only
        #define DEBUG_CLI               1776                  
    
        // {ON|OFF} tracks:  call sequence WITH internal and API status checks
        #define DEBUG_CALL_CHECKS       1492 

        // {ON|OFF} tracks:  call sequence WITH getter calls
        #define DEBUG_GETS              1992                 
    
        // {ON|OFF} tracks:  call sequence WITH setter calls
        #define DEBUG_SETS              1999                 
    
        // {ON|OFF} tracks:  call sequence WITH  copier calls
        #define DEBUG_COPYS             2000    

        // {ON|OFF} tracks:  call sequence WITH  timer calls
        #define DEBUG_TIMERS            1165               
    
        // {ON|OFF} tracks:  " ", where ever you want to debug, place anywhere, usually just temporary
        #define DEBUG_CUSTOM            1865               

        // {ON|OFF} prints SIQ header as loaded, in 'siq_manager' class 
        #define DEBUG_SIQ_LOADER_HEADER 1941   

        // {ON|OFF} prints SIQ data as loaded, in 'siq_manager' class 
        #define DEBUG_SIQ_LOADER_DATA   1945     


        #ifdef DEBUG_MIN
            constexpr char DEBUG_MIN_FORMAT[]         = "DEBUG_MIN        ,  <%4d>  %s/%s()  !!!  %s\n";
        #endif
        #ifdef DEBUG_MAX
            constexpr char DEBUG_MAX_FORMAT[]         = "DEBUG_MAX        ,  <%4d>  %s/%s()  %s\n";
        #endif
        #ifdef DEBUG_ACQ_STATUS
            constexpr char DEBUG_ACQ_STATUS_FORMAT[]  = "DEBUG_ACQ_STATUS ,  %s\n";
        #endif
        #ifdef DEBUG_CLI
            constexpr char DEBUG_CLI_FORMAT[]         = "DEBUG_CLI        ,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_CALL_CHECKS
            constexpr char DEBUG_CALL_CHECKS_FORMAT[] = "DEBUG_CALL_CHECKS,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_GETS
            constexpr char DEBUG_GETS_FORMAT[]        = "DEBUG_GETS       ,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_SETS
            constexpr char DEBUG_SETS_FORMAT[]        = "DEBUG_SETS       ,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_COPYS
            constexpr char DEBUG_COPYS_FORMAT[]       = "DEBUG_COPYS      ,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_COPYS
            constexpr char DEBUG_TIMERS_FORMAT[]      = "DEBUG_TIMERS     ,  <%4d>  %s/%s()\n";
        #endif
        #ifdef DEBUG_CUSTOM
            constexpr char DEBUG_CUSTOM_FORMAT[]      = "DEBUG_CUSTOM     ,  <%4d>  %s/%s()  ***  %s\n";
        #endif
    
    // may require a change
    constexpr char DEBUG_FILEPATH[] = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DOC/debug_logs/";  
    
     // size of the debug string, used for printing and writting
    constexpr int DEBUG_WIDTH = 745;   

    // number of object instances debugger will track
     constexpr int ACTIVE_OBJECTS = 7; 

    #define GET_NAME(var) #var    // debug utility for identifying variable name

#endif


// program sizing parameters
constexpr int BUF_A = 32;      // a short general purpose buffer
constexpr int BUF_B = 64;      // ..
constexpr int BUF_C = 128;     // ...
constexpr int BUF_D = 256;     // ....
constexpr int BUF_E = 512;     // .....
constexpr int BUF_F = 1024;    // a long general purpose buffer

// Data IO
constexpr char DATA_DIRECTORY_RAW[]       = "../DATA/data_raw/";         // write data received directly from the RSA-306B here
constexpr char DATA_DIRECTORY_PROCESSED[] = "../DATA/data_processed/";   // write data modified by the program here
constexpr char DATA_OUTPUT_EXTENSTION[]   = ".csv";                      // default output file extention

// Common hardware constants
constexpr std::size_t TRACES_306B                = 3UL;                // the RSA-306B has 3 possible traces available
constexpr char        BITCHECK_SUCCESS_MESSAGE[] = "good bitcheck";    // common message recorded upon successful bitcheck
constexpr unsigned    BITCHECK_SUCCESS           = 0U;                 // all successful bitchecks result in 0
    // AUDIO
    constexpr char AUDIO_FILE_NAME_BASE[]                                = "audio";              // default output file base name for the API group
    constexpr char AUDIO_FIELD_1[]                                       = "interval";           // used to label fields in "*.csv" output
    constexpr char AUDIO_FIELD_2[]                                       = "values";             // used to label fields in "*.csv" output
    // DPX
    constexpr char DPX_FILE_NAME_BASE[]                                  = "dpx";                // default output file base name for the API group
    constexpr char DPX_OUTPUT_TYPE_SOGRAM_BITMAP[]                       = "sogram_bitmap";      // default to place in file name when writing a 'sogram_bitmap'
    constexpr char DPX_OUTPUT_TYPE_SPECTRUM_BITMAP[]                     = "spectrum_bitmap";    // default to place in file name when writing a 'spectrum_bitmap'
    constexpr char DPX_OUTPUT_TYPE_HI_RES_LINE[]                         = "hires_line";         // default to place in file name when writing a 'hires_line'
    constexpr int  DPX_BITCHECKS                                         = 5;                    // checks for 'DPX' acqDataStatus
    constexpr char DPX_BITCHECK_MESSAGES[DPX_BITCHECKS][BUF_B]           =                       // error codes for 'DPX' bitchecks
    {
        "b0 : input to the ADC was outside of its operating range",
        "b1 : loss of locked status on the reference oscillator",
        "b4 : power (5V and USB) failure detected",
        "b5 : dropped frame, loss of ADC data frame samples",
        "acqDataStatus bitcheck failures: "
    };
    // IFSTREAM
    constexpr char IFSTREAM_FILE_NAME_BASE[]                             = "ifstream";           // default base name for output files
    constexpr int  IFSTREAM_BITCHECKS                                    = 3;                    // checks for 'IFSTREAM' acqStatus
    constexpr char IFSTREAM_FIELD_1[]                                    = "interval";           // used to label fields in "*.csv" output
    constexpr char IFSTREAM_FIELD_2[]                                    = "adc";                // used to label fields in "*.csv" output
    constexpr char IFSTREAM_BITCHECK_MESSAGES[IFSTREAM_BITCHECKS][BUF_B] =                       // error codes for 'IFSTREAM' bitchecks
    {
        "b0 : ADC input overrange detected",
        "b1 : continuity error (gap) detected in IF frames",
        "acqStatus bitcheck failures: "
    };
    // SPECTRUM
    constexpr char SPECTRUM_FILE_NAME_BASE[]                             = "spectrum";           // default output file base name for the API group
    constexpr int  SPECTRUM_BITCHECKS                                    = 5;                    // checks for DPX acqDataStatus
    constexpr char SPECTRUM_BITCHECK_MESSAGES[SPECTRUM_BITCHECKS][BUF_B] =                       // error codes for 'SPECTRUM' bitchecks
    {
        "b0 : input to the ADC was outside of its operating range",
        "b1 : loss of locked status on the reference oscillator",
        "b4 : power (5V and USB) failure detected",
        "b5 : dropped frame, loss of ADC data frame samples",
        "acqDataStatus bitcheck failures: "
    };

// program initialization values, covers most types
constexpr char         INIT_CHAR       = 'Z';
constexpr char         INIT_CHARP[]    = "ZZZ";
constexpr double       INIT_DOUBLE     = -9.9F;
constexpr float        INIT_FLOAT      = -9.9F;
constexpr int          INIT_INT        = -9;
constexpr int8_t       INIT_INT8       = -9;
constexpr int16_t      INIT_INT16      = -9;
constexpr int32_t      INIT_INT32      = -9;
constexpr int64_t      INIT_INT64      = -9L;
constexpr std::size_t  INIT_STD_SIZE_T = 5UL;
constexpr std::size_t  INIT_STL_LENGTH = 3UL;    // for sizing std::vector, std::queue, ...make this big if preallocating helps
constexpr uint8_t      INIT_UINT8      = 0xFFU;
constexpr uint16_t     INIT_UINT16     = 0xFFFFU;
constexpr uint32_t     INIT_UINT32     = 0xFFFFFFFFU;
constexpr uint64_t     INIT_UINT64     = 0xFFFFFFFFFFFFFFFFLU;
constexpr wchar_t      INIT_WCHARP[]   = L"wchar_t";


#endif


////////~~~~~~~~END>  resourcez.h
