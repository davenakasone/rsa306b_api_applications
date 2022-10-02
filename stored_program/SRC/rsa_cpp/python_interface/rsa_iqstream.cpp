/*
    source code for the python interface
    API group 'IQSTREAM'

        < 1 >  iqstream_set_vars()
        < 2 >  iqstream_acq_direct()
        < 3 >  iqstream_write_csv()
        < 4 >  iqstream_record_siq()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
int iqstream_set_vars(int record_ms, double bw_hz, bool stream_file)
{
    // python user can pick these settings:
    X_rsa.vars.iqstream.record_time_ms = record_ms;
    X_rsa.vars.iqstream.bandwidth = bw_hz;
    if (stream_file == true)
    {
        X_rsa.vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_FILE_SIQ;
    }
    else
    {
        X_rsa.vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_CLIENT;
    }

    // python user should not be trusted with these settings:
    X_rsa.vars.iqstream.buffer_multiplier = iqsBuff::b2x;
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE;
    (void)sprintf(X_rsa.vars.iqstream.filename_base, "%s%s_", 
        DATA_DIRECTORY_RAW,
        IQSTREAM_FILE_NAME_BASE);
    X_rsa.vars.iqstream.suffix_control = static_cast<int>(RSA_API::IQSSDFN_SUFFIX_TIMESTAMP);
    return static_cast<int>(X_rsa.iqstream_set_vars());
}

// < 2 >
int iqstream_acq_direct()
{
    if (X_rsa.vars.iqstream.destination_select != RSA_API::IQSOUTDEST::IQSOD_CLIENT)
    {
        return static_cast<int>(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)X_rsa.iqstream_clear_sticky();
    return static_cast<int>(X_rsa.iqstream_acquire_data());
}

// < 3 >
char* iqstream_write_csv()
{
    if (X_rsa.vars.iqstream.destination_select != RSA_API::IQSOUTDEST::IQSOD_CLIENT)
    {
        return NULL;
    }

    X_rsa.cutil.helper[0] = '\0';
    if (X_rsa.iqstream_write_csv(X_rsa.cutil.helper) != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    return X_rsa.cutil.helper;
}

// < 4 >
char* iqstream_record_siq()
{
    if (X_rsa.vars.iqstream.destination_select != RSA_API::IQSOUTDEST::IQSOD_FILE_SIQ)
    {
        return NULL;
    }
    
    (void)X_rsa.iqstream_clear_sticky();
    memset(X_rsa.cutil.helper, '\0', sizeof(X_rsa.cutil.helper));
    if (X_rsa.iqstream_record_siq() != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    (void)strcpy(X_rsa.cutil.helper, X_rsa.vars.iqstream.filenames_0_data);
    return X_rsa.cutil.helper;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_iqstream.cpp


        

        



