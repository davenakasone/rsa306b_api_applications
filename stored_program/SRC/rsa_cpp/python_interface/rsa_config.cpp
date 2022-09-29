/*
    source code for the python interface
    API group 'CONFIG'
*/

#include "python_access.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


void config_set_vars(double cf_hz, double ref_dbm)
{
    X_rsa.vars.config.center_frequency_hz = cf_hz;
    X_rsa.vars.config.reference_level_dbm = ref_dbm;
    (void)X_rsa.config_set_vars();
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_config.cpp
