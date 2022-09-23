/*
    API group "DEVICE"

    public :
        < 1 >  device_print()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints "device" variables to stdout
    only the private struct is displayed
*/
CODEZ rsa306b_class::device_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'DEVICE' group >>>\n");
    (void)printf("\tis connected         :  %d\n"   , this->_vars.device.is_connected);
    (void)printf("\tis running           :  %d\n"   , this->_vars.device.is_running);
    (void)printf("\tis over temperature  :  %d\n"   , this->_vars.device.is_over_temperature);
    (void)printf("\tID                   :  %d\n"   , this->_vars.device.id);
    (void)printf("\terror string         :  %s\n"   , this->_vars.device.api_status_message);
    (void)printf("\tevent occured        :  %d\n"   , this->_vars.device.event_occured);
    (void)printf("\tEvent Timestamp      :  %lu\n"  , this->_vars.device.event_timestamp);
    (void)printf("\tevent ID             :  %d  ,  ", this->_vars.device.event_id);
    switch (this->_vars.device.event_id)
    {
        case (0) : (void)printf("OVERANGE\n") ; break;
        case (1) : (void)printf("TRIGGER\n" ) ; break;
        default  : (void)printf("unknown\n" ) ; break;
    }
    (void)printf("\tAPI Version          :  %s\n" , this->_vars.device.info_type.apiVersion);
    (void)printf("\tFPGA Version         :  %s\n" , this->_vars.device.info_type.fpgaVersion);
    (void)printf("\tFirmware Version     :  %s\n" , this->_vars.device.info_type.fwVersion);
    (void)printf("\tHardware Version     :  %s\n" , this->_vars.device.info_type.hwVersion);
    (void)printf("\tNomenclature         :  %s\n" , this->_vars.device.info_type.nomenclature);
    (void)printf("\tSerial Number        :  %s\n" , this->_vars.device.info_type.serialNum);

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_device_print.cpp
    