/*
    this class maintians the consants used in "rsa306b" object instances
    these constants are specific to the RSA-306B 
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

        // files
        const char SPECTRUM_CSV_PATH[BUF_B] = "./program_test/data/outputs_txt/";    // where "spectrum_write_csv()" goes

        const int IFSTREAM_SUFFIX = -2;    // control file suffix name for IFSTREAM group, {0:increment, -1:timestamp, -2:none}
        const char IFSTREAM_FILE_PATH[BUF_B] = "./program_test/data/outputs_r3f/";   // IFSTREAM output directory
        const char IFSTREAM_FILE_NAME_BASE[BUF_A] = "ifstream";                      // IFSTREAM base file name
        const int IFSTREAM_MAX_MS = 1000;                                            // limit in milli-seconds for "*.r3f" file
        const int IFSTREAM_DEFAULT_MS = 10;                                          // default recording length for "*.r3f" files, in ms
        const int IFSTREAM_DEFAULT_FILE_COUNT = 1;                                   // IFSTREAM files to produce

        ///home/unlv/Desktop/rsa306b_api_applications/working/cpp_class_v2/program_test/data
};


#endif


////////~~~~~~~~END>  rsa306b_constants_class.h
