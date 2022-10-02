/*
    API group "IFSTREAM", setters

    revise these later, put in more validation

    public :
        < 1 >  ifstream_set_vars()
    
    private :
        < 1 >  _ifstream_set_vars()
        < 2 >  _ifstream_set_file_name_suffix()
        < 3 >  _ifstream_set_file_path()
        < 4 >  _ifstream_set_file_name_base()
        < 5 >  _ifstream_set_file_length_ms()
        < 6 >  _ifstream_set_file_count()
        < 7 >  _ifstream_set_output_configuration_select()
        < 8 >  _ifstream_set_is_enabled()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::ifstream_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_ifstream_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_ifstream_set_vars()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 8;
    CODEZ caught_call[callz];

    caught_call[0] = this->_ifstream_set_file_name_suffix();
    caught_call[1] = this->_ifstream_set_file_path();
    caught_call[2] = this->_ifstream_set_file_name_base();
    caught_call[3] = this->_ifstream_set_file_length_ms();
    caught_call[4] = this->_ifstream_set_file_count();
    caught_call[5] = this->_ifstream_set_output_configuration_select();
    caught_call[6] = this->_ifstream_set_is_enabled();
    
    caught_call[7] = this->_ifstream_get_vars();

    return this->cutil.codez_checker(caught_call, callz);
    
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_ifstream_set_file_name_suffix()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.ifstream.file_name_suffix < static_cast<int>(RSA_API::IFSSDFN_SUFFIX_NONE))
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid suffix  %d, must be > %d",
                this->vars.ifstream.file_name_suffix,
                static_cast<int>(RSA_API::IFSSDFN_SUFFIX_NONE));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)this->device_stop();

    this->_vars.ifstream.file_name_suffix = this->vars.ifstream.file_name_suffix;
    this->_api_status = 
        RSA_API::IFSTREAM_SetDiskFilenameSuffix
        (
            this->_vars.ifstream.file_name_suffix
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_ifstream_set_file_path()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.ifstream.file_path == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s",
                this->cutil.codez_messages(CODEZ::_7_parameter_not_allocated));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    (void)this->device_stop();

    (void)strcpy(this->_vars.ifstream.file_path, this->vars.ifstream.file_path);
    this->_api_status =
        RSA_API::IFSTREAM_SetDiskFilePath
        (
            this->_vars.ifstream.file_path
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_ifstream_set_file_name_base()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.ifstream.file_name_base == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s",
                this->cutil.codez_messages(CODEZ::_7_parameter_not_allocated));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    (void)this->device_stop();

    (void)strcpy(this->_vars.ifstream.file_name_base, this->vars.ifstream.file_name_base);
    this->_api_status = 
        RSA_API::IFSTREAM_SetDiskFilenameBase
        (
            this->_vars.ifstream.file_name_base
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_ifstream_set_file_length_ms()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.ifstream.file_length_max_ms > this->_vars.ifstream._FILE_LENGTH_MAX_MS)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid max length ms:  %d, must be < %d",
                this->vars.ifstream.file_length_max_ms,
                this->_vars.ifstream.FILE_LENGTH_MAX_MS);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)this->device_stop();

    this->_vars.ifstream.file_length_max_ms = this->vars.ifstream.file_length_max_ms;
    this->_api_status =
        RSA_API::IFSTREAM_SetDiskFileLength
        (
            this->_vars.ifstream.file_length_max_ms
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_ifstream_set_file_count()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    // enforce count if it becomes a problem
    (void)this->device_stop();

    this->_vars.ifstream.file_count = this->vars.ifstream.file_count;
    this->_api_status = 
        RSA_API::IFSTREAM_SetDiskFileCount
        (
            this->_vars.ifstream.file_count
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_ifstream_set_output_configuration_select()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.ifstream.output_destination_select != RSA_API::IFSOD_CLIENT  &&
        this->vars.ifstream.output_destination_select != RSA_API::IFSOD_FILE_R3F )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid output destination:  %d, must be IFSOD_CLIENT or IFSOD_FILE_R3F",
                static_cast<int>(this->vars.ifstream.output_destination_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
    (void)this->device_stop();

    this->_vars.ifstream.output_destination_select = this->vars.ifstream.output_destination_select;
    this->_api_status = 
        RSA_API::IFSTREAM_SetOutputConfiguration
        (
            this->_vars.ifstream.output_destination_select
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_ifstream_set_is_enabled()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_vars.ifstream.is_enabled = this->vars.ifstream.is_enabled;
    this->_api_status = 
        RSA_API::IFSTREAM_SetEnable
        (
            this->_vars.ifstream.is_enabled
        );
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_ifstream_set.cpp
