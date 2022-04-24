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
        < 9 >  _aduio_copy_data_samples_output()

*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_audio_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_audio_copy_is_demodulating();
    this->_audio_copy_is_mute();
    this->_audio_copy_frequecny_offset_hz();
    this->_audio_copy_volume();
    this->_audio_copy_demodulation_select();
    this->_audio_copy_data();
    this->_audio_copy_data_samples_requested();
    this->_audio_copy_data_samples_output();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_audio_copy_is_demodulating()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.is_demodulating = this->_vars.audio.is_demodulating;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_audio_copy_is_mute()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.is_mute = this->_vars.audio.is_mute;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_audio_copy_frequecny_offset_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.frequency_offset_hz = this->_vars.audio.frequency_offset_hz;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_audio_copy_volume()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.volume = this->_vars.audio.volume;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_audio_copy_demodulation_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.demodulation_select = this->_vars.audio.demodulation_select;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_audio_copy_data()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < AUDIO_DATA_LENGTH_MAX; ii++)
    {
        this->_vars.audio.data[ii] = this->_vars.audio.data[ii];
    }
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_audio_copy_data_samples_requested()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.data_samples_requested = this->_vars.audio.data_samples_requested;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_audio_copy_data_samples_output()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.audio.data_samples_output = this->_vars.audio.data_samples_output;
}

////////~~~~~~~~END>  rsa306b_audio_copy.cpp
