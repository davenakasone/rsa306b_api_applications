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

    // status
        const int CALL_SUCCESS                       = 7777;    // successful, non-API function calls
        const int CALL_FAILURE                       = -777;    // failed, non-API function calls (must be different)
        const uint32_t ACQ_STATUS_SUCCESS            = 0;       // successful value for API bit checks
        const char ACQ_STATUS_SUCCESS_MESSAGE[BUF_B] = "GOOD BITCHECK";


    // initialization values and sizes
        const char    INIT_CHAR            = 'Z';
        const char    INIT_STR[6]          = "ZZZZZ";
        const double  INIT_DOUBLE          = -99.123;
        const float   INIT_FLOAT           = -99.4;
        const int     INIT_INT             = -99;
        const std::size_t  INIT_STL_LENGTH = 3;    // for std::vector, std::queue, ...
        const uint8_t INIT_UINT            = 0xFF;
        const wchar_t INIT_WCHAR[6]        = L"w_str";

    // device limits for the RSA-306B
        const double EXTERNAL_FREQUENCY                   = 10e6;     // external reference frequency, required
        const double EXTERNAL_AMPLITUDE_dbm               = 10;       // allows +/- 10 dbm maximum amplitude  
        const double REFERENCE_LEVEL_MAX_dbm              = 30;       // highest measurable signal power
        const double REFERENCE_LEVEL_MIN_dbm              = -130;     // smallest measurable signal power
        const double SPAN_MAX_Hz                          = 40e6;     // largest measurable bandwith
        const double SPAN_MIN_Hz                          = 100;      // smallest measurable bandwith 
        const double POSITION_PERCENT_MIN                 = 1;        // smallest trigger position percentage
        const double POSITION_PERCENT_MAX                 = 99;       // largest trigger position percentage
        const float AUDIO_VOLUME_MAX                      = 1.0;      // maximum audio volume API will accept
        const float AUDIO_VOLUME_MIN                      = 0.0;      // minimum audio volume API will accept
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz = 20e6;     // highest audio demodulator API accepts
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz = -20e6;    // highest audio demodulator API accepts

    // sizing the STL and Boost data structures
        const size_t SAMPLES_IN_BUFFER     = 260e6;    // ADC samples internal buffer is capable of storing before overflow, usally 130,848
        const size_t ADC_SAMPLES_PER_FRAME = 8178;     // ADC buffer size, number of 16-bit signed data samples per frame
        const size_t FRAMES_IN_BUFFER      = 32000;    // max IF frames the internal buffer can hold
        const size_t CORRECTION_POINTS     = 501;      // size of the correction points
        const size_t BYTES_PER_FRAME       = 16384;    // size of a frame, 2^14 bytes, includes footer
        //const size_t FOOTER_BYTES = 28;                // bytes per frame less 2*samples per frame

    // generating output files
        const char SPECTRUM_CSV_PATH[BUF_B] = "./program_test/data/outputs_txt/";    // where "spectrum_write_csv()" goes

        const int IFSTREAM_SUFFIX                 = -1;                                   // control file suffix name for IFSTREAM group, {0:increment, -1:timestamp, -2:none}
        const char IFSTREAM_FILE_PATH[BUF_B]      = "./program_test/data/outputs_r3f/";   // IFSTREAM output directory
        const char IFSTREAM_FILE_NAME_BASE[BUF_A] = "ifstream";                           // IFSTREAM base file name
        const int IFSTREAM_MAX_MS                 = 1000;                                 // limit in milli-seconds for "*.r3f" file
        const int IFSTREAM_DEFAULT_MS             = 10;                                   // default recording length for "*.r3f" files, in ms
        const int IFSTREAM_DEFAULT_FILE_COUNT     = 1;                                    // IFSTREAM files to produce
        const char IFSTREAM_CSV_PATH[BUF_B]       = "./program_test/data/outputs_txt/";   // where raw ADC data from IFSTREAM goes

    // IQBLK constants...clean this acqStatus
        const uint8_t IQBLK_GET_IQ_DATA                = 0;    // selects RSA_API::IQBLK_GetIQData() for acquisition
        const uint8_t IQBLK_GET_IQ_DATA_CPLX           = 1;    // selects RSA_API::IQBLK_GetIQDataCplx() for acquisition
        const uint8_t IQBLK_GET_IQ_DATA_DEINETERLEAVED = 2;    // selects RSA_API::IQBLK_GetIQDataDeinterleaved() for acquisition
        const char IQBLK_BIT_0[BUF_B]                  = "*ADC input over range during acquisition*";
        const char IQBLK_BIT_1[BUF_B]                  = "*Frequency reference unlocked during acquisition*";
        const char IQBLK_BIT_2[BUF_B]                  = "*oscillator unlocked / power failure during acquisition*";
        const char IQBLK_BIT_3[BUF_B]                  = "*USB frame transfer error detected during acquisition*";
        const int IQBLK_MIN_PAIRS                      = 2;
        const int IQBLK_STARTING_PAIRS                 = 1000;
        const int IQBLK_GETTER_DEFAULT                 = IQBLK_GET_IQ_DATA_DEINETERLEAVED;
        const double IQBLK_STARTING_BANDWIDTH          = 1e6;
        //const int IQBLK_MAX_PAIRS = 104857600;
    
    // IQSTREAM constants, [0:5] for sample, [6:11] sticky, [12] summary
        enum
        {
            IQS_BIT_0 = 0,
            IQS_BIT_1 = 1,
            IQS_BIT_2 = 2,
            IQS_BIT_3 = 3,
            IQS_BIT_4 = 4,
            IQS_BIT_5 = 5,
            IQS_BIT_16 = 6,
            IQS_BIT_17 = 7,
            IQS_BIT_18 = 8,
            IQS_BIT_19 = 9,
            IQS_BIT_20 = 10,
            IQS_BIT_21  = 11,
            IQS_BIT_SUMMARY = 12
        };
        const char IQSTREAM_FAIL_BIT[IQSTREAM_BITCHECKS][BUF_C] =
        {
            "b0 {this sample} RF input overrange detected",
            "b1 {this sample} USB data stream discontinuity error, gap detected in IF frame transfers",
            "b2 {this sample} Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream",
            "b3 {this sample} Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured",
            "b4 {this sample} Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data",
            "b5 {this sample} Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped",
            "b16 {sticky} RF input overrange detected",
            "b17 {sticky} USB data stream discontinuity error, gap detected in IF frame transfers",
            "b18 {sticky} Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream",
            "b19 {sticky} Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured",
            "b20 {sticky} Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data",
            "b21 {sticky} Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped",
            "acqStatus bitcheck failures: "
        };
        /*
        const char IQSTREAM_FAIL_BIT_0[BUF_C] = "b0 {this sample} RF input overrange detected";
        const char IQSTREAM_FAIL_BIT_1[BUF_C] = "b1 {this sample} USB data stream discontinuity error, gap detected in IF frame transfers";
        const char IQSTREAM_FAIL_BIT_2[BUF_C] = "b2 {this sample} Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream";
        const char IQSTREAM_FAIL_BIT_3[BUF_C] = "b3 {this sample} Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured";
        const char IQSTREAM_FAIL_BIT_4[BUF_C] = "b4 {this sample} Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data";
        const char IQSTREAM_FAIL_BIT_5[BUF_C] = "b5 {this sample} Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped";

        const char IQSTREAM_FAIL_BIT_16[BUF_C] = "b16 {sticky} RF input overrange detected";
        const char IQSTREAM_FAIL_BIT_17[BUF_C] = "b17 {sticky} USB data stream discontinuity error, gap detected in IF frame transfers";
        const char IQSTREAM_FAIL_BIT_18[BUF_C] = "b18 {sticky} Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream";
        const char IQSTREAM_FAIL_BIT_19[BUF_C] = "b19 {sticky} Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured";
        const char IQSTREAM_FAIL_BIT_20[BUF_C] = "b20 {sticky} Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data";
        const char IQSTREAM_FAIL_BIT_21[BUF_C] = "b21 {sticky} Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped";

        const char IQSTREAM_FAIL_BITS[BUF_C] = "acqStatus bitcheck failures: ";
        */
};


#endif


////////~~~~~~~~END>  rsa306b_constants_class.h
