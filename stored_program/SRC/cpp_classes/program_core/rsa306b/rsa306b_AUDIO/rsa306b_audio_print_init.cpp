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
CODEZ rsa306b_class::print_audio()
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
    (void)printf("\tdata[0]                 :  %d\n", this->_vars.audio.data[0]);
    (void)printf("\tdata samples requested  :  %u\n", this->_vars.audio.data_samples_requested);
    (void)printf("\tdata samples aquired    :  %u\n", this->_vars.audio.data_samples_acquired);
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

    for (int ii = 0; ii < AUDIO_DATA_LENGTH; ii++)
    {
        this->_vars.audio.data[ii] = INIT_INT;
    }

    this->_vars.audio.data_samples_acquired  = 0;
    this->_vars.audio.data_samples_requested = AUDIO_DATA_LENGTH;
    this->_vars.audio.demodulation_select    = RSA_API::ADM_AM_8KHZ;
    this->_vars.audio.frequency_offset_hz    = this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz;
    this->_vars.audio.is_demodulating        = false;
    this->_vars.audio.is_mute                = true;
    this->_vars.audio.volume                 = this->constants.AUDIO_VOLUME_MIN;

    this->_audio_copy_vars();
}


////////~~~~~~~~END>  rsa306b_audio_print_init.cpp
