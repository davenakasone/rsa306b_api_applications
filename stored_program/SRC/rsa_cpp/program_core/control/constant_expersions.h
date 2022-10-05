/*
    fixed values, requested to be populated at compile time

    note that the RSA_API header + all the C and C++ libraries are brought in

    this header will consolidate to "resourcez.h"
*/

#ifndef H_constant_expresions
#define H_constant_expresions


#include "common_libraries.h"  // the RSA_API header + all the C and C++ libraries


constexpr char CL_ARG_RESET[] = "reset";    // the command line argument, used through main(), that forces a hard reset


// Data IO
constexpr char DATA_DIRECTORY_RAW[]       = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_raw/";       
constexpr char DATA_DIRECTORY_PROCESSED[] = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_processed/";  
constexpr char DATA_DEFAULT_EXT[]         = "csv";      // data file outputs use this extension, if not specified, no "."                    
constexpr int EXTENSION_LIMIT             = 10;         // characters allowed in a file extension
constexpr char TAG_DECODED[]              = "_DEC_";    // decoded file outputs have this inserted into their file names, if not specified
constexpr char EXT_DECODED[]              = "txt";      // decoded file outputs use this extension, if not specified, no "."
constexpr char TAG_PARSED[]               = "_PAR_";    // parsed file outputs have this inserted into their file names, if not specified
constexpr char EXT_PARSED[]               = "txt";      // parsed file outputs use this extension, if not specified, no "."

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
constexpr std::size_t  INIT_STL_LENGTH = 9999UL;    // for sizing std::vector, std::queue, ...make this big if preallocating helps
constexpr uint8_t      INIT_UINT8      = 0xFFU;
constexpr uint16_t     INIT_UINT16     = 0xFFFFU;
constexpr uint32_t     INIT_UINT32     = 0xFFFFFFFFU;
constexpr uint64_t     INIT_UINT64     = 0xFFFFFFFFFFFFFFFFLU;
constexpr wchar_t      INIT_WCHARP[]   = L"wchar_t";


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// HARDWARE CONSTANTS ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
constexpr char DPX_TAG_SOGRAM_BITMAP[]                     = "sogram_bitmap";      // default to place in file name when writing a 'sogram_bitmap'
constexpr char DPX_TAG_SPECTRUM_BITMAP[]                   = "spectrum_bitmap";    // default to place in file name when writing a 'spectrum_bitmap'
constexpr char DPX_TAG_HI_RES_LINE[]                       = "hires_line";         // default to place in file name when writing a 'hires_line'
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
constexpr char IFSTREAM_FILE_NAME_BASE[]   = "ifstream";    // default base name for output files
constexpr char IFSTREAM_TAG_ADC[]          = "_ADC_";       // adc file outputs have this insersted into their file names, if not specified
constexpr char IFSTREAM_TAG_EQL[]          = "_EQL_";       // equalization file outputs have this insersted into their file names, if not specified
constexpr int  IFSTREAM_BITCHECKS          = 3;             // checks for 'IFSTREAM' acqStatus
constexpr char IFSTREAM_FIELD_ADC_1_OF_2[] = "time";        // used to label fields in "*.csv" output
constexpr char IFSTREAM_FIELD_ADC_2_OF_2[] = "adc";         // used to label fields in "*.csv" output
constexpr char IFSTREAM_FIELD_EQL_1_OF_3[] = "frequency";   // used to label fields in "*.csv" output
constexpr char IFSTREAM_FIELD_EQL_2_OF_3[] = "scaling";     // used to label fields in "*.csv" output
constexpr char IFSTREAM_FIELD_EQL_3_OF_3[] = "phase";       // used to label fields in "*.csv" output
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
constexpr char IQBLK_FIELD_1[]                                    = "time";        // used to label fields in "*.csv" output
constexpr char IQBLK_FIELD_2[]                                    = "I";           // used to label fields in "*.csv" output
constexpr char IQBLK_FIELD_3[]                                    = "Q";           // used to label fields in "*.csv" output
constexpr char IQBLK_BITCHECK_MESSAGES[IQBLK_BITCHECKS][BUF_C]    =                // error codes for 'IQBLK' bitchecks
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
    b1x = 1,    // scale IQ buffer to minimum size
    b2x = 2,    // scale IQ buffer to default size
    b3x = 3,
    b4x = 4,
    b5x = 5,
    b6x = 6,
    b7x = 7,
    b8x = 8     // scale IQ buffer to maximum size
}iqsBuff;
constexpr int IQSTREAM_BUFFER_SIZE_LARGE                          = 65536;         // for 2.5 MHz to 40 MHz
constexpr int IQSTREAM_BUFFER_SIZE_MEDIUM                         = 32768;         // for 96765.625 Hz to 2.5 MHz
constexpr int IQSTREAM_BUFFER_SIZE_SMALL                          = 128;           // for < 96765.625 Hz
constexpr int IQSTREAM_INTERVALS                                  = 10;            // bandwidth intervals
constexpr double IQSTREAM_BANDWIDTH_RANGES[IQSTREAM_INTERVALS][2] =
{
    {1.25e6 / 1   , 2.5e6 / 1   },   // divide by 2^0
    {1.25e6 / 2   , 2.5e6 / 2   },   // divide by 2^1 
    {1.25e6 / 4   , 2.5e6 / 4   },   // ...
    {1.25e6 / 8   , 2.5e6 / 8   },
    {1.25e6 / 16  , 2.5e6 / 16  },
    {1.25e6 / 32  , 2.5e6 / 32  },
    {1.25e6 / 64  , 2.5e6 / 64  },    // ...
    {1.25e6 / 128 , 2.5e6 / 128 },    // divided by 2^7
    {1e3          , 9765.625    },    // lowest bandwidth range, smallest sample pairs
    {2.5e6        , 40e6        }     // highest bandwidth range, largest sample pairs
    
};
constexpr char IQSTREAM_FILE_NAME_BASE[]                         = "iqstream";    // default base name for output files
constexpr char IQSTREAM_FIELD_1[]                                = "time";        // used to label fields in "*.csv" output
constexpr char IQSTREAM_FIELD_2[]                                = "I";           // used to label fields in "*.csv" output
constexpr char IQSTREAM_FIELD_3[]                                = "Q";           // used to label fields in "*.csv" output
constexpr int IQSTREAM_BITCHECKS                                 =  13;           //  status bits [0:5], [16:21], + summary, for both "*acqStatus" 
const char IQSTREAM_BITCHECK_MESSAGES[IQSTREAM_BITCHECKS][BUF_C] =                // error codes for 'IQSTREAM' bitchecks
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// RAW FILE CONSTANTS ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// R3F file parsing
constexpr char        R3F_RAW_EXT[]                       = "r3f";     // known name of the raw extension, no "."
constexpr std::size_t R3F_EQL_FILEDS                      = 3;         // frequency, scaling, and phase   
constexpr std::size_t R3F_EQL_IDX_FREQ                    = 0;         // index number of frequency in equalization vector
constexpr std::size_t R3F_EQL_IDX_SCAL                    = 1;         // index number of scaling in equalization vector
constexpr std::size_t R3F_EQL_IDX_PHAS                    = 2;         // index number of phase in equalization vector
constexpr size_t      R3F_FIELD_ID_SIZE_BYTES             = 28;        // header known field size
constexpr size_t      R3F_DEVICE_SERIAL_NUMBER_SIZE_BYTES = 64;        // header known field size
constexpr size_t      R3F_DEVICE_NOMENCLATURE_SIZE_BYTES  = 32;        // header known field size
constexpr int         R3F_REFTIME_ELEMENTS                = 7;         // header known field size
constexpr int         R3F_MAX_TABLE_ENTRIES               = 501;       // header known field size, equalization table
constexpr int         R3F_FOOTER_DISCARD                  = 8;         // header known field size, 28-byte frame footers, 8 bytes are nothing
constexpr long int    R3F_BI_FILE_ID_START                = 0L;        // header byte indexes, by section
constexpr long int    R3F_BI_FILE_ID_STOP                 = 511L;      // header byte indexes, by section
constexpr long int    R3F_BI_VERSION_INFO_START           = 512L;      // header byte indexes, by section
constexpr long int    R3F_BI_VERSION_INFO_STOP            = 1023L;     // header byte indexes, by section
constexpr long int    R3F_BI_INSTRUMENT_STATE_START       = 1024L;     // header byte indexes, by section
constexpr long int    R3F_BI_ISNTRUMENT_STATE_STOP        = 2047L;     // header byte indexes, by section
constexpr long int    R3F_BI_DATA_FORMAT_START            = 2048L;     // header byte indexes, by section
constexpr long int    R3F_BI_DATA_FORMAT_STOP             = 3071L;     // header byte indexes, by section
constexpr long int    R3F_BI_SIGNAL_PATH_START            = 3072L;     // header byte indexes, by section
constexpr long int    R3F_BI_SIGNAL_PATH_STOP             = 4095L;     // header byte indexes, by section
constexpr long int    R3F_BI_CHANNEL_CORRECTION_START     = 4096L;     // header byte indexes, by section
constexpr long int    R3F_BI_CHANNEL_CORRECTION_MID       = 4352L;     // header byte indexes, by section
constexpr long int    R3F_BI_CHANNEL_CORRECTION_STOP      = 12287L;    // header byte indexes, by section
constexpr char        R3F_BLOCK_SEPERATOR[BUF_C] = "------------------------------------------------------------------------------------------";

