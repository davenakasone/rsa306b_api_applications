/*
    this class maintians the consants used in "rsa306b" object instances
    these constants are specific to the RSA-306B 

    route data through relative or absolute path:
        /home/unlv/Desktop/rsa306b_api_applications/working/cpp_class_v2/program_test/data
*/


#ifndef H_rsa306b_constants_class
#define H_rsa306b_constants_class


#include "../../control/resourcez.h"


class rsa306b_constants_class
{
    public :
        
        rsa306b_constants_class();
        ~rsa306b_constants_class();

    // status of internal non-API function calls
        const int CALL_SUCCESS = 7777;    // the function call was successful
        const int CALL_FAILURE = -777;    // the function call failed

    // common initialization values, by data type
        const char INIT_CHAR = 'Z';
        const char INIT_STR[6] = "ZZZZZ";
        const double INIT_DOUBLE = -99.123;
        const float INIT_FLOAT = -99.4;
        const int INIT_INT = -99;
        const uint8_t INIT_UINT = 99;

    // device limits for the RSA-306B
        const double EXTERNAL_FREQUENCY = 10e6;                       // external reference frequency, required
        const double EXTERNAL_AMPLITUDE_dbm = 10;                     // allows +/- 10 dbm maximum amplitude  
        const double REFERENCE_LEVEL_MAX_dbm = 30;                    // highest measurable signal power
        const double REFERENCE_LEVEL_MIN_dbm = -130;                  // smallest measurable signal power
        const double SPAN_MAX_Hz = 40e6;                              // largest measurable bandwith
        const double SPAN_MIN_Hz = 100;                               // smallest measurable bandwith 
        const double POSITION_PERCENT_MIN = 1;                        // smallest trigger position percentage
        const double POSITION_PERCENT_MAX = 99;                       // largest trigger position percentage
        const float AUDIO_VOLUME_MAX = 1.0;                           // maximum audio volume API will accept
        const float AUDIO_VOLUME_MIN = 0.0;                           // minimum audio volume API will accept
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz = 20e6;     // highest audio demodulator API accepts
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz = -20e6;    // highest audio demodulator API accepts

    // sizing the STL and Boost data structures
        const size_t SAMPLES_IN_BUFFER = 260e6;       // ADC samples internal buffer is capable of storing before overflow, usally 130,848
        const size_t ADC_SAMPLES_PER_FRAME = 8178;    // ADC buffer size, number of 16-bit signed data samples per frame
        const size_t FRAMES_IN_BUFFER = 32000;        // max IF frames the internal buffer can hold
        const size_t CORRECTION_POINTS = 501;         // size of the correction points
        const size_t BYTES_PER_FRAME = 16384;         // size of a frame, 2^14 bytes, includes footer
        //const size_t FOOTER_BYTES = 28;               // bytes per frame less 2*samples per frame

    // generating output files
        const char SPECTRUM_CSV_PATH[BUF_B] = "./program_test/data/outputs_txt/";    // where "spectrum_write_csv()" goes

        const int IFSTREAM_SUFFIX = -1;    // control file suffix name for IFSTREAM group, {0:increment, -1:timestamp, -2:none}
        const char IFSTREAM_FILE_PATH[BUF_B] = "./program_test/data/outputs_r3f/";   // IFSTREAM output directory
        const char IFSTREAM_FILE_NAME_BASE[BUF_A] = "ifstream";                      // IFSTREAM base file name
        const int IFSTREAM_MAX_MS = 1000;                                            // limit in milli-seconds for "*.r3f" file
        const int IFSTREAM_DEFAULT_MS = 10;                                          // default recording length for "*.r3f" files, in ms
        const int IFSTREAM_DEFAULT_FILE_COUNT = 1;                                   // IFSTREAM files to produce
        const char IFSTREAM_CSV_PATH[BUF_B] = "./program_test/data/outputs_txt/";    // where raw ADC data from IFSTREAM goes

    // IQBLK constants
        const char IQBLK_BIT_PASS[BUF_B] = "GOOD BITCHECK";
        const char IQBLK_BIT_0[BUF_B] = "*ADC input over range during acquisition*";
        const char IQBLK_BIT_1[BUF_B] = "*Frequency reference unlocked during acquisition*";
        const char IQBLK_BIT_2[BUF_B] = "*oscillator unlocked / power failure during acquisition*";
        const char IQBLK_BIT_3[BUF_B] = "*USB frame transfer error detected during acquisition*";
        const int IQBLK_MIN_PAIRS = 2;
        const int IQBLK_STARTING_PAIRS = 1000;
        const int IQBLK_MAX_PAIRS = 104857600;
        const double IQBLK_STARTING_BANDWIDTH = 1e6;
        uint32_t IQBLK_BIT_SUCCESS = 0; // bitcheck with no error
};


#endif


////////~~~~~~~~END>  rsa306b_constants_class.h
