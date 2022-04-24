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
void rsa306b_class::audio_set_vars()
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
        return;
    }

    this->_vars.gp.call_status = this->_audio_set_vars();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\terror setting audio parameters\n");
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
void rsa306b_class::audio_acquire_data()
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
        return;
    }

    this->_vars.audio.data_samples_output = 0;
    this->device_run();
    this->_vars.gp.api_status = RSA_API::AUDIO_Start();
    this->_gp_confirm_api_status();
    this->_vars.audio.is_demodulating = true;

    this->_vars.gp.api_status = RSA_API::AUDIO_GetData(
        this->_vars.audio.data, 
        this->_vars.audio.data_samples_requested, 
        &this->_vars.audio.data_samples_output);
    this->_gp_confirm_api_status();
    this->_audio_get_data();

    this->_vars.gp.api_status = RSA_API::AUDIO_Stop();
    this->_vars.audio.is_demodulating = false;
    this->_gp_confirm_api_status();
    this->device_stop();
}


////////~~~~~~~~END>  rsa306b_audio_user.cpp
