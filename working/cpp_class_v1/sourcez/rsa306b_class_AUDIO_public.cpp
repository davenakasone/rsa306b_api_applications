/*
    implementation of the rsa306b_class
    using "AUDIO" function group of the API
    public functions for user action 
    getters are combined in the struct "audio_type"

        public:
            < 1 >  audio_print_all()
            < 2 >  audio_get_settings()
            < 3 >  audio_prepare()
            < 4 >  audio_get_data()

        private:
            # none
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    call to print availible audio information to stdout
*/
void rsa306b::audio_print_all()                       
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->audio_get_settings(&this->_audio_type);

    printf("\nAUDIO information >>>\n");
    printf("\tdemodulation status      :  ");
    if (this->_audio_type.is_demodulating == true)
    {
        printf("%d  ,  device IS demodulating\n", this->_audio_type.is_demodulating);
    }
    else
    {
        printf("%d  ,  device is NOT demodulating\n", this->_audio_type.is_demodulating);
    }
    printf("\tcenter frequency offset  :  %lf Hz\n", this->_audio_type.center_frequency_offset_hz);
    printf("\tmute status              :  ");
    if (this->_audio_type.is_mute == true)
    {
        printf("%d  ,  output speakers ARE muted\n", this->_audio_type.is_mute);
    }
    else
    {
        printf("%d  ,  output speakers are NOT muted\n", this->_audio_type.is_mute);
    }
    printf("\tvolume                   :  %f\n", this->_audio_type.volume);
    printf("\tdemodulation mode        :  ");
    switch (this->_audio_type.demodulation_mode_select)
    {
        case (RSA_API::ADM_FM_8KHZ)   : printf("FM, 8 kHz\n");   break;
        case (RSA_API::ADM_FM_13KHZ)  : printf("FM, 13 kHz\n");  break;
        case (RSA_API::ADM_FM_75KHZ)  : printf("FM, 75 kHz\n");  break;
        case (RSA_API::ADM_FM_200KHZ) : printf("FM, 200 kHz\n"); break;
        case (RSA_API::ADM_AM_8KHZ)   : printf("FM, 8 kHz\n");   break;
        default                       : printf("unknown\n");     break;
    }
    printf("\taudio data received      :  %d\n", this->_audio_type.data_length_received);
}


////~~~~


/*
    public < 2 >
    updates settings into provided struct
    uses 5x API calls to get audio settings
*/
void rsa306b::audio_get_settings
(
    audio_type* settings
)                       
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::AUDIO_GetFrequencyOffset(
        &settings->center_frequency_offset_hz);
    this->_api_error_check();
    this->_api_return_status = RSA_API::AUDIO_GetEnable(
        &settings->is_demodulating);
    this->_api_error_check();
    this->_api_return_status = RSA_API::AUDIO_GetMode(
        &settings->demodulation_mode_select);
    this->_api_error_check();
    this->_api_return_status = RSA_API::AUDIO_GetMute(
        &settings->is_mute);
    this->_api_error_check();
    this->_api_return_status = RSA_API::AUDIO_GetVolume(
        &settings->volume);
    this->_api_error_check();
    settings->data_length_received = this->_audio_type.data_length_received;
}


////~~~~


/*
    public < 3 >
    prepares requested audio settings
    a running device is stopped
    settings are validated by the setters
    reinforces new settings by getting
    internal struct is updated
*/
void rsa306b::audio_prepare
(
    audio_type* settings
)                       
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->device_stop();

    this->_gp_return_status = 
        this->_audio_set_center_frequency_offset(
            settings->center_frequency_offset_hz);
    this->_gp_error_check();
    if (this->_gp_return_status != this->CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror setting frequency offset\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_audio_set_demodulation_mode(
            settings->demodulation_mode_select);
    this->_gp_error_check();
    if (this->_gp_return_status != this->CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror setting demodulation mode\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_audio_set_mute_status(
            settings->is_mute);
    this->_gp_error_check();
    if (this->_gp_return_status != this->CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror in mute status\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_audio_set_volume(
            settings->volume);
    this->_gp_error_check();
    if (this->_gp_return_status != this->CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror setting volume\n");
        #endif
        return;
    }

    settings->data_length_received = this->_audio_type.data_length_received;
    this->audio_get_settings(settings);
    this->audio_get_settings(&this->_audio_type);
}


////~~~~


/*
    public < 4 >
    audio settings are verified
    demodulation is started and stopped
    aquisition is placed in public member "audio_data"
    elements aquired updated in "settings.data_length_received"
*/
void rsa306b::audio_get_data
(
    audio_type* settings
)                     
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->audio_prepare(settings);
    this->device_run();
    this->_api_return_status = RSA_API::AUDIO_Start();
    this->_api_error_check();

    this->_api_return_status = RSA_API::AUDIO_GetData(
        this->aduio_data, 
        AUDIO_DATA_LENGTH, 
        &this->_audio_type.data_length_received);

    this->_audio_type.data_length_received = settings->data_length_received;
    this->_api_return_status = RSA_API::AUDIO_Stop();
    this->_api_error_check();
    this->device_stop();
}


////////~~~~~~~~END>  rsa306b_class_AUDIO_public.cpp
