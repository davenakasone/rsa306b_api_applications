/*
    API group "AUDIO"

    public :
        < 1 >  print_audio()
    
    private :
        < 1 >  _audio_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    print "AUDIO" group variables to stdout
*/
CODEZ rsa306b_class::audio_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'AUDIO' group >>>\n");
    (void)printf("\tis demodulationg        :  %d\n", this->_vars.audio.is_demodulating);
    (void)printf("\tis mute                 :  %d\n", this->_vars.audio.is_mute);
    (void)printf("\tfrequency offset (Hz)   :  %lf\n", this->_vars.audio.frequency_offset_hz);
    (void)printf("\tvolume                  :  %f\n", this->_vars.audio.volume);
    (void)printf("\tdemodulation mode       :  ");
    switch (this->_vars.audio.demodulation_select)
    {
        case (RSA_API::ADM_FM_8KHZ)   : (void)printf("FM, 8 kHz\n");   break;
        case (RSA_API::ADM_FM_13KHZ)  : (void)printf("FM, 13 kHz\n");  break;
        case (RSA_API::ADM_FM_75KHZ)  : (void)printf("FM, 75 kHz\n");  break;
        case (RSA_API::ADM_FM_200KHZ) : (void)printf("FM, 200 kHz\n"); break;
        case (RSA_API::ADM_AM_8KHZ)   : (void)printf("FM, 8 kHz\n");   break;
        default                       : (void)printf("unknown\n");     break;
    }
    (void)printf("\tdata[0]                 :  %d\n", this->_vars.audio.data_v[0]);
    (void)printf("\tdata samples requested  :  %u\n", this->_vars.audio.data_samples_requested);
    (void)printf("\tdata samples aquired    :  %u\n", this->_vars.audio.data_samples_acquired);

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


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


////////~~~~~~~~END>  rsa306b_audio_print_init.cpp
