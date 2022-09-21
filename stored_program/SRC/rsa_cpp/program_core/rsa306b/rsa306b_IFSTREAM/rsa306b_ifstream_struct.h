/*
    variables needed for the API group "IFSTREAM" 
        IFSTREAM_SetDiskFilenameSuffix()
        IFSTREAM_GetActiveStatus()
        IFSTREAM_GetAcqParameters()
        IFSTREAM_GetEQParameters()
        IFSTREAM_GetIFData()
        IFSTREAM_GetIFDataBufferSize()
        IFSTREAM_GetIFFrames()
        IFSTREAM_GetScalingParameters()
        IFSTREAM_SetDiskFileCount()
        IFSTREAM_SetDiskFileLength()
        IFSTREAM_SetDiskFilenameBase()
        IFSTREAM_SetDiskFilePath()
        IFSTREAM_SetEnable()
        IFSTREAM_SetOutoutConfiguration()

    active vars :
        int                               file_name_suffix
        bool                              is_active   
        double                            if_bandwidth_hz
        double                            samples_per_second
        double                            if_center_frequency
        int                               points_in_equalization_buffer
        std::vector<float>                eq_frequency_v
        std::vector<float>                eq_amplitude_v
        std::vector<float>                eq_phase_v     
        std::vector<int16_t>              adc_data_v  
        std::vector<bool>                 adc_triggers_v
        int                               if_data_length
        char                              acq_status_messages[IFSTREAM_BITCHECKS][BUF_D]
        RSA_API::IFSTRMDATAINFO           data_info_type
        int                               buffer_size_bytes
        int                               buffer_samples
        std::vector<std::vector<int16_t>> framed_adc_data_v
        int                               frame_bytes
        int                               number_of_frames
        double                            scale_factor    
        double                            scale_frequency
        int                               file_count
        int                               file_length_max_ms
        char                              file_name_base[BUF_B]
        char                              file_path[BUF_B]
        RSA_API::IFSOUTDEST               output_destination_select

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore

    make sure DEVICE_Run() is called at least once before using
    start and stop the IFSTREAM and DEVICE enables in sequence
    <file path> <filename base> <suffix> . <ext> , use ".r3f"

    obsolete :
        IFSTREAM_SetDiskFileMode()
*/


#ifndef H_rsa306b_ifstream_struct
#define H_rsa306b_ifstream_struct


#include "../../control/resourcez.h"


// constexpr helpers
constexpr char IFSTREAM_FILE_NAME_BASE[] = "ifstream";
constexpr int  IFSTREAM_BITCHECKS        = 3;
constexpr char IFSTREAM_BITCHECK_MESSAGES[IFSTREAM_BITCHECKS][BUF_B] =
{
    "b0 : ADC input overrange detected",
    "b1 : continuity error (gap) detected in IF frames",
    "acqStatus bitcheck failures: "
};


struct rsa306b_ifstream_struct
{


// limiting constants
const double LOOP_LIMIT_S    = 0.05;    // maximum time, in seconds, to loiter in a loop and wait for data acquisition
const int FILE_LENGTH_MAX_MS = 999;


/*
    IFSTREAM_SetDiskFilenameSuffix()
        last field before the extension
            file_name_suffix ; determines suffix {-2, -1, >=0}, use the enum
*/
    int       file_name_suffix;
    const int _FILE_NAME_SUFFIX = static_cast<int>(RSA_API::IFSSDFN_SUFFIX_NONE);    // DEFAULT


/*
    IFSTREAM_GetActiveStatus()
        status of ADC streaming operation
            is_active ; if true, the data is still being acquired, else false
*/
    bool       is_active;         
    const bool _IS_ACTIVE = false;    // DEFAULT


/*
    GetAcqParameters()
        if_bandwidth_hz    ; usuable IF signal bandwidth in Hz
        samples_per_second ; IF data sample rate, in samples per second
        if_center_frequency; IF frequency where original requestd center frequency was translated
*/
    double       if_bandwidth_hz;        
    const double _IF_BANDWIDTH_HZ = INIT_DOUBLE;       // DEFAULT

    double       samples_per_second;
    const double _SAMPLES_PER_SECOND = INIT_DOUBLE;    // DEFAULT

