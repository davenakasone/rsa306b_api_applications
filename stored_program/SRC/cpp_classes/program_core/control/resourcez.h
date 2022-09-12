/*
    macros of the program are restricted to this header file (except testing macros)
    these macros determine the flow and control of the core program

    libraries and other resources are consolidated here

    std=c++17 appears to be safe, but don't try to use > c++17 on the RSA_API

    {ON//OFF}  means that the macro should be commented on or off when building
*/

#ifndef H_resourcez
#define H_resourcez


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

#include "../../api_resourcez/RSA_API.h"    // has <time.h> and <stdint.h> 

#define GET_NAME(var) #var    // debug utility for identifying variable name

#define DE_BUG 22               // {ON//OFF} if activated, debug features are applied
//#define WAIT_ENTER_CLEAR 111    // {ON//OFF} if activated, calls wait_enter_clear(), stand-alone execution only

#ifdef DE_BUG
    // pick: none, one, or all
    //#define DEBUGS_WILL_PRINT 44    // {ON//OFF} if activated, debug activity is displayed to stdout
    #define DEBUGS_WILL_WRITE 55    // {ON//OFF} if activated, debug activity is writen

    // good to have at least "DEBUG_MIN" activated
    #define DEBUG_MIN 1917                  // {ON//OFF} tracks:  essential information, they will force-print to stdout
    #define DEBUG_MAX 1787                  // {ON//OFF} tracks:  additional information 
    #define DEBUG_CLI 1776                  // {ON//OFF} tracks:  __LINE__, __FILE__, __func__ for major calls
    #define DEBUG_CALL_CHECKS 1492          // {ON//OFF} tracks:  API return status checks and other call checks
    #define DEBUG_GETS 1992                 // {ON//OFF} tracks:  __LINE__, __FILE__, __func__ for getter calls
    #define DEBUG_SETS 1999                 // {ON//OFF} tracks:  __LINE__, __FILE__, __func__ for setter calls
    #define DEBUG_COPYS 2000                // {ON//OFF} tracks:  __LINE__, __FILE__, __func__ for copier calls
    #define DEBUG_CUSTOM 1865               // {ON//OFF} tracks: "    ", where ever you want to debug, place anywhere

    // only needed if there is trouble parsing "*.siq" files
    //#define DEBUG_SIQ_LOADER_HEADER 1941    // {ON//OFF} when activated, prints SIQ header as loaded, in 'siq_manager' class 
    //#define DEBUG_SIQ_LOADER_DATA 1945      // {ON//OFF} when activated, prints SIQ data as loaded, in 'siq_manager' class

    #ifdef DEBUG_MIN
        const char DEBUG_MIN_FORMAT[]         = "DEBUG_MIN        ,  <%4d>  %s/%s()  !!!  %s\n";
        
    #endif
    #ifdef DEBUG_MAX
        const char DEBUG_MAX_FORMAT[]         = "DEBUG_MAX        ,  <%4d>  %s/%s()  %s\n";
    #endif
    #ifdef DEBUG_CLI
        const char DEBUG_CLI_FORMAT[]         = "DEBUG_CLI        ,  <%4d>  %s/%s()\n";
    #endif
    #ifdef DEBUG_CALL_CHECKS
        const char DEBUG_CALL_CHECKS_FORMAT[] = "DEBUG_CALL_CHECKS,  <%4d>  %s/%s()\n";
    #endif
    #ifdef DEBUG_GETS
        const char DEBUG_GETS_FORMAT[]        = "DEBUG_GETS       ,  <%4d>  %s/%s()\n";
    #endif
    #ifdef DEBUG_SETS
        const char DEBUG_SETS_FORMAT[]        = "DEBUG_SETS       ,  <%4d>  %s/%s()\n";
    #endif
    #ifdef DEBUG_COPYS
        const char DEBUG_COPYS_FORMAT[]       = "DEBUG_COPYS      ,  <%4d>  %s/%s()\n";
    #endif
    #ifdef DEBUG_CUSTOM
        const char DEBUG_CUSTOM_FORMAT[]      = "DEBUG_CUSTOM     ,  <%4d>  %s/%s()  ***  %s\n";
    #endif
    const char DEBUG_FILEPATH[] = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DOC/debug_logs/";  // may require a change

    #define DEBUG_WIDTH 555    // size of the debug string, used for printing and writting
#endif

#define BUF_A 32      // a short general purpose buffer
#define BUF_B 64      // ..
#define BUF_C 128     // ...
#define BUF_D 256     // ....
#define BUF_E 512     // .....
#define BUF_F 1024    // a long general purpose buffer


#endif


////////~~~~~~~~END>  resourcez.h
