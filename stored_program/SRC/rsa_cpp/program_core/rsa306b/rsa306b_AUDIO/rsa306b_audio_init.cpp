/*
    API group "AUDIO"

    public :
        #  none
    
    private :
        < 1 >  _audio_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    initialize "AUDIO" group variables to known values
*/
CODEZ rsa306b_class::_audio_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.audio.data_v.assign(this->_vars.audio._DATA_V_size, this->_vars.audio._DATA_V_element);
    
    this->_vars.audio.data_samples_acquired  = this->_vars.audio._DATA_SAMPLES_ACQUIRED;
    this->_vars.audio.data_samples_requested = this->_vars.audio._DATA_SAMPLES_REQUESTED;
    this->_vars.audio.demodulation_select    = this->_vars.audio._DEMODULATION_SELECT;
    this->_vars.audio.frequency_offset_hz    = this->_vars.audio._FREQUENCY_OFFSET_HZ;
    this->_vars.audio.is_demodulating        = this->_vars.audio._IS_DEMODULATING;
    this->_vars.audio.is_mute                = this->_vars.audio._IS_MUTE;
    this->_vars.audio.volume                 = this->_vars.audio._VOLUME;

    return this->_audio_copy_vars();
}


////////~~~~~~~~END>  rsa306b_audio_init.cpp    
