/*
    API group "ADUIO", setters
    setting occurs through the public struct
    setting of the private struct does not occur until new value is validated

    public :
        < 1 >  audio_set_vars()
    
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
    < 1 > public
    user updates variables of the public struct
    new values are set in the class if they are valid
        and no API error occurs while setting
*/
CODEZ rsa306b_class::audio_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_audio_set_vars();
}


////~~~~ 


/*
    < 1 > private
    calls the API setters if the device is conected
*/
CODEZ rsa306b_class::_audio_set_vars()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_audio_set_is_mute               ();
    caught_call[1] = this->_audio_set_frequency_offset_hz   ();
    caught_call[2] = this->_audio_set_volume                ();
    caught_call[3] = this->_audio_set_demodulation_select   ();
    caught_call[4] = this->_audio_set_data_samples_requested();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
    the API call is made if the device is connected
        and the user value is different than the current value
*/
CODEZ rsa306b_class::_audio_set_is_mute()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }

    (void)this->device_stop();
    RSA_API::ReturnStatus temp = 
        RSA_API::AUDIO_SetMute(&this->vars.audio.is_mute);
    (void)this->_audio_get_is_mute();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_audio_set_frequency_offset_hz()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.audio.frequency_offset_hz < this->_vars.audio.CENTER_FREQUENCY_OFFSET_MIN_HZ ||
        this->vars.audio.frequency_offset_hz > this->_vars.audio.CENTER_FREQUENCY_OFFSET_MAX_HZ  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "audio frequency offset { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.audio.frequency_offset_hz,
                this->_vars.audio.CENTER_FREQUENCY_OFFSET_MIN_HZ,
                this->_vars.audio.CENTER_FREQUENCY_OFFSET_MAX_HZ);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)this->device_stop();
    RSA_API::ReturnStatus temp = 
        RSA_API::AUDIO_SetFrequencyOffset(this->vars.audio.frequency_offset_hz);
    (void)this->_audio_get_frequency_offset_hz();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_audio_set_volume()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.audio.volume < this->_vars.audio.VOLUME_MIN ||
        this->vars.audio.volume > this->_vars.audio.VOLUME_MAX  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "audio volume { %f }  ,  out of range [ %f , %f ]",
                this->vars.audio.volume,
                this->_vars.audio.VOLUME_MIN,
                this->_vars.audio.VOLUME_MAX);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    
    (void)this->device_stop();
    RSA_API::ReturnStatus temp = 
        RSA_API::AUDIO_SetVolume(this->vars.audio.volume);
    (void)this->_audio_get_volume();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_audio_set_demodulation_select()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    
    if (this->vars.audio.demodulation_select != RSA_API::ADM_FM_8KHZ   &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_13KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_75KHZ  &&
        this->vars.audio.demodulation_select != RSA_API::ADM_FM_200KHZ &&
        this->vars.audio.demodulation_select != RSA_API::ADM_AM_8KHZ    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid demodulation mode selected:  %d",
                static_cast<int>(this->vars.audio.demodulation_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)this->device_stop();
    RSA_API::ReturnStatus temp = 
        RSA_API::AUDIO_SetMode(this->vars.audio.demodulation_select);
    (void)this->_audio_get_demodulation_select();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_audio_set_data_samples_requested()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.audio.data_samples_requested < 1                                 ||
        this->vars.audio.data_samples_requested > this->_vars.audio.DATA_V_MAX_LENGTH)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "samples requested { %u }  ,  out of range [ 1 , %u ]",
                this->vars.audio.data_samples_requested,
                this->_vars.audio.DATA_V_MAX_LENGTH);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    this->_vars.audio.data_samples_requested = this->vars.audio.data_samples_requested;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_audio_set.cpp
