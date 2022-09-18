/*
    API group "DEVICE", the private copiers

    public :
        #  none
    
    private :
        < 1 >   _device_copy_vars()
        < 2 >   _device_copy_is_connected()
        < 3 >   _device_copy_is_over_temperature()
        < 4 >   _device_copy_is_running()
        < 5 >   _device_copy_event_occured()
        < 6 >   _device_copy_api_status_message()
        < 7 >   _device_copy_id()
        < 8 >   _device_copy_event_id()
        < 9 >   _device_copy_info_type()
        < 10 >  _device_copy_event_timestamp()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_device_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int copyz = 9;
    CODEZ codez_copyz[copyz];

    codez_copyz[1]  = this->_device_copy_api_status_message ();
    codez_copyz[2]  = this->_device_copy_event_id           ();
    codez_copyz[3]  = this->_device_copy_event_occured      ();
    codez_copyz[4]  = this->_device_copy_event_timestamp    ();
    codez_copyz[5]  = this->_device_copy_id                 ();
    codez_copyz[6]  = this->_device_copy_info_type          ();
    codez_copyz[7]  = this->_device_copy_is_connected       ();
    codez_copyz[8]  = this->_device_copy_is_over_temperature();
    codez_copyz[9]  = this->_device_copy_is_running         ();

    return this->cutil.codez_checker(codez_copyz, copyz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_device_copy_is_connected()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.is_connected = this->_vars.device.is_connected;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_device_copy_is_over_temperature()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.is_over_temperature = this->_vars.device.is_over_temperature;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_device_copy_is_running()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.is_running = this->_vars.device.is_running;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_device_copy_event_occured()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.event_occured = this->_vars.device.event_occured;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_device_copy_api_status_message()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->cutil.exe_strcpy(this->vars.device.api_status_message, this->_vars.device.api_status_message);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_device_copy_id()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.id = this->_vars.device.id;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_device_copy_event_id()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.event_id = this->_vars.device.event_id;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_device_copy_info_type()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int infoz = 6;
    CODEZ infoz_list[infoz];

    infoz_list[0]  = this->cutil.exe_strcpy(this->vars.device.info_type.apiVersion  , this->_vars.device.info_type.apiVersion);
    infoz_list[1]  = this->cutil.exe_strcpy(this->vars.device.info_type.fpgaVersion , this->_vars.device.info_type.fpgaVersion);
    infoz_list[2]  = this->cutil.exe_strcpy(this->vars.device.info_type.fwVersion   , this->_vars.device.info_type.fwVersion);
    infoz_list[3]  = this->cutil.exe_strcpy(this->vars.device.info_type.hwVersion   , this->_vars.device.info_type.hwVersion);
    infoz_list[4]  = this->cutil.exe_strcpy(this->vars.device.info_type.nomenclature, this->_vars.device.info_type.nomenclature);
    infoz_list[5]  = this->cutil.exe_strcpy(this->vars.device.info_type.serialNum   , this->_vars.device.info_type.serialNum);
    
    return this->cutil.codez_checker(infoz_list, infoz);
}


////~~~~


/*
    < 10 > private
*/
CODEZ rsa306b_class::_device_copy_event_timestamp()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.device.event_timestamp = this->_vars.device.event_timestamp;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_device_copy.cpp
