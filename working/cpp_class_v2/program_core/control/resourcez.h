/*
    macros of the program are restricted to this header file (except testing macros)
    these macros determine the flow and control of the core program

    libraries and other resources are consolidate here

    avoid the circular reference
*/

#ifndef H_resourcez
#define H_resourcez


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../api_resourcez/RSA_API.h"    // has <time.h> and <stdint.h> 

#define GET_NAME(var) #var

//#define DEBUG_CLI 1776    // when activated, prints __LINE__, __FILE__, __func__ for each call
#define DEBUG_MIN 1917    // when activated, prints essential information
//#define DEBUG_MAX 1787    // when activated, prints additional information (keep DEBUG_MIN on if using)
//#define DEBUG_ERR 1492    // when activated, prints the occurance of API and class "call checks"

#define BUF_A 32                    // a short general purpose buffer
#define BUF_B 64                    // ..
#define BUF_C 128                   // ...
#define BUF_D 256                   // ....
#define BUF_E 512                   // .....
#define BUF_F 1024                  // a long general purpose buffer

#define TRACES_AVAILABLE 3           // the RSA-306B has three traces that can be used
#define SPECTRUM_DATA_LENGTH 2048    // spectrum aquisitions, go dynamic if needed
#define AUDIO_DATA_LENGTH 1024       // maximum audio data points, 2^16 - 1, go dynamic if needed
#define IFSTREAM_SUFFIX -1           // control file suffix name for IFSTREAM group, {0:increment, -1:timestamp, -2:none}
#define IFSTREAM_VECTOR_LENGTH 3     // correction vectors for the IFSTREAM data, a set of tripplets


#endif


////////~~~~~~~~END>  resourcez.h
