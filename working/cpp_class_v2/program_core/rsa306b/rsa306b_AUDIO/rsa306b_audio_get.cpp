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
void rsa306b_class::_audio_get_vars()
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
void rsa306b_class::_audio_get_is_demodulating()
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
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetEnable(&this->_vars.audio.is_demodulating);
    this->_gp_confirm_api_status();
    this->_audio_copy_is_demodulating();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_audio_get_is_mute()
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
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetMute(&this->_vars.audio.is_mute);
    this->_gp_confirm_api_status();
    this->_audio_copy_is_mute();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_audio_get_frequency_offset_hz()
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
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetFrequencyOffset(&this->_vars.audio.frequency_offset_hz);
    this->_gp_confirm_api_status();
    this->_audio_copy_frequecny_offset_hz();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_audio_get_volume()
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
    this->_vars.gp.api_status = 
        RSA_API::AUDIO_GetVolume(&this->_vars.audio.volume);
    this->_gp_confirm_api_status();
    this->_audio_copy_volume();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_audio_get_demodulation_select()
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
void rsa306b_class::_audio_get_data()
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
    if (this->_vars.audio.is_demodulating == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\taudio demodulation was not activated\n");
        #endif
        return;
    }
    this->_audio_copy_data_samples_acquired();
    
    if (this->_vars.audio.data_samples_acquired == 0)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno audio data was acquired\n");
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