// SIQ file parsing
constexpr char SIQ_RAW_EXT[]               = "siq";    // known name of the raw extension, no "."
constexpr char SIQ_TAG_IQ[]               = "_IQ_";    // for "*.siq" CSV files, to signify IQ data
constexpr int  SIQ_HEADER_FIELDS           = 22;       // number of fields in an IQ data file header
constexpr int  SIQ_NUMBER_FORMATS          = 3;        // f9 NumberFormat, possible formats data samples in IQ file can use
constexpr int  SIQ_ENDIANS                 = 2;        // f11 DataEndian, possible endians data samples in IQ file can use
constexpr int  SIQ_REF_TIME_SOURCES        = 3;        // f20 RefTimeSource, possible time sources IQ file can use 
constexpr int  SIQ_FREQ_REF_SOURCES        = 4;        // f21 FreqRefSource, possible frequency sources IQ file can use
constexpr int  SIQ_CORRECT_IQ_FILE_VERSION = 1;        // f0 RSASIQHT, all "siq" files should be on version #1 for the RSA-306B
constexpr char SIQ_HEADER_FIELDS_STRINGS[SIQ_HEADER_FIELDS][BUF_A] =    // for searching the header of the "siq" file for field entries
{
    "RSASIQHT",             // index 0
    "FileDateTime",         // index 1
    "Hardware",             // index 2
    "Software/Firmware",    // index 3
    "ReferenceLevel",       // index 4
    "CenterFrequency",      // index 5
    "SampleRate",           // index 6
    "AcqBandwidth",         // index 7
    "NumberSamples",        // index 8
    "NumberFormat",         // index 9
    "DataScale",            // index 10
    "DataEndian",           // index 11
    "RecordUtcSec",         // index 12
    "RecordUtcTime",        // index 13
    "RecordLclTime",        // index 14
    "TriggerIndex",         // index 15
    "TriggerUtcSec",        // index 16
    "TriggerUtcTime",       // index 17
    "TriggerLclTime",       // index 18
    "AcqStatus",            // index 19
    "RefTimeSource",        // index 20
    "FreqRefSource"         // index 21

};
enum
{
    siq_RSASIQHT          = 0,     // index 0
    siq_FileDateTime      = 1,     // index 1
    siq_Hardware          = 2,     // index 2
    siq_Software_Firmware = 3,     // index 3
    siq_ReferenceLevel    = 4,     // index 4
    siq_CenterFrequency   = 5,     // index 5
    siq_SampleRate        = 6,     // index 6
    siq_AcqBandwidth      = 7,     // index 7
    siq_NumberSamples     = 8,     // index 8
    siq_NumberFormat      = 9,     // index 9
    siq_DataScale         = 10,    // index 10
    siq_DataEndian        = 11,    // index 11
    siq_RecordUtcSec      = 12,    // index 12
    siq_RecordUtcTime     = 13,    // index 13
    siq_RecordLclTime     = 14,    // index 14
    siq_TriggerIndex      = 15,    // index 15
    siq_TriggerUtcSec     = 16,    // index 16
    siq_TriggerUtcTime    = 17,    // index 17
    siq_TriggerLclTime    = 18,    // index 18
    siq_AcqStatus         = 19,    // index 19
    siq_RefTimeSource     = 20,    // index 20
    siq_FreqRefSource     = 21     // index 21
};

