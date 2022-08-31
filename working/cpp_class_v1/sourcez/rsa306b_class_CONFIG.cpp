/*
    implementation of the rsa306b_class
    using "CONFIG" function group of the API
    3 user action functions
    1 initialization function

        public:
            < 1 >  config_update_cf_rl()
            < 2 >  config_print_all()
            < 3 >  config_use_external_reference_source()
    
        private:
            < 1 >  _config_init()
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    the connected device is confirmed
    a running device is stopped
    the inputs are range-checked
    configuration of the center frequency and reference level
    memebers are updated
    caller responsible for calling "device_run()"
*/
int rsa306b::config_update_cf_rl
(
    double cf_Hz, 
    double rl_dBm
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not able to configure\n");
        #endif
        return CALL_FAILURE;
    }
    this->device_stop();

    if (cf_Hz < this->_config_center_frequency_min_hz ||
        cf_Hz > this->_config_center_frequency_max_hz  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tcenter frequency  %lf  Hz\n", cf_Hz);
            printf("\t\tmust be [  %lf  :  %lf  ]  Hz\n",
                this->_config_center_frequency_min_hz,
                this->_config_center_frequency_max_hz);
        #endif
        return CALL_FAILURE;
    }
    if (rl_dBm < this->REFERENCE_LEVEL_MIN_dbm ||
        rl_dBm > this->REFERENCE_LEVEL_MAX_dbm  )
    {
        #ifdef DEBUG_MIN
            printf("\n\treference level  %lf  dbm\n", rl_dBm);
            printf("\t\tmust be in range [  %lf  :  %lf  ]  dbm\n",
                this->REFERENCE_LEVEL_MIN_dbm,
                this->REFERENCE_LEVEL_MAX_dbm);
        #endif
        return CALL_FAILURE;
    }

    this->_api_return_status = RSA_API::CONFIG_SetReferenceLevel(rl_dBm);
    this->_api_error_check();
    this->_api_return_status = RSA_API::CONFIG_SetCenterFreq(cf_Hz);
    this->_api_error_check();

    this->_config_set_center_frequency_hz();
    this->_config_set_reference_level_dbm();
    #ifdef DEBUG_MIN
        printf("\n\tcenter frequency and reference level are configured\n");
    #endif
    return CALL_SUCCESS;
}


////~~~~


/*
    public < 2 >
    prints members as is, no updates
    designed to be used with a running device
*/
void rsa306b::config_print_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not able to configure\n");
        #endif
    } 

    printf("\nCONFIG information >>>\n");
    printf("\texternal frequency          :  %lf  Hz\n", this->_config_external_reference_frequency_hz);
    printf("\tmin center frequency        :  %lf  Hz\n", this->_config_center_frequency_min_hz);
    printf("\tcenter frequency            :  %lf  Hz\n", this->_config_center_frequency_hz);
    printf("\tmax center frequency        :  %lf  Hz\n", this->_config_center_frequency_max_hz);
    printf("\treference level             :  %lf  dBm\n", this->_config_reference_level_dbm);
    printf("\tfrequency reference source  :  ");
    switch (this->_config_frequency_reference_source_select)
    {
        case (RSA_API::FRS_INTERNAL) :
            printf("internal\n");
            break;
        case (RSA_API::FRS_EXTREF) :
            printf("external\n");
            break;
        case (RSA_API::FRS_GNSS) :
            printf("GNSS\n");
            break;
        case (RSA_API::FRS_USER) :
            printf("user-provided\n");
        default :
            printf("unknown\n");
    }
}


////~~~~


/*
    public < 3 >
    must have external reference source hooked up
    external source must be in range
        10 MHz 
        +/- 10 dbm in maximum amplitude
    internal used by default
    GNSS and user provided only availible on RSA500/600
    when enabled, the external source is mixed with 
        input signal, using the local oscillators
*/
void rsa306b::config_use_external_reference_source
(
    RSA_API::FREQREF_SOURCE source
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not able to configure\n");
        #endif
    } 
    this->device_stop();

    switch (source)
    {
        case (RSA_API::FRS_INTERNAL) :
            this->_api_return_status = RSA_API::CONFIG_SetFrequencyReferenceSource(source);
            this->_api_error_check();
            if (this->_api_return_status != RSA_API::noError)
            {
                #ifdef DEBUG_MIN
                    printf("\n\tfailed to activate internal reference source\n");
                #endif
            }
            else
            {
                #ifdef DEBUG_MIN
                    printf("\n\tinternal reference source activated\n");
                #endif
            }
            break;
        case (RSA_API::FRS_EXTREF) :
            this->_api_return_status = RSA_API::CONFIG_SetFrequencyReferenceSource(source);
            this->_api_error_check();
            if (this->_api_return_status != RSA_API::noError)
            {
                #ifdef DEBUG_MIN
                    printf("\n\tfailed to activate external reference source\n");
                #endif
            }
            else
            {
                #ifdef DEBUG_MIN
                    printf("\n\texternal reference source activated\n");
                #endif
            }
            break;
        case (RSA_API::FRS_GNSS) :
            #ifdef DEBUG_MIN
                printf("\n\tGNSS reference not available on the RSA-306B\n");
            #endif
            break;
        case (RSA_API::FRS_USER) :
            #ifdef DEBUG_MIN
                printf("\n\tuser reference not available on the RSA-306B\n");
            #endif
            break;
        default :
            #ifdef DEBUG_MIN
                printf("\n\tinvalid reference source type\n");
            #endif
            break;
    }
    this->_config_set_frequency_reference_source();
}


////~~~~


/*
    private < 1 >
    initialization requirements when connecting
        (1) preset the configurations
            - free run trigger
            - center frequency = 1.5e9 Hz
            - span = 40e6 Hz
            - IQ length = 1024
            - reference level = 0 dbm
        (2) find min/max center freqency
        (3) initialize members
*/
void rsa306b::_config_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not able to configure\n");
        #endif
    }
    
    // 1, preset
    this->_api_return_status = RSA_API::CONFIG_Preset();
    this->_api_error_check();

    // 2, find min/max ceneter frequency
    this->_api_return_status = RSA_API::CONFIG_GetMaxCenterFreq(
        &this->_config_center_frequency_max_hz);
    this->_api_error_check();
    this->_api_return_status = RSA_API::CONFIG_GetMinCenterFreq(
        &this->_config_center_frequency_min_hz);
    this->_api_error_check();

    // 3, initialize members
    this->_config_set_frequency_reference_source();
    this->_config_set_center_frequency_hz();
    this->_config_set_reference_level_dbm();
}


////////~~~~~~~~END>  rsa306b_class_CONFIG.
