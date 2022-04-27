/*
    variables needed for the API group "CONFIG" 
*/

#ifndef H_rsa306b_config_struct
#define H_rsa306b_config_struct


#include "../../control/resourcez.h"


struct rsa306b_config_struct
{
    double reference_level_dbm;
    double center_frequency_hz;
    double min_center_frequency_hz;
    double max_center_frequency_hz;
    double external_reference_frequency_hz;

    RSA_API::FREQREF_SOURCE frequency_reference_source_select;
};
typedef struct rsa306b_config_struct rsa306b_config_struct;


#endif


////////~~~~~~~~END>  rsa306b_config_struct.h
