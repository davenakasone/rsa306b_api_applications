/*
    source code for the python interface
    API group 'IQBLK'

        < 1 >  iqblk_set_vars()
        < 2 >  iqblk_acquire()
        < 3 >  iqblk_make_csv()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
void iqblk_set_vars(double bw_hz)
{
    // python user gets standard trace length + complex format
    X_rsa.vars.iqblk.bandwidth_hz = bw_hz;
    X_rsa.vars.iqblk.getting_select = iqblkGetData::complex;
    (void)X_rsa.iqblk_set_vars();
}

// < 2 >
int iqblk_acquire()
{
    return static_cast<int>(X_rsa.iqblk_acquire_data());
}

// < 3 >
char* iqblk_make_csv()
{
    X_rsa.cutil.helper[0] = '\0';
    if (X_rsa.iqblk_make_csv(X_rsa.cutil.helper) != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    return X_rsa.cutil.helper;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_iqblk.cpp


        

        



