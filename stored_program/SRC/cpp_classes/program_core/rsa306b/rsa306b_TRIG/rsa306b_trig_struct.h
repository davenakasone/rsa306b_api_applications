/*
    variables needed for the API group "TRIG"
*/

#ifndef H_rsa306b_trig_struct
#define H_rsa306b_trig_struct


#include "../rsa306b_constants.h"


struct rsa306b_trig_struct
{

    double if_power_level;                           // power level of IF trigger occurs
    double position_percent;                         // how much data to store before and after trigger event
    
    RSA_API::TriggerMode mode_select;                // free-run or triggered
    RSA_API::TriggerSource source_select;            // where the source of the trigger is derived
    RSA_API::TriggerTransition transition_select;    // event that causes trigger activation

};
typedef struct rsa306b_trig_struct rsa306b_trig_struct;


#endif


////////~~~~~~~~END>  rsa306b_trig_struct.h
