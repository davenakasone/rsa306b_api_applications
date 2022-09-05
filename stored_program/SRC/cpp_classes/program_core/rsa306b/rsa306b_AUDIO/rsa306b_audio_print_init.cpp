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
void rsa306b_class::print_audio()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'AUDIO' group >>>\n");
    printf("\tis demodulationg        :  %d\n", this->_vars.audio.is_demodulating);
    printf("\tis mute                 :  %d\n", this->_vars.audio.is_mute);
    printf("\tfrequency offset (Hz)   :  %lf\n", this->_vars.audio.frequency_offset_hz);
    printf("\tvolume                  :  %f\n", this->_vars.audio.volume);
    printf("\tdemodulation mode       :  ");
    switch (this->_vars.audio.demodulation_select)
    {
        case (RSA_API::ADM_FM_8KHZ)   : printf("FM, 8 kHz\n");   break;
        case (RSA_API::ADM_FM_13KHZ)  : printf("FM, 13 kHz\n");  break;
        case (RSA_API::ADM_FM_75KHZ)  : printf("FM, 75 kHz\n");  break;
        case (RSA_API::ADM_FM_200KHZ) : printf("FM, 200 kHz\n"); break;
        case (RSA_API::ADM_AM_8KHZ)   : printf("FM, 8 kHz\n");   break;
        default                       : printf("unknown\n");     break;
    }
    printf("\tdata[0]                 :  %d\n", this->_vars.audio.data[0]);
    printf("\tdata samples requested  :  %u\n", this->_vars.audio.data_samples_requested);
    printf("\tdata samples aquired    :  %u\n", this->_vars.audio.data_samples_acquired);
}


////~~~~


/*
    < 1 > private
    initialize "AUDIO" group variables to known values
*/
void rsa306b_class::_audio_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < AUDIO_DATA_LENGTH; ii++)
    {
        this->_vars.audio.data[ii] = this->constants.INIT_INT;
    }

    this->_vars.audio.data_samples_acquired = 0;
    this->_vars.audio.data_samples_requested = AUDIO_DATA_LENGTH;
    this->_vars.audio.demodulation_select = RSA_API::ADM_AM_8KHZ;
    this->_vars.audio.frequency_offset_hz = this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz;
    this->_vars.audio.is_demodulating = false;
    this->_vars.audio.is_mute = true;
    this->_vars.audio.volume = this->constants.AUDIO_VOLUME_MIN;

    this->_audio_copy_vars();
}


////////~~~~~~~~END>  rsa306b_audio_print_init.cpp
