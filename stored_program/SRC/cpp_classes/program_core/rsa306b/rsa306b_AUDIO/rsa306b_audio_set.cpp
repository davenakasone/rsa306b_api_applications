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
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    // vars.audio.is_mute
    if (this->vars.audio.is_mute != this->_vars.audio.is_mute)
    {
        if (this->_audio_set_is_mute() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.audio.frequency_offset_hz
    if (this->vars.audio.frequency_offset_hz != this->_vars.audio.frequency_offset_hz)
    {
        if (this->_audio_set_frequency_offset_hz() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.audio.volume
    if (this->vars.audio.volume != this->_vars.audio.volume)
    {
        if (this->_audio_set_volume() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.audio.demodulation_select
    if (this->vars.audio.demodulation_select != this->_vars.audio.demodulation_select)
    {
        if (this->_audio_set_demodulation_select() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.data_samples_requested
    if (this->vars.audio.data_samples_requested != this->_vars.audio.data_samples_requested)
    {
        if (this->_audio_set_data_samples_requested() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    
    return this->constants.CALL_SUCCESS;
}


////~~~~


/*
    < 2 > private
    the API call is made if the device is connected
        and the user value is different than the current value
*/
int rsa306b_class::_audio_set_is_mute()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
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
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.audio.frequency_offset_hz < this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz ||
        this->vars.audio.frequency_offset_hz > this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "audio frequency offset { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.audio.frequency_offset_hz,
                this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz,
                this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
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
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.audio.volume < this->constants.AUDIO_VOLUME_MIN ||
        this->vars.audio.volume > this->constants.AUDIO_VOLUME_MAX  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "audio volume { %f }  ,  out of range [ %f , %f ]",
                this->vars.audio.volume,
                this->constants.AUDIO_VOLUME_MIN,
                this->constants.AUDIO_VOLUME_MAX);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
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
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.audio.demodulation_select != RSA_API::ADM_FM_8KHZ   &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_13KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_75KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_200KHZ &&
        this->vars.audio.demodulation_select != RSA_API::ADM_AM_8KHZ    )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid demodulation mode selected:  %d",
                static_cast<int>(this->vars.audio.demodulation_select));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
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
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.audio.data_samples_requested < 1               ||
        this->vars.audio.data_samples_requested > AUDIO_DATA_LENGTH)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "samples requested { %u }  ,  out of range [ 1 , %d ]",
                this->vars.audio.data_samples_requested,
                AUDIO_DATA_LENGTH);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.audio.data_samples_requested = 
        this->vars.audio.data_samples_requested;
    return this->constants.CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_audio_set.cpp
