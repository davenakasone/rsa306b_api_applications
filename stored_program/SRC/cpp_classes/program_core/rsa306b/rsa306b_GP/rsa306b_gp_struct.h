/*
    variables common to the "rsa306b" class
    these variables are used in multiple API function groups
*/

#ifndef H_rsa306b_gp_struct
#define H_rsa306b_gp_struct


#include "../rsa306b_constants.h"


struct rsa306b_gp_struct
{
    uint16_t acquisition_code;           // interperets API dat aquisiton status for most recent acquistion
    char acquisition_message[BUF_B];     // API aquisition message for most recent data acquisition
    char helper[BUF_E];                  // string for utility
    char holder[BUF_F];                  // big string for utility   
    int call_status;                     // set when calling non-API functions
    RSA_API::ReturnStatus api_status;    // enum, all API functions return this
};
typedef struct rsa306b_gp_struct rsa306b_gp_struct;


#endif


////////~~~~~~~~END>  rsa306b_gp_struct.h