// f9 NumberFormat
const char SIQ_NUMBER_FORMATS_STRING[SIQ_NUMBER_FORMATS][BUF_A] =
{
    "IQ-Single",    // index 0
    "IQ-Int16",     // index 1
    "IQ-Int32"      // index 2
};
enum
{
    siq_NUMBER_FORMAT_SINGLE = 0,    // index 0
    siq_NUMBER_FORMAT_INT16  = 1,    // index 1
    siq_NUMBER_FORMAT_INT32  = 2     // index 2
};

// f11 DataEndian
const char SIQ_ENDIANS_STRING[SIQ_ENDIANS][BUF_A] =
{
    "Little",    // index 0
    "Big"        // index 1
};
enum
{
    siq_Little = 0,    // index 0
    siq_Big = 1        // index 1
};

// f20 RefTimeSource
constexpr char SIQ_REF_TIME_SOURCES_STRING[SIQ_REF_TIME_SOURCES][BUF_A] =
{
    "System",    // index 0
    "GnssRx",    // index 1
    "UserCa"     // index 2
};

// f21 FreqRefSource
constexpr char SIQ_FREQ_REF_SOURCES_STRING[SIQ_FREQ_REF_SOURCES][BUF_A] =
{
    "Intern",    // index 0
    "Extern",    // index 1
    "GnssRx",    // index 2
    "UserCa"     // index 3
};


#endif


////////~~~~~~~~END>  constant_expresions.h
