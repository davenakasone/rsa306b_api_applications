/*
    API group "IFSTREAM", user funcitons

    public :
        < 1 >  ifstream_set_vars()
        < 2 >  ifstream_record_file()
        < 3 >  ifstream_acquire_adc_data()
        < 4 >  ifstream_acquire_adc_frames()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::ifstream_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_ifstream_set_vars();
}


////~~~~


/*
    < 2 > public
    produces "*.r3f" file
    user already set correct settings (or is using default)
*/
void rsa306b_class::ifstream_record_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (this->_vars.ifstream.output_configuration_select != 
        RSA_API::IFSOD_FILE_R3F                           )
    {
        #ifdef DEBUG_MIN
            printf("\n\tbad output configuration\n");
        #endif
        return;
    }
    this->_vars.ifstream.is_active = true;
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();
    RSA_API::IFSTREAM_SetEnable(true);

    while(this->_vars.ifstream.is_active == true)
    {
        this->_ifstream_get_is_active();
    }

    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->device_stop();

    #ifdef DEBUG_MIN
        printf("\n\trecording complete, check:  %s%s*\n", 
            this->_vars.ifstream.file_path, 
            this->_vars.ifstream.file_name_base);
    #endif
}


////~~~~


/*
    < 3 > public
    user initiates direct data acquisition
    no files are generated
    "vars.ifstream.adc_data_v" is populated with the entire raw ADC buffer
*/
void rsa306b_class::ifstream_acquire_adc_data()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

}


////////~~~~~~~~END>  rsa306b_ifstream_user1.cpp
