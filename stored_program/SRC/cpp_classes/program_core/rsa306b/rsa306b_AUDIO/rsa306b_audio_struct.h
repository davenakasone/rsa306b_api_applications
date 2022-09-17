/*
    variables needed for the API group "AUDIO" 

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
*/


#ifndef H_rsa306b_audio_struct
#define H_rsa306b_audio_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_audio_struct
{
/*
    AUDIO_GetFrequencyOffset(), AUDIO_SetFrequencyOffset()
        get/set the demodulation carrier frequency offset from center frequency, in Hz
        limited by:
            "CENTER_FREQUENCY_OFFSET_MIN_HZ"
            "CENTER_FREQUENCY_OFFSET_MAX_HZ"
*/
    double         frequency_offset_hz;
    const double   _FREQUENCY_OFFSET_HZ = INIT_DOUBLE;    // DEFAULT


/*
    AUDIO_GetEnable()
        "true" indicates if demodulation is occuring
*/
    bool       is_demodulating;
    const bool _IS_DEMODULATING = false;    // DEFAULT


/*
    AUDIO_GetData()
        must allocate int16_t array, place in STL for safety
        limited by:
            "DATA_V_MAX_LENGTH"
*/
    std::vector<int16_t> data_v;                               // holds the AUDIO data received
    const int16_t        _DATA_V_element = INIT_INT16;         // DEFAULT, element value
    const std::size_t    _DATA_V_size    = INIT_STL_LENGTH;    // DEFAULT, number of elements

    uint16_t       data_samples_requested;                     // how many samples the user wants 
    const uint16_t _DATA_SAMPLES_REQUESTED = INIT_UINT16;      // DEFAULT

    uint16_t       data_samples_acquired;                      // how many audio data samples were actually acquired
    const uint16_t _DATA_SAMPLES_ACQUIRED = INIT_UINT16;       // DEFAULT

        
/*
    AUDIO_GetMode()
        the demodulation type that will be applied
*/
    RSA_API::AudioDemodMode       demodulation_select;                                            // determines type of demodulation
    const RSA_API::AudioDemodMode _DEMODULATION_SELECT = RSA_API::AudioDemodMode::ADM_AM_8KHZ;    // DEFAULT


/*
    AUDIO_GetMute(), AUDIO_GetMute()
        get/set mute status of output speakers
        does not effect audio data acquisition
        "true" means speakers are mute        ...set "true", the speakers are disabled
        "false" means speakers are not mute   ...set "false", the speakers make sound
*/
    bool is_mute;                  
    const bool _IS_MUTE = false;    // DEFAULT


/*
    AUDIO_SetVolume()
        sets the volume
        if volume goes out of range, it might be clipped
        limited by:
            "AUDIO_VOLUME_MIN"
            "AUDIO_VOLUME_MAX"

*/
    float       volume;                  // output volume level
    const float _VOLUME = INIT_FLOAT;    // DEFAULT


/*
    AUDIO_Start()
        start audio demodulation output generation
        call before trying to get data
*/



/*
    AUDIO_Stop()
        stops audio demodulation output generation
        call after data was received
*/


// limiting constants :
    const double   CENTER_FREQUENCY_OFFSET_MAX_HZ = 20e6;       // highest audio demodulator API accepts
    const double   CENTER_FREQUENCY_OFFSET_MIN_HZ = -20e6;      // highest audio demodulator API accepts
    const uint16_t DATA_V_MAX_LENGTH              = 0xFFFFU;    // maximum audio data points, 2^16 - 1
    const float    VOLUME_MAX                     = 1.0;        // maximum audio volume API will accept
    const float    VOLUME_MIN                     = 0.0;        // minimum audio volume API will accept


};
typedef struct rsa306b_audio_struct rsa306b_audio_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
