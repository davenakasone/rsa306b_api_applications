/*
    source code for the python interface
    API group 'CONFIG'

        < 1 >  config_set_vars()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
int config_set_vars(double cf_hz, double ref_dbm)
{
    static int juicy;
    X_rsa.vars.config.center_frequency_hz = cf_hz;
    X_rsa.vars.config.reference_level_dbm = ref_dbm;
    X_rsa.vars.config.frequency_reference_source_select = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;
    juicy = static_cast<int>(X_rsa.config_set_vars());
    return juicy; 
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_config.cpp
