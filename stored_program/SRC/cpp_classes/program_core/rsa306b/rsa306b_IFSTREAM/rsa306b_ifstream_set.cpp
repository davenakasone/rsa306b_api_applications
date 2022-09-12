/*
    API group "IFSTREAM", setters

    revise these later, put in more validation

    public :
        #  none
    
    private :
        < 1 >  _ifstream_set_vars()
        < 2 >  _ifstream_set_file_name_suffix()
        < 3 >  _ifstream_set_file_path()
        < 4 >  _ifstream_set_file_name_base()
        < 5 >  _ifstream_set_file_length_ms()
        < 6 >  _ifstream_set_file_count()
        < 7 >  _ifstream_set_output_configuration_select()
        < 8 >  _ifstream_set_is_enabled_adc()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_ifstream_set_file_name_suffix();
    this->_ifstream_set_file_path();
    this->_ifstream_set_file_name_base();
    this->_ifstream_set_file_length_ms();
    this->_ifstream_set_file_count();
    this->_ifstream_set_output_configuration_select();
    //this->_ifstream_set_is_enabled_adc(); user should not touch this
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_ifstream_set_file_name_suffix()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.file_name_suffix = this->vars.ifstream.file_name_suffix;
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_SetDiskFilenameSuffix(
            this->_vars.ifstream.file_name_suffix);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_ifstream_set_file_path()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    strcpy(this->_vars.ifstream.file_path, this->vars.ifstream.file_path);
    this->_vars.gp.api_status =
        RSA_API::IFSTREAM_SetDiskFilePath(
            this->_vars.ifstream.file_path);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_ifstream_set_file_name_base()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    strcpy(this->_vars.ifstream.file_name_base, this->vars.ifstream.file_name_base);
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_SetDiskFilenameBase(
            this->_vars.ifstream.file_name_base);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_ifstream_set_file_length_ms()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.file_length_ms = this->vars.ifstream.file_length_ms;
    this->_vars.gp.api_status =
        RSA_API::IFSTREAM_SetDiskFileLength(
            this->_vars.ifstream.file_length_ms);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_ifstream_set_file_count()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.file_count = this->vars.ifstream.file_count;
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_SetDiskFileCount(
            this->_vars.ifstream.file_count);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_ifstream_set_output_configuration_select()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.output_configuration_select = this->vars.ifstream.output_configuration_select;
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_SetOutputConfiguration(
            this->_vars.ifstream.output_configuration_select);
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_ifstream_set_is_enabled_adc()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.is_enabled_adc = this->vars.ifstream.is_enabled_adc;
    this->_vars.gp.api_status =
        RSA_API::IFSTREAM_SetEnable(
            this->_vars.ifstream.is_enabled_adc);
    this->_gp_confirm_api_status();
    this->_ifstream_copy_is_enabled_adc();
}


////////~~~~~~~~END>  rsa306b_ifstream_set.cpp
