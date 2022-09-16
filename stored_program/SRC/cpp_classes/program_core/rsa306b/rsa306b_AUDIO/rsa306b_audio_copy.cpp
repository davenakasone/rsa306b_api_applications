/*
    API group "AUDIO", copiers

    public :
        #  none
    
    private :
        < 1 >  _audio_copy_vars()
        < 2 >  _audio_copy_is_demodulating()
        < 3 >  _audio_copy_is_mute()
        < 4 >  _audio_copy_frequecny_offset_hz()
        < 5 >  _audio_copy_volume()
        < 6 >  _audio_copy_demodulation_select()
        < 7 >  _audio_copy_data()
        < 8 >  _audio_copy_data_samples_requested()
        < 9 >  _aduio_copy_data_samples_acquired()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_audio_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_audio_copy_is_demodulating();
    this->_audio_copy_is_mute();
    this->_audio_copy_frequecny_offset_hz();
    this->_audio_copy_volume();
    this->_audio_copy_demodulation_select();
    this->_audio_copy_data();
    this->_audio_copy_data_samples_requested();
    this->_audio_copy_data_samples_acquired();
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_audio_copy_is_demodulating()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.is_demodulating = this->_vars.audio.is_demodulating;
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_audio_copy_is_mute()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.is_mute = this->_vars.audio.is_mute;
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_audio_copy_frequecny_offset_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.frequency_offset_hz = this->_vars.audio.frequency_offset_hz;
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_audio_copy_volume()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.volume = this->_vars.audio.volume;
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_audio_copy_demodulation_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.demodulation_select = this->_vars.audio.demodulation_select;
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_audio_copy_data()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    for (int ii = 0; ii < AUDIO_DATA_LENGTH; ii++)
    {
        this->_vars.audio.data[ii] = this->_vars.audio.data[ii];
    }
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_audio_copy_data_samples_requested()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.data_samples_requested = this->_vars.audio.data_samples_requested;
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_audio_copy_data_samples_acquired()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.audio.data_samples_acquired = this->_vars.audio.data_samples_acquired;
}

////////~~~~~~~~END>  rsa306b_audio_copy.cpp
