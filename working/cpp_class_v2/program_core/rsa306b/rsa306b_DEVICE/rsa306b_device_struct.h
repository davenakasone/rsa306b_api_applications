/*
    variables needed for the API "device group"
*/

#include "../../control/resourcez.h"


struct rsa306b_device_struct
{

    bool is_connected;                 // device connection status, important
    bool is_over_temperature;          // status of device over the temperature limit
    bool is_running;                   // status of run state
    int id;                            // only 1 spectrum analyzer can connect per machine
    RSA_API::DEVICE_INFO info_type;    // struct, has 6 strings
    
};
typedef struct rsa306b_device_struct rsa306b_device_struct;

////////~~~~~~~~END>  rsa306b_device_struct.h