    double       if_center_frequency;
    const double _IF_CENTER_FREQUENCY = INIT_DOUBLE;   // DEFAULT


/*
    GetEQParameters()
        intended for client to receive and do custom processing
        if device settings change, the device must run for these to take effect
        apply these scalars to flatten / correct the IFSTREAM data
        points_in_equalization_buffer ; number of points in the equalization buffer
            eq_frequency_v                ; collects equalization frequencies, in Hz
            eq_amplitude_v                ; collects equalization amplitudes,  in dB
            eq_phase_v                    ; collects equalization phase, in degrees
*/
    int       points_in_equalization_buffer;
    const int _POINTS_IN_EQUALIZATION_BUFFER = INIT_INT;           // DEFAULT

    std::vector<float> eq_frequency_v;
    const float        _EQ_FREQUENCY_V_element    = INIT_FLOAT;    // DEFAULT
    const std::size_t  _EQ_FREQUENCY_V_size = INIT_STL_LENGTH;     // DEFAULT

    std::vector<float> eq_amplitude_v;   
    const float        _EQ_AMPLITUDE_V_element    = INIT_FLOAT;    // DEFAULT
    const std::size_t  _EQ_AMPLITUDE_V_size = INIT_STL_LENGTH;     // DEFAULT

    std::vector<float> eq_phase_v;        
    const float        _EQ_PHASE_V_element    = INIT_FLOAT;        // DEFAULT
    const std::size_t  _EQ_PHASE_V_size = INIT_STL_LENGTH;         // DEFAULT


/*
    IFSTREAM_GetIFData()
        retrieves the entire ADC buffer
        for receiving the IF stream directly into the program
        client must take internal buffers before they overflow
        internal buffer can only hold 2.4 seconds of ADC data, about 260e6 samples
        internal dynamically allocated data types are supplemented with std::vector
            adc_data_v          ; collects internal buffer
            adc_triggers_v      ; when trigger index is acquired, inicates if trigger event occured for the sample 
            if_data_length      ; number of signed 16-bit samples returned
            acq_status_messages ; tracks error messages present in each bicheck position
            data_info_type      ; contains aquisition information, "aqcStatus" 
        struct IFSTRMDATAINFO   // what would be in the footer of a "*.r3f" file
            timestamp      ; timestamp of first IF sample returned in block
            triggerCount   ; number of triggers detected in this block
            triggerIndices ; internal array of trigger sample indices in block (overwritten on each new block query)
            acqStatus      ; see IQSTRM_STATUS enum to decode, needs a bit check
*/          
    std::vector<int16_t> adc_data_v;  
    const int16_t        _ADC_DATA_V_element = INIT_INT16;                   // DEFAULT
    std::size_t          _ADC_DATA_V_size    = INIT_STL_LENGTH;              // DEFAULT

    std::vector<bool> adc_triggers_v;  
    const bool        _ADC_TRIGGERS_element    = false;                      // DEFAULT
    std::size_t       _ADC_TRIGGERS_V_size  = INIT_STL_LENGTH;               // DEFAULT

    int       if_data_length;
    const int _IF_DATA_LENGTH = INIT_INT;                                    // DEFAULT

    char        acq_status_messages[IFSTREAM_BITCHECKS][BUF_D];
    const char* _ACQ_STATUS_MESSAGES = BITCHECK_SUCCESS_MESSAGE;            // DEFAULT

    RSA_API::IFSTRMDATAINFO data_info_type;   
    const uint64_t          _DATA_INFO_TYPE_timestamp      = INIT_UINT64;         // DEFAULT
    const int               _DATA_INFO_TYPE_triggerCount   = INIT_INT;            // DEFAULT
    int*                    _DATA_INFO_TYPE_triggerIndices = NULL;                // DEFAULT
    const uint32_t          _DATA_INFO_TYPE_acqStatus      = BITCHECK_SUCCESS;    // DEFAULT


/*
    IFSTREAM_GetIFDataBufferSize()
        query buffer requirements clinet must provide
        must use before calling "IFSTREAM_GetIFData()"
        should call "IFSTREAM_SetOutputConfiguration()" before calling this, to indicate client output is required
            buffer_size_bytes ; size in bytes to allocate when calling "GetIFData()" // (int16_t*)malloc(buffer_size_in_bytes / 2)
            number_of_samples ; number of 16-bit samples "GetIFData()" will return   // (int16_t*)malloc(number_samples*sizeof(int16_t))
*/ 
    int       buffer_size_bytes; 
    const int _BUFFER_SIZE_BYTES = INIT_INT;    // DEFAULT

