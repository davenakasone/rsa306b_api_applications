/*
    macros of the program are restricted to this header file (except testing macros)
    these macros determine the flow and control of the core program

    libraries and other resources are consolidated here

    avoid the circular reference

    std=c++17 appears to be safe, but don't try to use > c++17 on the RSA_API
*/

#ifndef H_resourcez
#define H_resourcez

// for C++ use cases
#include <cmath>
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <cwchar>

// for interfacing with the C ABI
#include <dirent.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../api_resourcez/RSA_API.h"    // has <time.h> and <stdint.h> 

#define GET_NAME(var) #var

#define DEBUG_MIN 1917    // when activated, prints essential information
//#define DEBUG_MAX 1787    // when activated, prints additional information (keep DEBUG_MIN on if using)
//#define DEBUG_CLI 1776    // when activated, prints __LINE__, __FILE__, __func__ for each call
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
#define IFSTREAM_VECTOR_LENGTH 3     // correction vectors for the IFSTREAM data, a set of triplets

// setting "int getter" in "struct rsa306b_iqblk_struct" determines method to aquire IQBLK data
// use the fastest API call or method most appropriate for the use case
#define IQBLK_GET_IQ_DATA 0                   // use RSA_API::IQBLK_GetIQData() for acquisition
#define IQBLK_GET_IQ_DATA_CPLX 1              // use RSA_API::IQBLK_GetIQDataCplx() for acquisition
#define IQBLK_GET_IQ_DATA_DEINETERLEAVED 2    // use RSA_API::IQBLK_GetIQDataDeinterleaved() for acquisition

#endif


////////~~~~~~~~END>  resourcez.h
