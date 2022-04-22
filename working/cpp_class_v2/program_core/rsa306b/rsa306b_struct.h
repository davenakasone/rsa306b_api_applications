/*
    the member variables for the "rsa306b" class are contained
    composes function group variables to provide organized user access
*/

#ifndef H_rsa306b_struct
#define H_rsa306b_struct


#include "./rsa306b_CONST/rsa306b_constants_class.h"
#include "./rsa306b_GP/rsa306b_gp_struct.h"
#include "./rsa306b_DEVICE/rsa306b_device_struct.h"


struct rsa306b_struct
{

    rsa306b_constants_class constants;    // important constants for the spectrum analyzer
    rsa306b_gp_struct gp;                 // common use class variables "general purpose"
    rsa306b_device_struct device;         // API group "DEVICE"

}; typedef struct rsa306b_struct rsa306b_struct;


#endif


////////~~~~~~~~END>  rsa306b_struct.h
