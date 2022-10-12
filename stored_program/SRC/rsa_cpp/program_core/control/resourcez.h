/*
    macros of the program are restricted to this header file (except testing macros)
    these macros determine the flow and control of the core program

    libraries and other resources are consolidated here

    std=c++17 appears to be safe, but don't try to use > c++17 on the RSA_API

    {ON|OFF}  means that the macro should be commented on or off when building

    this is the header file with all the resources

        - C libraries
        - C++ libraries
        - the RSA API header
        - macros, preprocessor directives, and program flow (this header file)
*/

#ifndef H_resourcez
#define H_resourcez


#include "constant_expersions.h"    // brings all libraries and constants
#include "codez.h"                  // brings in the return "codez"


constexpr char UNLV_RSA_VERSION[] = "unlv_rsa_2022_10";    // program version:  unlv_rsa_<year YYYY>_<month MM>


#define DE_BUG           1    // {ON|OFF} if activated, debug features are applied, good to have at least this and  "DEBUG_MIN" activated
#define BLOCKING_TIMEOUT 2    // {ON|OFF} if activated, any acquisitions that block will be limited by "TIMEOUT_LIMIT_*"
#define SAFETY_CHECKS    3    // {ON|OFF} if activated, applies checks needed for proper device operation (but slows program)
#define BUILD_PYTHON     4    // {ON|OFF} if activated, compiles with C++ to python3 interfacing, should be on to make a proper library
#define UNIT_TESTING     5    // {ON|OFF} if activated, compiles with unit testing, select build target accordingly
    
    #ifdef BLOCKING_TIMEOUT
        constexpr int    TIMEOUT_LIMIT_MS = 222;
        constexpr double TIMEOUT_LIMIT_S  = static_cast<double>(TIMEOUT_LIMIT_MS) / 1000.0;    // milli-seconds to seconds
    #endif
    #ifdef UNIT_TESTING
        #define WAIT_ENTER_CLEAR 6    // {ON|OFF} if activated, calls wait_enter_clear(), for selected tasks and unit tests
    #endif


#ifdef DE_BUG
    // pick: none, one, or all
    //#define DEBUGS_WILL_PRINT 11    // {ON|OFF} if activated, debug activity is displayed to stdout
    #define DEBUGS_WILL_WRITE 111    // {ON|OFF} if activated, debug activity is writen

        // {ON|OFF} tracks:  essential information, force-prints to stdout, errors that would crash the program
        #define DEBUG_MIN               1917                  
        
        // {ON|OFF} tracks:  additional information, not always an error; usually valuable diagnostic information
        #define DEBUG_MAX               1787                  

        // {ON|OFF} tracks:  acqStatus and acqDataStatus of all status code verifications, after data is acquired
        //#define DEBUG_ACQ_STATUS        2022    

        // {ON|OFF} tracks:  call sequence of the executing program, for major calls only
        #define DEBUG_CLI               1776                  
    
        // {ON|OFF} tracks:  call sequence WITH internal and API status checks
        //#define DEBUG_CALL_CHECKS       1492 

        // {ON|OFF} tracks:  call sequence WITH getter calls
        //#define DEBUG_GETS              1941                
    
        // {ON|OFF} tracks:  call sequence WITH setter calls
        //#define DEBUG_SETS              1945                
    
        // {ON|OFF} tracks:  call sequence WITH  copier calls
        //#define DEBUG_COPYS             2000    

        // {ON|OFF} tracks:  call sequence WITH  timer calls
        //#define DEBUG_TIMERS            1165               
    
        // {ON|OFF} tracks:  " ", where ever you want to debug, place anywhere, usually just temporary
        #define DEBUG_CUSTOM            1865                

        // {ON|OFF} prints function entries of interest printed to stdout (no string format required)
        // sprinkle them whereever you need
        // #define DEBUG_FUNC 1956
        

        #ifdef DEBUG_MIN
            constexpr char DEBUG_MIN_FORMAT[]         = "DEBUG_MIN        ,  <%4d>  %s/%s()  !!!  %s";
        #endif
        #ifdef DEBUG_MAX
            constexpr char DEBUG_MAX_FORMAT[]         = "DEBUG_MAX        ,  <%4d>  %s/%s()  %s";
        #endif
        #ifdef DEBUG_ACQ_STATUS
            constexpr char DEBUG_ACQ_STATUS_FORMAT[]  = "DEBUG_ACQ_STATUS ,  %s";
        #endif
        #ifdef DEBUG_CLI
            constexpr char DEBUG_CLI_FORMAT[]         = "DEBUG_CLI        ,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_CALL_CHECKS
            constexpr char DEBUG_CALL_CHECKS_FORMAT[] = "DEBUG_CALL_CHECKS,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_GETS
            constexpr char DEBUG_GETS_FORMAT[]        = "DEBUG_GETS       ,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_SETS
            constexpr char DEBUG_SETS_FORMAT[]        = "DEBUG_SETS       ,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_COPYS
            constexpr char DEBUG_COPYS_FORMAT[]       = "DEBUG_COPYS      ,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_COPYS
            constexpr char DEBUG_TIMERS_FORMAT[]      = "DEBUG_TIMERS     ,  <%4d>  %s/%s()";
        #endif
        #ifdef DEBUG_CUSTOM
            constexpr char DEBUG_CUSTOM_FORMAT[]      = "DEBUG_CUSTOM     ,  <%4d>  %s/%s()  ***  %s";
        #endif
    
    // may require a change
    constexpr char DEBUG_FILEPATH[] = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DOC/debug_logs/";  
    
     // size of the debug string, used for printing and writting
    constexpr int DEBUG_WIDTH = 745;   

    // number of object instances debugger will track
     constexpr int ACTIVE_OBJECTS = 7; // {X_rsa + cutil} + {X_r3f + cutil} + {X_siq + cutil} + X_util

    #define GET_NAME(var) #var    // debug utility for identifying variable name

#endif


#endif


////////~~~~~~~~END>  resourcez.h
