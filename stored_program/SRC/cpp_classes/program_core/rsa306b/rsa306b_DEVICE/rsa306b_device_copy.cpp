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
        < 6 >   _device_copy_error_string()
        < 7 >   _device_copy_id()
        < 8 >   _device_copy_event_id()
        < 9 >   _device_copy_info_type()
        < 10 >  _device_copy_event_timestamp()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_device_copy_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_device_copy_error_string();
    this->_device_copy_event_id();
    this->_device_copy_event_occured();
    this->_device_copy_event_timestamp();
    this->_device_copy_id();
    this->_device_copy_info_type();
    this->_device_copy_is_connected();
    this->_device_copy_is_over_temperature();
    this->_device_copy_is_running();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_device_copy_is_connected()
{ 
    this->vars.device.is_connected = this->_vars.device.is_connected;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_device_copy_is_over_temperature()
{
    this->vars.device.is_over_temperature = this->_vars.device.is_over_temperature;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_device_copy_is_running()
{
    this->vars.device.is_running = this->_vars.device.is_running;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_device_copy_event_occured()
{
    this->vars.device.event_occured = this->_vars.device.event_occured;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_device_copy_error_string()
{
    strcpy(this->vars.device.error_string, this->_vars.device.error_string);
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_device_copy_id()
{
    this->vars.device.id = this->_vars.device.id;
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_device_copy_event_id()
{
    this->vars.device.event_id = this->_vars.device.event_id;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_device_copy_info_type()
{
    strcpy(this->vars.device.info_type.apiVersion, this->_vars.device.info_type.apiVersion);
    strcpy(this->vars.device.info_type.fpgaVersion, this->_vars.device.info_type.fpgaVersion);
    strcpy(this->vars.device.info_type.fwVersion, this->_vars.device.info_type.fwVersion);
    strcpy(this->vars.device.info_type.hwVersion, this->_vars.device.info_type.hwVersion);
    strcpy(this->vars.device.info_type.nomenclature, this->_vars.device.info_type.nomenclature);
    strcpy(this->vars.device.info_type.serialNum, this->_vars.device.info_type.serialNum);
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_device_copy_event_timestamp()
{
    this->vars.device.event_timestamp = this->_vars.device.event_timestamp;
}


////////~~~~~~~~END>  rsa306b_device_copy.cpp