    int       buffer_samples;
    const int _BUFFER_SAMPLES = INIT_INT;    // DEFAULT


/*
    IFSTREAM_GetIFFrames()
        access to raw USB frames (includes footer), that is why it gets byte-by-byte (uint8_t)
        understand the contents of a frame, there is a lot of intermixed data
        use "IFSTREAM_GetIFData()" if you want a continous block + trigger info
        must acquire the data fast enough, before overflow occurs
        internal buffers only have 2.4 seconds of IF frames, about 32k frames
            framed_adc_data_v ; frame index and ADC sample value, (getter[n+1] << 8) | (getter[n]), don't allocate getter*
            frame_bytes       ; frame data length, in bytes (includes data + footer)
            number_of_frames  ; number of frames acquired  

*/
    std::vector<std::vector<int16_t>> framed_adc_data_v;
    const int16_t                     _FRAMED_ADC_DATA_V_element = INIT_INT16;         // DEFAULT
    const std::size_t                 _FRAMED_ADC_DATA_V_rows    = INIT_STL_LENGTH;    // DEFAULT
    const std::size_t                 _FRAMED_ADC_DATA_V_cols    = INIT_STL_LENGTH;    // DEFAULT

    int       frame_bytes;    
    const int _FRAME_BYTES = INIT_INT;                                                 // DEFAULT

    int number_of_frames;
    const int _NUMBER_OF_FRAMES = INIT_INT;                                            // DEFAULT
    
           
/*
    IFSTREAM_GetScalingParameters()
        if device settings are changed, run the device before calling
            scale_factor   ; multiply ADC data for equivelent of volts terminated at 50 ohms
            scale_frequency; IF frequency the scale factor applies
*/
    double       scale_factor;       
    const double _SCALE_FACTOR = INIT_DOUBLE;    // DEFAULT

    double       scale_frequency; 
    const double _SCALE_FREQUENCY = INIT_DOUBLE;    // DEFAULT


/*
    IFSTREAM_SetDiskFileCount()
        remember that files > 1 second get split into multiple files, so check duration
            file_count ; sets maximum number of files to save 
*/
    int       file_count;
    const int _FILE_COUNT = 1;    // DEFAULT


/*
    IFSTREAM_SetDiskFileLength()
        anything > 1 second will split files
            file_length_max_ms ; maximum recording time for any single data file, in ms
*/
    int       file_length_max_ms;           
    const int _FILE_LENGTH_MAX_MS = FILE_LENGTH_MAX_MS;    // DEFAULT


/*
    IFSTREAM_SetDiskFilenameBase()
        this field follows after the "path"
            file_name_base ; <file path> <filename base> <suffix> . <ext>
*/
    char        file_name_base[BUF_B]; 
    const char* _FILE_NAME_BASE = IFSTREAM_FILE_NAME_BASE;    // DEFAULT


/*
    IFSTREAM_SetDiskFilePath()
        file_path ; <file path> <filename base> <suffix> . <ext>
*/
    char        file_path[BUF_B];
    const char* _FILE_PATH = DATA_DIRECTORY_RAW;    // DEFAULT


/*
    IFSTREAM_SetEnable()
        start or stop the IF streaming operation
        see "is_active" in "IFSTREAM_GetActiveStatus()"
*/


/*
    IFSTREAM_SetOutoutConfiguration()
        will set the file format if needed, see the enum
        {0: no file, direct to client, 1:r3f, 3:r3h+r3a, 11:CDIF, 12:CDIF+DET}
            output_destination_select ; where the stream goes
*/
    RSA_API::IFSOUTDEST       output_destination_select;   
    const RSA_API::IFSOUTDEST _OUTPUT_DESTINATION_SELECT = RSA_API::IFSOUTDEST::IFSOD_CLIENT;    // DEFAULT
    

};
typedef struct rsa306b_ifstream_struct rsa306b_ifstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_ifstream_struct.h
   