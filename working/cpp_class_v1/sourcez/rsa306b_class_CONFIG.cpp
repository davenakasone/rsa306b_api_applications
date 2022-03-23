/*
    implementation of the rsa306b_class
    using "CONFIG" function group of the API
        # rsa_configure_cf_rl()
        # print_configuration()
*/

#include "../includez/rsa306b_class.h"


/*
    public
    called to set the center frequecny and reference level
    as of now, automatically uses internal refrence
    change in future if external reference source is needed
    these changes need the device to stop
        caller responsible for calling rsa_run() upon return
*/
void rsa306b::rsa_configure_cf_rl(double cf, double rl)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("can't configure, no device connected\n");
        #endif
        return;
    }
    this->rsa_stop();

    this->frequency_reference_source = RSA_API::FRS_INTERNAL; // change source here
    this->api_return_status = RSA_API::CONFIG_SetFrequencyReferenceSource(
        this->frequency_reference_source);
    this->error_check();

    if (cf > FREQUENCY_MIN_HZ &&
        cf < FREQUENCY_MAX_HZ  )
    {
        this->center_frequency = cf;
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("center frequency is out of range, must be:  %lf  to  %lf  Hz\n",
                FREQUENCY_MIN_HZ, FREQUENCY_MAX_HZ);
        #endif
        return;
    }

    if (rl > REFERENCE_LEVEL_MIN_DB &&
        rl < REFERENCE_LEVEL_MAX_DB  )
    {
        this->reference_level = rl;
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("reference level is out of range, must be:  %lf  to  %lf  dB\n",
                REFERENCE_LEVEL_MIN_DB, REFERENCE_LEVEL_MAX_DB);
        #endif
        return;
    }

    this->api_return_status = RSA_API::CONFIG_Preset();
    this->error_check();

    this->api_return_status = RSA_API::CONFIG_SetReferenceLevel(this->reference_level);
    this->error_check();

    this->api_return_status = RSA_API::CONFIG_SetCenterFreq(this->center_frequency);
    this->error_check();

    #ifdef DEBUG_MIN
        printf("center frequency and reference level are configured\n");
    #endif
}


////~~~~


/*
    public
    displays basic information about the current configuration
*/
void rsa306b::print_configuration()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("can't print configuration, no device connected\n");
        #endif
        return;
    }
    
    this->api_return_status = RSA_API::CONFIG_GetCenterFreq(&this->center_frequency);
    this->error_check();
    this->api_return_status = RSA_API::CONFIG_GetMaxCenterFreq(&this->center_frequency_max);
    this->error_check();
    this->api_return_status = RSA_API::CONFIG_GetMinCenterFreq(&this->center_frequency_min);
    this->error_check();
    this->api_return_status = RSA_API::CONFIG_GetReferenceLevel(&this->reference_level);
    this->error_check();
    this->api_return_status = RSA_API::CONFIG_GetFrequencyReferenceSource(&this->frequency_reference_source);
    this->error_check();

    printf("\ndevice configuration status >>>\n");
    printf("\tmin center frequency:        %lf  Hz\n", this->center_frequency_min);
    printf("\tcenter frequency:            %lf  Hz\n", this->center_frequency);
    printf("\tmax center frequency:        %lf  Hz\n", this->center_frequency_max);
    printf("\treference level:             %lf  dBm\n", this->reference_level);
    printf("\tfrequency reference source:  ");
    switch (this->frequency_reference_source)
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


////////~~~~~~~~END>  rsa306b_class_CONFIG.cpp
