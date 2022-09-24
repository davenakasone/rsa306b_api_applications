/*
    fixed values, requested to be populated at compile time
*/

#ifndef H_constant_expresions
#define H_constant_expresions


#include "common_libraries.h"


// Data IO
constexpr char DATA_DIRECTORY_RAW[]       = "../DATA/data_raw/";         // write data received directly from the RSA-306B here
constexpr char DATA_DIRECTORY_PROCESSED[] = "../DATA/data_processed/";   // write data modified by the program here
constexpr char DATA_OUTPUT_EXTENSTION[]   = ".csv";                      // default output file extention


// program sizing parameters
constexpr int BUF_A = 32;      // a short general purpose buffer
constexpr int BUF_B = 64;      // ..
constexpr int BUF_C = 128;     // ...
constexpr int BUF_D = 256;     // ....
constexpr int BUF_E = 512;     // .....
constexpr int BUF_F = 1024;    // a long general purpose buffer


// program initialization values, covers most types
constexpr char         INIT_CHAR       = 'Z';
constexpr char         INIT_CHARP[]    = "ZZZ";
constexpr double       INIT_DOUBLE     = -9.9F;
constexpr float        INIT_FLOAT      = -9.9F;
constexpr int          INIT_INT        = -9;
constexpr int8_t       INIT_INT8       = -9;
constexpr int16_t      INIT_INT16      = -9;
constexpr int32_t      INIT_INT32      = -9;
constexpr int64_t      INIT_INT64      = -9L;
constexpr std::size_t  INIT_STD_SIZE_T = 5UL;
constexpr std::size_t  INIT_STL_LENGTH = 3UL;    // for sizing std::vector, std::queue, ...make this big if preallocating helps
constexpr uint8_t      INIT_UINT8      = 0xFFU;
constexpr uint16_t     INIT_UINT16     = 0xFFFFU;
constexpr uint32_t     INIT_UINT32     = 0xFFFFFFFFU;
constexpr uint64_t     INIT_UINT64     = 0xFFFFFFFFFFFFFFFFLU;
constexpr wchar_t      INIT_WCHARP[]   = L"wchar_t";


//////////////////////////////////////////////// Common hardware constants ///////////////////////////////////////////////////////////////////////////////////////
constexpr std::size_t TRACES_306B                = 3UL;                // the RSA-306B has 3 possible traces available
constexpr char        BITCHECK_SUCCESS_MESSAGE[] = "good bitcheck";    // common message recorded upon successful bitcheck
constexpr unsigned    BITCHECK_SUCCESS           = 0U;                 // all successful bitchecks result in 0
constexpr std::size_t SAMPLES_PER_FRAME          = 8178LU;             // number of 16-bit-signed data samples, per frame  (capacity ~ 260e6 samples, 32e3 frames)
                                                                       // note 2^14 bytes per frame, less 28 for footer, /2 --> # of int16_t samples
// AUDIO
constexpr char AUDIO_FILE_NAME_BASE[] = "audio";       // default output file base name for the API group
constexpr char AUDIO_FIELD_1[]        = "interval";    // used to label fields in "*.csv" output
constexpr char AUDIO_FIELD_2[]        = "values";      // used to label fields in "*.csv" output

// DPX
constexpr char DPX_FILE_NAME_BASE[]                        = "dpx";                // default output file base name for the API group
constexpr char DPX_OUTPUT_TYPE_SOGRAM_BITMAP[]             = "sogram_bitmap";      // default to place in file name when writing a 'sogram_bitmap'
constexpr char DPX_OUTPUT_TYPE_SPECTRUM_BITMAP[]           = "spectrum_bitmap";    // default to place in file name when writing a 'spectrum_bitmap'
constexpr char DPX_OUTPUT_TYPE_HI_RES_LINE[]               = "hires_line";         // default to place in file name when writing a 'hires_line'
constexpr int  DPX_BITCHECKS                               = 5;                    // checks for 'DPX' acqDataStatus
constexpr char DPX_BITCHECK_MESSAGES[DPX_BITCHECKS][BUF_B] =                       // error codes for 'DPX' bitchecks
{
    "b0 : input to the ADC was outside of its operating range",
    "b1 : loss of locked status on the reference oscillator",
    "b4 : power (5V and USB) failure detected",
    "b5 : dropped frame, loss of ADC data frame samples",
    "acqDataStatus bitcheck failures: "
};

