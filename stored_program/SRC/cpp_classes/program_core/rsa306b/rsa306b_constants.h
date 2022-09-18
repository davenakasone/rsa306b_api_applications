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
        const double EXTERNAL_FREQUENCY                   = 10e6;     // external reference frequency, required
        const double EXTERNAL_AMPLITUDE_DBM               = 10;       // allows +/- 10 dbm maximum amplitude  
        
        const double SPAN_MAX_HZ                          = 40e6;     // largest measurable bandwith
        const double SPAN_MIN_HZ                          = 100;      // smallest measurable bandwith 
        const double POSITION_PERCENT_MIN                 = 1;        // smallest trigger position percentage
        const double POSITION_PERCENT_MAX                 = 99;       // largest trigger position percentage
        

    // sizing the STL and Boost data structures
        const size_t SAMPLES_IN_BUFFER     = 260e6;    // ADC samples internal buffer is capable of storing before overflow, usally 130,848
        const size_t ADC_SAMPLES_PER_FRAME = 8178;     // ADC buffer size, number of 16-bit signed data samples per frame
        const size_t FRAMES_IN_BUFFER      = 32000;    // max IF frames the internal buffer can hold
        const size_t CORRECTION_POINTS     = 501;      // size of the correction points
        const size_t BYTES_PER_FRAME       = 16384;    // size of a frame, 2^14 bytes, includes footer
        //const size_t FOOTER_BYTES = 28;                // bytes per frame less 2*samples per frame

    
    

   

    // IQBLK constants...clean this acqStatus
        const uint8_t  IQBLK_GET_IQ_DATA                = 0;    // selects RSA_API::IQBLK_GetIQData() for acquisition
        const uint8_t  IQBLK_GET_IQ_DATA_CPLX           = 1;    // selects RSA_API::IQBLK_GetIQDataCplx() for acquisition
        const uint8_t  IQBLK_GET_IQ_DATA_DEINETERLEAVED = 2;    // selects RSA_API::IQBLK_GetIQDataDeinterleaved() for acquisition
        const int      IQBLK_MIN_PAIRS                  = 2;
        const int      IQBLK_STARTING_PAIRS             = 1000;
        const int      IQBLK_GETTER_DEFAULT             = IQBLK_GET_IQ_DATA_DEINETERLEAVED;
        const double   IQBLK_STARTING_BANDWIDTH         = 1e6;
        const uint32_t ACQ_STATUS_SUCCESS               = 0;    // IQBLK,  successful value for API bit checks
        const char     ACQ_STATUS_SUCCESS_MESSAGE[BUF_B] = "GOOD BITCHECK";  
        //const int IQBLK_MAX_PAIRS = 104857600;

    // IQSTREAM constants
        const int  IQSTREAM_MSEC_MIN             = 1;             // if this is 0, then infinite recording occurs, p79
        const int  IQSTREAM_MSEC_MAX             = 1000;          // limit for disk space, the files are huge
        const char IQSTREAM_FILENAME_BASE[BUF_C] = "iqstream";    // for writing output
        const int  IQSTREAM_TIMEOUT_MS           = 100;
        // setting the buffer size, direct acquisition, see p82
        const int IQSTREAM_BUFFER_SIZE_LARGE  = 65536;                            // for 2.5 MHz to 40 MHz
        const int IQSTREAM_BUFFER_SIZE_MEDIUM = 32768;                            // for 96765.625 Hz to 2.5 MHz
        const int IQSTREAM_BUFFER_SIZE_SMALL  = 128;                              // for < 96765.625 Hz
        const int IQSTREAM_DIV[8]             = {1, 2, 4, 8, 16, 32, 64, 128};    // dividers for base size inference
        enum
        {
            IQSTREAM_BUFFER_X_1 = 1,    // the minimum size
            IQSTREAM_BUFFER_X_2 = 2,    // the default size
            IQSTREAM_BUFFER_X_3 = 3,
            IQSTREAM_BUFFER_X_4 = 4,
            IQSTREAM_BUFFER_X_5 = 5,
            IQSTREAM_BUFFER_X_6 = 6,
            IQSTREAM_BUFFER_X_7 = 7,
            IQSTREAM_BUFFER_X_8 = 8     // the maximum size
        };
        const double IQSTREAM_BANDWIDTH_RANGES[IQSTREAM_ROW_RANGES][2] =
        {
            {1.25e6 / IQSTREAM_DIV[0], 2.5e6 / IQSTREAM_DIV[0]},    // divided by 2^0
            {1.25e6 / IQSTREAM_DIV[1], 2.5e6 / IQSTREAM_DIV[1]},    // divided by 2^1...
            {1.25e6 / IQSTREAM_DIV[2], 2.5e6 / IQSTREAM_DIV[2]},
            {1.25e6 / IQSTREAM_DIV[3], 2.5e6 / IQSTREAM_DIV[3]},
            {1.25e6 / IQSTREAM_DIV[4], 2.5e6 / IQSTREAM_DIV[4]},
            {1.25e6 / IQSTREAM_DIV[5], 2.5e6 / IQSTREAM_DIV[5]},
            {1.25e6 / IQSTREAM_DIV[6], 2.5e6 / IQSTREAM_DIV[6]},      
            {1.25e6 / IQSTREAM_DIV[7], 2.5e6 / IQSTREAM_DIV[7]},    // divided by 2^7
            {SPAN_MIN_HZ, 9765.625},                                // lowest bandwidth range, smallest sample pairs
            {2.5e6, 40e6}                                           // highest bandwidth range, largest sample pairs
            
        };
        // [0:5] for sample, [6:11] sticky, [12] summary, common to both "acqStatus" checks
        enum
        {
            IQSTREAM_BIT_0       = 0,
            IQSTREAM_BIT_1       = 1,
            IQSTREAM_BIT_2       = 2,
            IQSTREAM_BIT_3       = 3,
            IQSTREAM_BIT_4       = 4,
            IQSTREAM_BIT_5       = 5,
            IQSTREAM_BIT_16      = 6,
            IQSTREAM_BIT_17      = 7,
            IQSTREAM_BIT_18      = 8,
            IQSTREAM_BIT_19      = 9,
            IQSTREAM_BIT_20      = 10,
            IQSTREAM_BIT_21      = 11,
            IQSTREAM_BIT_SUMMARY = 12
        };
        
}; typedef struct rsa306b_constants rsa306b_constants;


#endif


////////~~~~~~~~END>  rsa306b_constants.h
