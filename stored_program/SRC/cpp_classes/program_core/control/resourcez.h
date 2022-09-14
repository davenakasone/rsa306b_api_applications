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

#include "../../api_resourcez/RSA_API.h"    // has <time.h>, <stdint.h>, <thread.h>, ...

#define DE_BUG 22               // {ON//OFF} if activated, debug features are applied
#define WAIT_ENTER_CLEAR 111    // {ON//OFF} if activated, calls wait_enter_clear(), stand-alone execution only

#ifdef DE_BUG
    // pick: none, one, or all
    #define DEBUGS_WILL_PRINT 44    // {ON//OFF} if activated, debug activity is displayed to stdout
    #define DEBUGS_WILL_WRITE 55    // {ON//OFF} if activated, debug activity is writen

    // good to have at least "DEBUG_MIN" activated
    #define DEBUG_MIN 1917                  // {ON//OFF} tracks:  essential information, force-prints to stdout
    #define DEBUG_MAX 1787                  // {ON//OFF} tracks:  additional information, not always an error
    #define DEBUG_CLI 1776                  // {ON//OFF} tracks:  call stack of the executing program, for major calls
    #define DEBUG_CALL_CHECKS 1492          // {ON//OFF} tracks:  call checks for API and program internal calls
    #define DEBUG_GETS 1992                 // {ON//OFF} tracks:  for getter calls
    #define DEBUG_SETS 1999                 // {ON//OFF} tracks:  for setter calls
    #define DEBUG_COPYS 2000                // {ON//OFF} tracks:  for copier calls
    #define DEBUG_CUSTOM 1865               // {ON//OFF} tracks:  " ", where ever you want to debug, place anywhere

    // only needed if there is trouble parsing "*.siq" files
    //#define DEBUG_SIQ_LOADER_HEADER 1941    // {ON//OFF} prints SIQ header as loaded, in 'siq_manager' class 
    //#define DEBUG_SIQ_LOADER_DATA 1945      // {ON//OFF} prints SIQ data as loaded, in 'siq_manager' class

    #ifdef DEBUG_MIN
        constexpr char DEBUG_MIN_FORMAT[]         = "DEBUG_MIN        ,  <%4d>  %s/%s()  !!!  %s\n";
    #endif
    #ifdef DEBUG_MAX
        constexpr char DEBUG_MAX_FORMAT[]         = "DEBUG_MAX        ,  <%4d>  %s/%s()  %s\n";
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
    #ifdef DEBUG_CUSTOM
        constexpr char DEBUG_CUSTOM_FORMAT[]      = "DEBUG_CUSTOM     ,  <%4d>  %s/%s()  ***  %s\n";
    #endif
    
    // may require a change
    constexpr char DEBUG_FILEPATH[] = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DOC/debug_logs/";  
    
     // size of the debug string, used for printing and writting
    constexpr int DEBUG_WIDTH = 555;   

    // number of object instances debugger will track
     constexpr int ACTIVE_OBJECTS = 3; 

#endif

// Data IO
constexpr char DATA_DIRECTORY_RAW[]       = "../DATA/data_raw/";
constexpr char DATA_DIRECTORY_PROCESSED[] = "../DATA/data_processed/";   // path

#define GET_NAME(var) #var    // debug utility for identifying variable name

// program sizing parameters
constexpr int BUF_A = 32;      // a short general purpose buffer
constexpr int BUF_B = 64;      // ..
constexpr int BUF_C = 128;     // ...
constexpr int BUF_D = 256;     // ....
constexpr int BUF_E = 512;     // .....
constexpr int BUF_F = 1024;    // a long general purpose buffer

// program constants
constexpr char         INIT_CHAR            = 'Z';
constexpr char         INIT_CHARP[]         = "ZZZ";
constexpr double       INIT_DOUBLE          = -9999.9999;
constexpr float        INIT_FLOAT           = -999.999;
constexpr int          INIT_INT             = -999;
constexpr std::size_t  INIT_STL_LENGTH      = 3;    // for sizing std::vector, std::queue, ...
constexpr uint8_t      INIT_UINT            = 0xFF;
constexpr wchar_t      INIT_WCHARP[]        = L"wchar_t";


#endif


////////~~~~~~~~END>  resourcez.h
