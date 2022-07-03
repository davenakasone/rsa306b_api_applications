/*
    variables needed for the API group "AUDIO" 
*/

#ifndef H_rsa306b_audio_struct
#define H_rsa306b_audio_struct


#include "../rsa306b_constants.h"


struct rsa306b_audio_struct
{
   bool is_demodulating;                           // indicates if demodulation is occuring
   bool is_mute;                                   // indicates if speaker output is muted
   double frequency_offset_hz;                     // audio frequency offset from center frequency, in Hz
   float volume;                                   // must be [0:1], the output volume level
   RSA_API::AudioDemodMode demodulation_select;    // determines type of demodulation
   int16_t data[AUDIO_DATA_LENGTH];                // holds audio data
   uint16_t data_samples_requested;                // how many audio data samples to get
   uint16_t data_samples_acquired;                 // how many audio data samples were processed
};
typedef struct rsa306b_audio_struct rsa306b_audio_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
