/*
    resource for the API experiments
*/

#ifndef H_juice
#define H_juice

#include <stdlib.h>
#include <stdio.h>

#include "/home/unlv/Desktop/rsa306b_api_applications/stored_program/SRC/rsa_cpp/program_core/control/RSA_API.h"

constexpr int CALL_GOOD = 777;    // the function executed successfuly
constexpr int CALL_BAD  = 666;    // the function did not execute as designed

int AUDIO_GetVolume(int repitions);    // an API getter is called (see how it responds connected and disconnected)


#endif


////////~~~~~~~~END>  juice.h
