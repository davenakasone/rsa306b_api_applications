/*
    variables needed for the API group "DEVICE" 
*/

#ifndef H_rsa306b_device_struct
#define H_rsa306b_device_struct


#include "../rsa306b_constants.h"


struct rsa306b_device_struct
{

    bool is_connected;                 // device connection status, important
    bool is_over_temperature;          // status of device over the temperature limit
    bool is_running;                   // status of run state
    bool event_occured;                // used to querry "DEVICE_GetEventStatus()", indicates if event occured
   
    char error_string[BUF_E];          // device error string, given return status
   
    int id;                            // only 1 spectrum analyzer can connect per machine
    int event_id;                      // used to querry "DEVICE_GetEventStatus()", holds event identification number
   
    RSA_API::DEVICE_INFO info_type;    // struct, has 6 strings
   
    uint64_t event_timestamp;          // used to querry "DEVICE_GetEventStatus()", holds event time stamp
    
};
typedef struct rsa306b_device_struct rsa306b_device_struct;


#endif


////////~~~~~~~~END>  rsa306b_device_struct.h
