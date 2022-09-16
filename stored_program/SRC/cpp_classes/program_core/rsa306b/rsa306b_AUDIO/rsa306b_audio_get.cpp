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
        < 7 >  _audio_get_data()
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_audio_get_is_demodulating();
    this->_audio_get_is_mute();
    this->_audio_get_frequency_offset_hz();
    this->_audio_get_volume();
    this->_audio_get_demodulation_select();
    this->_audio_get_data();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetEnable(&this->_vars.audio.is_demodulating);
    this->_gp_confirm_api_status();
    this->_audio_copy_is_demodulating();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetMute(&this->_vars.audio.is_mute);
    this->_gp_confirm_api_status();
    this->_audio_copy_is_mute();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetFrequencyOffset(&this->_vars.audio.frequency_offset_hz);
    this->_gp_confirm_api_status();
    this->_audio_copy_frequecny_offset_hz();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetVolume(&this->_vars.audio.volume);
    this->_gp_confirm_api_status();
    this->_audio_copy_volume();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetMode(&this->_vars.audio.demodulation_select);
    this->_gp_confirm_api_status();
    this->_audio_copy_demodulation_select();
}


////~~~~


/*
    < 7 > private
    does not use an API call
    populates the user's struct after aquiring audio data
*/
CODEZ rsa306b_class::_audio_get_data()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->_vars.audio.is_demodulating == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "audio demodulation was not activated");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_audio_copy_data_samples_acquired();
    
    if (this->_vars.audio.data_samples_acquired == 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "no audio data was acquired");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    for (int ii = 0; ii < this->_vars.audio.data_samples_acquired; ii++)
    {
        this->vars.audio.data[ii] = this->_vars.audio.data[ii];
    }
    this->vars.audio.data_samples_acquired = this->_vars.audio.data_samples_acquired;
}


////////~~~~~~~~END>  rsa306b_audio_get.cpp
