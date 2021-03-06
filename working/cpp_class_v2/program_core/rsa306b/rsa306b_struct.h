/*
    the member variables for the "rsa306b" class are contained
    API function group variables are composed into a master variable struct

    this master struct is provided as a public and private member to the class
    together, the public and private instance create the basis for the 3/4 buffer

    generally, user is free to manipulate the public instance of the struct
    the private struct instance only updates if a correct value is provided

    struct for the "GP" group is the only non API variable contanier
    the class contains several variables outside of these structs 
        becuase the user has no need to touch them
*/

#ifndef H_rsa306b_struct
#define H_rsa306b_struct


#include "./rsa306b_GP/rsa306b_gp_struct.h"
#include "./rsa306b_ALIGN/rsa306b_align_struct.h"
#include "./rsa306b_AUDIO/rsa306b_audio_struct.h"
#include "./rsa306b_CONFIG/rsa306b_config_struct.h"
#include "./rsa306b_DEVICE/rsa306b_device_struct.h"
#include "./rsa306b_IFSTREAM/rsa306b_ifstream_struct.h"
#include "./rsa306b_IQBLK/rsa306b_iqblk_struct.h"
#include "./rsa306b_IQSTREAM/rsa306b_iqstream_struct.h"
#include "./rsa306b_REFTIME/rsa306b_reftime_struct.h"
#include "./rsa306b_SPECTRUM/rsa306b_spectrum_struct.h"
#include "./rsa306b_TRIG/rsa306b_trig_struct.h"


struct rsa306b_struct
{
    rsa306b_gp_struct gp;                 // common use class variables "general purpose"

    rsa306b_align_struct align;           // API group "ALIGN" variables

    rsa306b_audio_struct audio;           // API group "AUDIO" variables
    
    rsa306b_config_struct config;         // API group "CONFIG" variables

    rsa306b_device_struct device;         // API group "DEVICE" variables

    rsa306b_ifstream_struct ifstream;     // API group "IFSTREAM" variables

    rsa306b_iqblk_struct iqblk;           // API group "IQBLK" variables

    rsa306b_iqstream_struct iqstream;     // API group "IQSTREAM" variables

    rsa306b_reftime_struct reftime;       // API group "REFTIME" variables

    rsa306b_spectrum_struct spectrum;     // API group "SPECTRUM" variables

    rsa306b_trig_struct trig;             // API group "TRIG" variables

}; typedef struct rsa306b_struct rsa306b_struct;


#endif


////////~~~~~~~~END>  rsa306b_struct.h
