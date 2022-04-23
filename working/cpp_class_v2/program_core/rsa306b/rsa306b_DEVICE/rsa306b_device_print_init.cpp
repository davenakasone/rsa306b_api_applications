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
void rsa306b_class::print_device()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'DEVICE' group:\n");
    printf("\tis connected         :  %d\n", this->_vars.device.is_connected);
    printf("\tis running           :  %d\n", this->_vars.device.is_running);
    printf("\tis over temperature  :  %d\n", this->_vars.device.is_over_temperature);
    printf("\tID                   :  %d\n", this->_vars.device.id);
    printf("\terror string         :  %s\n", this->_vars.device.error_string);
    printf("\tevent occured        :  %d\n", this->_vars.device.event_occured);
    printf("\tevent ID             :  %d  ", this->_vars.device.event_id);
    switch (this->_vars.device.event_id)
    {
        case (0) : printf("OVERANGE\n"); break;
        case (1) : printf("TRIGGER\n");  break;
        default : printf("unknown\n");   break;
    }
    printf("\tEvent Timestamp      :  %ld\n", this->_vars.device.event_timestamp);
    printf("\tAPI Version          :  %s\n", this->_vars.device.info_type.apiVersion);
    printf("\tFPGA Version         :  %s\n", this->_vars.device.info_type.fpgaVersion);
    printf("\tFirmware Version     :  %s\n", this->_vars.device.info_type.fwVersion);
    printf("\tHardware Version     :  %s\n", this->_vars.device.info_type.hwVersion);
    printf("\tNomenclature         :  %s\n", this->_vars.device.info_type.nomenclature);
    printf("\tSerial Number        :  %s\n", this->_vars.device.info_type.serialNum);
}


////~~~~


/*
    < 1 > private
    initializes "device" variables to known values
    the public and private struct are updated
*/
void rsa306b_class::_device_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 
    
    this->_vars.device.is_connected = false;
    this->_vars.device.is_over_temperature = false;
    this->_vars.device.is_running = false;
    this->_vars.device.event_occured = false;

    memset(this->_vars.device.error_string, '\0', BUF_D);
    strncpy(this->_vars.device.error_string, this->_vars.constants.INIT_STR, BUF_D-1);

    this->_vars.device.id = this->_vars.constants.INIT_INT;
    this->_vars.device.event_id = this->_vars.constants.INIT_INT;

    memset(this->_vars.device.info_type.apiVersion, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.apiVersion, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    memset(this->_vars.device.info_type.fpgaVersion, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.fpgaVersion, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    memset(this->_vars.device.info_type.fwVersion, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.fwVersion, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    memset(this->_vars.device.info_type.hwVersion, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.hwVersion, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    memset(this->_vars.device.info_type.nomenclature, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.nomenclature, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    memset(this->_vars.device.info_type.serialNum, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    strncpy(this->_vars.device.info_type.serialNum, this->_vars.constants.INIT_STR, RSA_API::DEVINFO_MAX_STRLEN-1);
    
    this->_vars.device.event_timestamp = this->_vars.constants.INIT_INT;

    this->_device_copy_vars();
}


////////~~~~~~~~END>  rsa306b_device_print_init.cpp
    