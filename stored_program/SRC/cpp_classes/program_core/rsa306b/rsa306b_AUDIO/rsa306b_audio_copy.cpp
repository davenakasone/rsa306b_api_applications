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

    constexpr int calls = 8;
    CODEZ caught_call[calls];

    caught_call[0] = this->_audio_copy_is_demodulating       ();
    caught_call[1] = this->_audio_copy_is_mute               ();
    caught_call[2] = this->_audio_copy_frequecny_offset_hz   ();
    caught_call[3] = this->_audio_copy_volume                ();
    caught_call[4] = this->_audio_copy_demodulation_select   ();
    caught_call[5] = this->_audio_copy_data                  ();
    caught_call[6] = this->_audio_copy_data_samples_requested();
    caught_call[7] = this->_audio_copy_data_samples_acquired ();

    return this->cutil.codez_checker(caught_call, calls);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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

    this->vars.audio.data_v.clear();
    this->vars.audio.data_v.resize(this->_vars.audio.data_v.size());
    this->vars.audio.data_v = this->_vars.audio.data_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}

////////~~~~~~~~END>  rsa306b_audio_copy.cpp
