/*
    source code for the python interface
    API group 'IfSTREAM'

        < 1 >  ifstream_set_vars()
        < 2 >  ifstream_acq_direct()
        < 3 >  ifstream_write_csv()
        < 4 >  ifstream_record_r3f()
        < 5 >  ifstream_equalization()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
int ifstream_set_vars(int record_ms, bool stream_file)
{
    // python user can change these
    X_rsa.vars.ifstream.file_length_max_ms = 11;
    if (stream_file == true)
    {
        X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_FILE_R3F;
    }
    else
    {
        X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_CLIENT;
    }
    
    // python user is forced to use these
    X_rsa.vars.ifstream.file_name_suffix = static_cast<int>(RSA_API::IFSSDFN_SUFFIX_TIMESTAMP);
    (void)strcpy(X_rsa.vars.ifstream.file_path, DATA_DIRECTORY_RAW);
    (void)strcpy(X_rsa.vars.ifstream.file_name_base, IFSTREAM_FILE_NAME_BASE);
    X_rsa.vars.ifstream.file_count = 1;
    X_rsa.vars.ifstream.is_enabled = false;
    return static_cast<int>(X_rsa.ifstream_set_vars());
}

// < 2 >
int ifstream_acq_direct()
{
    if (X_rsa.vars.ifstream.output_destination_select != RSA_API::IFSOUTDEST::IFSOD_CLIENT)
    {
        return static_cast<int>(CODEZ::_5_called_with_bad_paramerters);
    }
    return static_cast<int>(X_rsa.ifstream_acquire_data());
}

// < 3 >
char* ifstream_write_csv()
{
    if (X_rsa.vars.ifstream.output_destination_select != RSA_API::IFSOUTDEST::IFSOD_CLIENT)
    {
        return NULL;
    }

    X_rsa.cutil.helper[0] = '\0';
    if (X_rsa.ifstream_write_csv_data(X_rsa.cutil.helper) != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    return X_rsa.cutil.helper;
}

// < 4 >
char* ifstream_record_r3f()
{
    if (X_rsa.vars.ifstream.output_destination_select != RSA_API::IFSOUTDEST::IFSOD_FILE_R3F)
    {
        return NULL;
    }
    
    if (X_rsa.ifstream_record_r3f() != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    (void)X_util.find_files_with_extension(DATA_DIRECTORY_RAW, R3F_RAW_EXT, X_rsa.cutil.filez_in, true);
    if (X_rsa.cutil.filez_in.size() > 0)
    {
        (void)strcpy(X_rsa.cutil.helper, X_rsa.cutil.filez_in.back().c_str());
    }
    else
    {
        (void)sprintf(X_rsa.cutil.helper, "try: %s%s*.r3f ?",
            X_rsa.vars.ifstream.file_path,
            X_rsa.vars.ifstream.file_name_base);
    }
    return X_rsa.cutil.helper;
}

// < 5 >
char* ifstream_equalization()
{
    X_rsa.cutil.helper[0] = '\0';
    if (X_rsa.ifstream_write_csv_equalization(X_rsa.cutil.helper) != CODEZ::_0_no_errors)
    {
        return NULL;
    }
    return X_rsa.cutil.helper;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_ifstream.cpp
