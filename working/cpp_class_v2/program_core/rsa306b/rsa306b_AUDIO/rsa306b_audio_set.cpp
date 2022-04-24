/*
    API group "ADUIO", setters
    setting occurs through the public struct
    setting of the private struct does not occur until new value is validated

    public :
        #  none
    
    private :
        < 1 >  _audio_set_vars()
        < 2 >  _audio_set_is_mute()
        < 3 >  _audio_set_frequency_offset_hz()
        < 4 >  _audio_set_volume()
        < 5 >  _audio_set_demodulation_select()
        < 6 >  _audio_set_data_samples_requested()

*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    calls the API setters if the device is conected
*/
int rsa306b_class::_audio_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.call_status = this->_audio_set_is_mute();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_audio_set_frequency_offset_hz();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_audio_set_volume();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_audio_set_demodulation_select();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_audio_set_data_samples_requested();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    return this->_vars.constants.CALL_SUCCESS;
}


////~~~~


/*
    < 2 > private
    the API call is made if the device is connected
        and the user value is different than the current value
*/
int rsa306b_class::_audio_set_is_mute()
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
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.audio.is_mute == this->_vars.audio.is_mute)
    {
        #ifdef DEBUG_MIN
            printf("\n\taudio already muted\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::AUDIO_SetMute(&this->vars.audio.is_mute);
    this->_gp_confirm_api_status();
    this->_audio_get_is_mute();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 3 > private
*/
int rsa306b_class::_audio_set_frequency_offset_hz()
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
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.audio.frequency_offset_hz < this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz ||
        this->vars.audio.frequency_offset_hz > this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz  )
    {
        #ifdef DEBUG_MIN
            printf("\n\taudio frequency offset { %lf }  ,  out of range [ %lf , %lf ]\n",
                this->vars.audio.frequency_offset_hz,
                this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz,
                this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::AUDIO_SetFrequencyOffset(this->vars.audio.frequency_offset_hz);
    this->_gp_confirm_api_status();
    this->_audio_get_frequency_offset_hz();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 4 > private
*/
int rsa306b_class::_audio_set_volume()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.audio.volume < this->_vars.constants.AUDIO_VOLUME_MIN ||
        this->vars.audio.volume > this->_vars.constants.AUDIO_VOLUME_MAX  )
    {
        #ifdef DEBUG_MAX
            printf("\n\taudio volume { %f }  ,  out of range [ %f , %f ]\n",
                this->vars.audio.volume,
                this->_vars.constants.AUDIO_VOLUME_MIN,
                this->_vars.constants.AUDIO_VOLUME_MAX);
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::AUDIO_SetVolume(this->vars.audio.volume);
    this->_gp_confirm_api_status();
    this->_audio_get_volume();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 5 > private
*/
int rsa306b_class::_audio_set_demodulation_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.audio.demodulation_select != RSA_API::ADM_FM_8KHZ   &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_13KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_75KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_200KHZ &&
        this->vars.audio.demodulation_select != RSA_API::ADM_AM_8KHZ    )
    {
        #ifdef DEBUG_MAX
            printf("\n\tinvalid demodulation mode selected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::AUDIO_SetMode(this->vars.audio.demodulation_select);
    this->_gp_confirm_api_status();
    this->_audio_get_demodulation_select();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 6 > private
*/
int rsa306b_class::_audio_set_data_samples_requested()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.audio.data_samples_requested < 1                   ||
        this->vars.audio.data_samples_requested > AUDIO_DATA_LENGTH_MAX)
    {
        #ifdef DEBUG_MAX
            printf("\n\tsamples requested { %u }  ,  out of range [ 1 , %d ]\n",
                this->vars.audio.data_samples_requested,
                AUDIO_DATA_LENGTH_MAX);
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    
    this->_vars.audio.data_samples_requested = 
        this->vars.audio.data_samples_requested;
    return this->_vars.constants.CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_audio_set.cpp
