/*
    API group "AUDIO", user functions

    public :
        < 1 >  audio_set_vars()
        < 2 >  audio_acquire_data()
    
    private :
        #  none
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }

    this->_vars.gp.call_status = this->_audio_set_vars();
    this->_gp_copy_call_status();
    if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "error setting AUDIO group");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
}


////~~~~


/*
    < 2 > public
    should be called after setting "AUDIO" group parameters
    automatic run/stop and start/stop is used
    public struct is updated if audio data samples are acquired
*/
CODEZ rsa306b_class::audio_acquire_data()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->_vars.audio.data_samples_requested < 1 ||
        this->_vars.audio.data_samples_requested > AUDIO_DATA_LENGTH)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "samples requested { %u }  ,  out of range [ 1 , %d ]",
                this->_vars.audio.data_samples_requested,
                AUDIO_DATA_LENGTH);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.audio.data_samples_acquired = 0;
    this->device_run();

    this->_audio_get_is_demodulating();
    if (this->_vars.audio.is_demodulating == false)
    {
        this->_vars.gp.api_status = RSA_API::AUDIO_Start();
        this->_gp_confirm_api_status();
    }
    this->_audio_get_is_demodulating();

    this->_vars.gp.api_status = RSA_API::AUDIO_GetData(
        this->_vars.audio.data, 
        this->_vars.audio.data_samples_requested, 
        &this->_vars.audio.data_samples_acquired);
    this->_gp_confirm_api_status();
    this->_audio_get_data();
    
    this->device_stop();
    this->_vars.gp.api_status = RSA_API::AUDIO_Stop();
    this->_audio_get_is_demodulating();
    this->_gp_confirm_api_status();
}


////////~~~~~~~~END>  rsa306b_audio_user.cpp
