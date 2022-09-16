/*
    API group "DEVICE"

    public :
        < 1 >  print_device()
    
    private :
        < 1 >  _device_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints "device" variables to stdout
    only the private struct is displayed
*/
CODEZ rsa306b_class::print_device()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'DEVICE' group >>>\n");
    (void)printf("\tis connected         :  %d\n", this->_vars.device.is_connected);
    (void)printf("\tis running           :  %d\n", this->_vars.device.is_running);
    (void)printf("\tis over temperature  :  %d\n", this->_vars.device.is_over_temperature);
    (void)printf("\tID                   :  %d\n", this->_vars.device.id);
    (void)printf("\terror string         :  %s\n", this->_vars.device.error_string);
    (void)printf("\tevent occured        :  %d\n", this->_vars.device.event_occured);
    (void)printf("\tevent ID             :  %d  ", this->_vars.device.event_id);
    switch (this->_vars.device.event_id)
    {
        case (0) : (void)printf("OVERANGE\n"); break;
        case (1) : (void)printf("TRIGGER\n");  break;
        default  : (void)printf("unknown\n");   break;
    }
    (void)printf("\tEvent Timestamp      :  %ld\n", this->_vars.device.event_timestamp);
    (void)printf("\tAPI Version          :  %s\n", this->_vars.device.info_type.apiVersion);
    (void)printf("\tFPGA Version         :  %s\n", this->_vars.device.info_type.fpgaVersion);
    (void)printf("\tFirmware Version     :  %s\n", this->_vars.device.info_type.fwVersion);
    (void)printf("\tHardware Version     :  %s\n", this->_vars.device.info_type.hwVersion);
    (void)printf("\tNomenclature         :  %s\n", this->_vars.device.info_type.nomenclature);
    (void)printf("\tSerial Number        :  %s\n", this->_vars.device.info_type.serialNum);
}


////~~~~


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
    
    this->_vars.device.is_connected        = false;
    this->_vars.device.is_over_temperature = false;
    this->_vars.device.is_running          = false;
    this->_vars.device.event_occured       = false;

    (void)memset(this->_vars.device.api_status_string , '\0'      , sizeof(this->_vars.device.api_status_string));
    (void)strncpy(this->_vars.device.api_status_string, INIT_CHARP, sizeof(this->_vars.device.api_status_string));

    this->_vars.device.id              = INIT_INT;
    this->_vars.device.event_id        = INIT_INT;
    this->_vars.device.event_timestamp = INIT_INT;

    (void)memset(this->_vars.device.info_type.apiVersion   , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.apiVersion  , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset(this->_vars.device.info_type.fpgaVersion  , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.fpgaVersion , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset(this->_vars.device.info_type.fwVersion    , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.fwVersion   , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset(this->_vars.device.info_type.hwVersion    , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.hwVersion   , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset(this->_vars.device.info_type.nomenclature , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.nomenclature, INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);
    (void)memset(this->_vars.device.info_type.serialNum    , '\0'      , RSA_API::DEVINFO_MAX_STRLEN);
    (void)strncpy(this->_vars.device.info_type.serialNum   , INIT_CHARP, RSA_API::DEVINFO_MAX_STRLEN-1);

    this->_device_copy_vars();
}


////////~~~~~~~~END>  rsa306b_device_print_init.cpp
    