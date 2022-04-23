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
//#define DEBUG_ERR 1492    // when activated, prints *_error_checks() that result in an API error condition

#define BUF_A 32                    // a short general purpose buffer
#define BUF_B 64                    // ..
#define BUF_C 128                   // ...
#define BUF_D 256                   // ....
#define BUF_E 512                   // .....
#define BUF_F 1024                  // a long general purpose buffer

#define SPECTRUM_DATA_LENGTH 2048   // spectrum aquisitions, stops need for dynamic allocation, trying dynamic first?
#define AUDIO_DATA_LENGTH 65535     // audio data points, 2^16 - 1


#endif


////////~~~~~~~~END>  resourcez.h
