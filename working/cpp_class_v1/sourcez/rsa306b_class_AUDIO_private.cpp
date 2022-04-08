/*
    implementation of the rsa306b_class
    using "AUDIO" function group of the API
    setters

        public:
            #  none

        private:
            < 1 >  _audio_set_center_frequency_offset()
            < 2 >  _audio_set_demodulation_mode()
            < 3 >  _audio_set_mute_status()
            < 4 >  _audio_set_volume()
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    sets the offset from center frequency
    desired setting is range checked
*/
int rsa306b::_audio_set_center_frequency_offset
(
    double cf_offset
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
        return CALL_FAILURE;
    }
    if (cf_offset > this->AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz ||
        cf_offset < this->AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tfrequency offset:  %lf  ,  out of range [ %lf : %lf ]\n",
                cf_offset,
                this->AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz,
                this->AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
        #endif
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::AUDIO_SetFrequencyOffset(cf_offset);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set audio center frequency offset\n");
        #endif
        return CALL_FAILURE;
    }
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 2 >
    sets desired demodulation mode 
    setting is validated
*/
int rsa306b::_audio_set_demodulation_mode
(
    RSA_API::AudioDemodMode mode
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
        return CALL_FAILURE;
    }
    if (mode != RSA_API::ADM_FM_8KHZ   &&
        mode != RSA_API::ADM_FM_13KHZ  &&
        mode != RSA_API::ADM_FM_75KHZ  &&
        mode != RSA_API::ADM_FM_200KHZ &&
        mode != RSA_API::ADM_AM_8KHZ    )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid mode\n");
        #endif
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::AUDIO_SetMode(mode);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set demodulation mode\n");
        #endif
        return CALL_FAILURE;
    }
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 3 >
    sets the mute status to desired setting
*/
int rsa306b::_audio_set_mute_status
(
    bool new_value
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
        return CALL_FAILURE;
    }
    bool temp;
    this->_api_return_status = RSA_API::AUDIO_GetMute(&temp);
    this->_api_error_check();
    if (new_value != temp)
    {
        this->_api_return_status = RSA_API::AUDIO_SetMute(new_value);
        this->_api_error_check();
    }
    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the mute status\n");
        #endif
        return CALL_FAILURE;
    }
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 4 >
*/
int rsa306b::_audio_set_volume
(
    float new_value
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
        return CALL_FAILURE;
    }
    if (new_value > this->AUDIO_VOLUME_MAX ||
        new_value < this->AUDIO_VOLUME_MIN  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tvolume:  %f  ,  out of range [ %f , %f ]\n",
                new_value,
                this->AUDIO_VOLUME_MIN,
                this->AUDIO_VOLUME_MAX);
        #endif
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::AUDIO_SetVolume(new_value);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the volume\n");
        #endif
        return CALL_FAILURE;
    }
    return CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_class_AUDIO_private.cpp
