/*
    this struct maintians the consants used in "rsa306b" object instances
    these constants are specific to the RSA-306B 

    there are other constants, common to all classes, in "resourcez.h"
    limiting constants can be found in the API group header file "rsa306b_<API_group>_struct.h"

    "_<API group>*" variables are initialization values, all can be adjusted here
*/

#ifndef H_rsa306b_constants
#define H_rsa306b_constants


#include "../control/resourcez.h"    // includes external libraries and other resources


// constexpr helpers, applies to more than 1 API group









/*
    acqData
    as found in:
        IFSTRMDATAINFO >> uint32_t  acqStatus;
*/









constexpr int IQSTREAM_ROW_RANGES = 10;    // IQSTREAM, ranges to infer buffer size from current bandwidth


struct rsa306b_constants
{

    // device limits for the RSA-306B
        
        
        

    // sizing the STL and Boost data structures

    
        const size_t SAMPLES_IN_BUFFER     = 260e6;    // ADC samples internal buffer is capable of storing before overflow, usally 130,848
        
        const size_t FRAMES_IN_BUFFER      = 32000;    // max frames the internal buffer can hold
        const size_t CORRECTION_POINTS     = 501;      // size of the correction points
        const size_t BYTES_PER_FRAME       = 16384;    // size of a frame, 2^14 bytes, includes footer
        //const size_t FOOTER_BYTES = 28;                // bytes per frame less 2*samples per frame


    // IQSTREAM constants
        
        // setting the buffer size, direct acquisition, see p82
        
       
        
        
}; typedef struct rsa306b_constants rsa306b_constants;


#endif


////////~~~~~~~~END>  rsa306b_constants.h