// IFSTREAM
constexpr char IFSTREAM_FILE_NAME_BASE[]                             = "ifstream";    // default base name for output files
constexpr int  IFSTREAM_BITCHECKS                                    = 3;             // checks for 'IFSTREAM' acqStatus
constexpr char IFSTREAM_FIELD_1[]                                    = "interval";    // used to label fields in "*.csv" output
constexpr char IFSTREAM_FIELD_2[]                                    = "adc";         // used to label fields in "*.csv" output
constexpr char IFSTREAM_BITCHECK_MESSAGES[IFSTREAM_BITCHECKS][BUF_B] =                // error codes for 'IFSTREAM' bitchecks
{
    "b0 : ADC input overrange detected",
    "b1 : continuity error (gap) detected in IF frames",
    "acqStatus bitcheck failures: "
};

// IQBLK
typedef enum 
{
    interleaved   = 0, 
    deinterleaved = 1, 
    complex       = 2
} iqblkGetData;                                                                    // method to acquire IQBLK data
constexpr char IQBLK_FILE_NAME_BASE[]                             = "iqblk";       // default base name for output files
constexpr int  IQBLK_BITCHECKS                                    = 5;             // checks for 'IQBLK' acqStatus
constexpr char IQBLK_FIELD_1[]                                    = "interval";    // used to label fields in "*.csv" output
constexpr char IQBLK_FIELD_2[]                                    = "I";           // used to label fields in "*.csv" output
constexpr char IQBLK_FIELD_3[]                                    = "Q";           // used to label fields in "*.csv" output
constexpr char IQBLK_BITCHECK_MESSAGES[IQBLK_BITCHECKS][BUF_C] =                   // error codes for 'IQBLK' bitchecks
{
    "b0 : ADC overange during acquisition",
    "b1 : frequency reference unlocked during acquisition",
    "b2 : acquisition system error within block (power or oscillator failure)",
    "b3 : data transfer error within block (USB frame) during acquisition",
    "acqStatus bitcheck failures: "
};

// IQSTREAM
typedef enum
{
    X_1 = 1,    // the minimum size
    X_2 = 2,    // the default size
    X_3 = 3,
    X_4 = 4,
    X_5 = 5,
    X_6 = 6,
    X_7 = 7,
    X_8 = 8     // the maximum size
}iqstreamBufferMultiple;
constexpr char IQSTREAM_FILE_NAME_BASE[] = "iqstream";
constexpr int IQSTREAM_BITCHECKS         =  13;                //  status bits [0:5], [16:21], + summary, for both "*acqStatus" 
const char IQSTREAM_FAIL_BITS[IQSTREAM_BITCHECKS][BUF_C] =
{
    "b0  {this sample} RF input overrange detected",
    "b1  {this sample} USB data stream discontinuity error, gap detected in IF frame transfers",
    "b2  {this sample} Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream",
    "b3  {this sample} Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured",
    "b4  {this sample} Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data",
    "b5  {this sample} Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped",
    "b16 {sticky}      RF input overrange detected",
    "b17 {sticky}      USB data stream discontinuity error, gap detected in IF frame transfers",
    "b18 {sticky}      Input buffer >= 75 %% full, IQ processing may have difficulty keeping up with IF sample stream",
    "b19 {sticky}      Input buffer overflow, IQ processing cannot keep up with IF sample stream, data loss occured",
    "b20 {sticky}      Output buffer >= 75%% full, output sink (disk/client) falling behind unloading data",
    "b21 {sticky}      Output buffer overflow, IQ unloading not keeping up with IF sample stream, output samples dropped",
    "acqStatus bitcheck failures: "
};

// SPECTRUM
constexpr char SPECTRUM_FILE_NAME_BASE[]                             = "spectrum_trace_";    // default output file base name for the API group
constexpr char SPECTRUM_FIELD_1[]                                    = "frequency";          // used to label fields in "*.csv" output
constexpr char SPECTRUM_FIELD_2[]                                    = "power";              // used to label fields in "*.csv" output
constexpr int  SPECTRUM_BITCHECKS                                    = 5;                    // checks for DPX acqDataStatus
constexpr char SPECTRUM_BITCHECK_MESSAGES[SPECTRUM_BITCHECKS][BUF_B] =                       // error codes for 'SPECTRUM' bitchecks
{
    "b0 : input to the ADC was outside of its operating range",
    "b1 : loss of locked status on the reference oscillator",
    "b4 : power (5V and USB) failure detected",
    "b5 : dropped frame, loss of ADC data frame samples",
    "acqDataStatus bitcheck failures: "
};


#endif


////////~~~~~~~~END>  constant_expresions.h