/*
    source code for the python interface
    API group 'IQBLK'

        < 1 >  iqblk_set_vars()
        < 2 >  iqblk_acquire()
        < 3 >  iqblk_write_csv()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
int iqblk_set_vars(double bw_hz)
{
    // python user gets standard trace length + complex format
    static int juicy;
    X_rsa.vars.iqblk.bandwidth_hz = bw_hz;
    X_rsa.vars.iqblk.getting_select = iqblkGetData::complex;
    juicy = static_cast<int>(X_rsa.iqblk_set_vars());
    return juicy;
}

// < 2 >
int iqblk_acquire()
{
    static int juicy;
    juicy = static_cast<int>(X_rsa.iqblk_acquire_data());
    return juicy;
}

// < 3 >
char* iqblk_write_csv()
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    if (X_rsa.iqblk_write_csv(juicy) != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    return juicy;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_iqblk.cpp


        

        



