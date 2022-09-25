/*
    API group "DEVICE"

    public :
        #  none
    
    private :
        < 1 >  _device_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    initializes "device" variables to known values
    the public and private struct are updated
*/
CODEZ rsa306b_class::_device_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
    
    this->_vars.device.is_connected        = this->_vars.device._IS_CONNECTED;
    this->_vars.device.is_over_temperature = this->_vars.device._IS_OVER_TEMPERATURE;
    this->_vars.device.is_running          = this->_vars.device._IS_RUNNING;
    
    (void)memset (this->_vars.device.api_status_message, '\0'                                  , sizeof(this->_vars.device.api_status_message));
    (void)strncpy(this->_vars.device.api_status_message, BITCHECK_SUCCESS_MESSAGE, sizeof(this->_vars.device.api_status_message));

    this->_vars.device.id              = this->_vars.device._ID;

    this->_vars.device.event_id        = this->_vars.device._EVENT_ID;
    this->_vars.device.event_timestamp = this->_vars.device._EVENT_TIMESTAMP;
    this->_vars.device.event_occured   = this->_vars.device._EVENT_OCCURED;

    (void)memset (this->_vars.device.info_type.apiVersion   , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.apiVersion   , INIT_CHARP  , RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset (this->_vars.device.info_type.fpgaVersion  , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.fpgaVersion  , INIT_CHARP , RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset (this->_vars.device.info_type.fwVersion    , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.fwVersion    , INIT_CHARP  , RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset (this->_vars.device.info_type.hwVersion    , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.hwVersion    , INIT_CHARP   , RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset (this->_vars.device.info_type.nomenclature , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.nomenclature , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset (this->_vars.device.info_type.serialNum    , '\0'                                      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.serialNum    , INIT_CHARP  , RSA_API::DEVINFO_MAX_STRLEN-1);

    return this->_device_copy_vars();
}


////////~~~~~~~~END>  rsa306b_device_init.cpp
    