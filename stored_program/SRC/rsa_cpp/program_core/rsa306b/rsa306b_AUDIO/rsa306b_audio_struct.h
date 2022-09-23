/*
    variables needed for the API group "AUDIO" 
        AUDIO_GetFrequencyOffset(), AUDIO_GetFrequencyOffset()
        AUDIO_GetEnable()
        AUDIO_GetData()           ,
        AUDIO_GetMode()           , AUDIO_SetMode()
        AUDIO_GetMute()           , AUDIO_SetMute()
        AUDIO_GetVolume()         , AUDIO_SetVolume()
        AUDIO_Start()
        AUDIO_Stop()

    active :
        double                  frequency_offset_hz
        bool                    is_demodulating
        std::vector<int16_t>    data_v                
        uint16_t                data_samples_requested
        uint16_t                data_samples_acquired
        RSA_API::AudioDemodMode demodulation_select
        bool                    is_mute                 
        float                   volume

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/


#ifndef H_rsa306b_audio_struct
#define H_rsa306b_audio_struct


#include "../../control/resourcez.h"


struct rsa306b_audio_struct
{


// limiting constants :
    const double   CENTER_FREQUENCY_OFFSET_MAX_HZ = 20e6;       // highest audio demodulator API accepts
    const double   CENTER_FREQUENCY_OFFSET_MIN_HZ = -20e6;      // highest audio demodulator API accepts
    const uint16_t DATA_V_MAX_LENGTH              = 0xFFFFU;    // maximum audio data points, 2^16 - 1
    const float    VOLUME_MAX                     = 1.0;        // maximum audio volume API will accept
    const float    VOLUME_MIN                     = 0.0;        // minimum audio volume API will accept


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
        is_demodulating ; true indicates if demodulation is occuring | false means no demodulation
*/
    bool       is_demodulating;
    const bool _IS_DEMODULATING = false;    // DEFAULT


/*
    AUDIO_GetData()
        must allocate int16_t array, place in STL for safety
            data_v                 ; holds the AUDIO data received
            data_samples_requested ; how many samples the user wants
            data_samples_acquired  ; how many audio data samples were actually acquired
        limited by:
            "DATA_V_MAX_LENGTH"
*/
    std::vector<int16_t> data_v;                               
    const int16_t        _DATA_V_element   = INIT_INT16;         // DEFAULT
    const std::size_t    _DATA_V_size      = INIT_STL_LENGTH;    // DEFAULT

    uint16_t       data_samples_requested;                  
    const uint16_t _DATA_SAMPLES_REQUESTED = INIT_UINT16;        // DEFAULT

    uint16_t       data_samples_acquired;                      
    const uint16_t _DATA_SAMPLES_ACQUIRED  = INIT_UINT16;        // DEFAULT

        
/*
    AUDIO_GetMode(), AUDIO_SetMode()
        demodulation_select ; the demodulation type that will be applied
*/
    RSA_API::AudioDemodMode       demodulation_select;
    const RSA_API::AudioDemodMode _DEMODULATION_SELECT = RSA_API::AudioDemodMode::ADM_AM_8KHZ;    // DEFAULT


/*
    AUDIO_GetMute(), AUDIO_GetMute()
        get/set mute status of output speakers
        does not effect audio data acquisition
        "true" means speakers are mute        ...set "true", the speakers are disabled
        "false" means speakers are not mute   ...set "false", the speakers make sound
*/
    bool       is_mute;                  
    const bool _IS_MUTE = false;    // DEFAULT


/*
    AUDIO_GetVolume(), AUDIO_SetVolume()
        if volume goes out of range, it might be clipped
        volume ; detrmines output volume level
        limited by:
            "AUDIO_VOLUME_MIN"
            "AUDIO_VOLUME_MAX"

*/
    float       volume;              
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


};
typedef struct rsa306b_audio_struct rsa306b_audio_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h                
   