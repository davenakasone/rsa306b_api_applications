/*
    API group "AUDIO", getters

    public :
        #  none
    
    private :
        < 1 >  _audio_get_vars()
        < 2 >  _audio_get_is_demodulating()
        < 3 >  _audio_get_is_mute()
        < 4 >  _audio_get_frequency_offset_hz()
        < 5 >  _audio_get_volume()
        < 6 >  _audio_get_demodulation_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_audio_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_audio_get_is_demodulating    ();
    caught_call[1] = this->_audio_get_is_mute            ();
    caught_call[2] = this->_audio_get_frequency_offset_hz();
    caught_call[3] = this->_audio_get_volume             ();
    caught_call[4] = this->_audio_get_demodulation_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_audio_get_is_demodulating()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_api_status = 
        RSA_API::AUDIO_GetEnable
        (
            &this->_vars.audio.is_demodulating
        );
    (void)this->_audio_copy_is_demodulating();
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_audio_get_is_mute()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_api_status = 
        RSA_API::AUDIO_GetMute
        (
            &this->_vars.audio.is_mute
        );
    (void)this->_audio_copy_is_mute();
    return this->_report_api_status();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_audio_get_frequency_offset_hz()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_api_status = 
        RSA_API::AUDIO_GetFrequencyOffset
        (
            &this->_vars.audio.frequency_offset_hz
        );
    (void)this->_audio_copy_frequecny_offset_hz();
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_audio_get_volume()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_api_status = 
        RSA_API::AUDIO_GetVolume
        (
            &this->_vars.audio.volume
        );
    (void)this->_audio_copy_volume();
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_audio_get_demodulation_select()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_api_status = 
        RSA_API::AUDIO_GetMode
        (
            &this->_vars.audio.demodulation_select
        );
    (void)this->_audio_copy_demodulation_select();
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_audio_get.cpp
