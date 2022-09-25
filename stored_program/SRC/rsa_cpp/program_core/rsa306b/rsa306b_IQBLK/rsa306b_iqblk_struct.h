/*
    variables needed for the API group "IQBLK" 
        IQBLK_GetAcqInfo()
        IQBLK_AcquireIQData()
        IQBLK_GetIQBandwidth(), IQBLK_SetIQBandwidth()
        IQBLK_GetIQData()
        IQBLK_GetIQDataCplx()
        IQBLK_GetIQDataDeinterleaved()
        IQBLK_GetRecordLength(), IQBLK_SetIQRecordLength()
        IQBLK_GetIQSampleRate()
        IQBLK_GetMaxIQBandwidth()
        IQBLK_GetMaxIQRecordLength()
        IQBLK_GetMinIQBandwidth()
        IQBLK_WaitForIQDataReady()
    
    active :
        RSA_API::IQBLK_ACQINFO       acq_info_type
        char                         acq_status_messages[IQBLK_BITCHECKS][BUF_D]
        double                       bandwidth_hz
        int                          actual_buffer_samples
        std::vector<RSA_API::Cplx32> cplx32_v
        int                          record_length
        double                       sample_rate
        double                       max_bandwidth_hz
        int                          max_record_length
        double                       min_bandwidth_hz;
        iqblkGetData                 getting_select

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"

    device is configured before use
    find out which data getter is fastest, only use that one
    the API has many good options, but speed is the priority
*/

#ifndef H_rsa306b_iqblk_struct
#define H_rsa306b_iqblk_struct


#include "../../control/resourcez.h"


struct rsa306b_iqblk_struct
{


// limiting constants
const int RECORD_LENGTH_MIN = 2;     // minimum IQ samples a record can contain
const int LOOP_LIMIT_MS     = 50;    // maximum time, in milli-seconds, to loiter in a loop and wait for data acquisition


/*
    IQBLK_GetAcqInfo()
        can be called after IQBLK_GetData(), IQBLK_GetIQDataInterleaved(), or IQBLK_GetDataComplex()
        the returned info, in the RSA struct, applies to the most recent acquisition
        RSA_API::IQBLK_ACQINFO
            sample0Timestamp   ; timestamp of first sample in block 
            triggerSampleIndex ; sample index of trigger event in block
            triggerTimestamp   ; timestamp of trigger event in block
            acqStatus          ; see valid_bitmask and acqstatus_messages to decode	
    
*/
    RSA_API::IQBLK_ACQINFO acq_info_type;    
    const uint64_t _ACQ_INFO_TYPE_sample0Timestamp            = INIT_UINT64;                 // DEFAULT
    const uint64_t _ACQ_INFO_TYPE_triggerSampleIndex          = INIT_UINT64;                 // DEFAULT
    const uint64_t _ACQ_INFO_TYPE_triggerTimestamp            = INIT_UINT64;                 // DEFAULT
    const uint32_t _ACQ_INFO_TYPE_acqStatus                   = INIT_UINT32;                 // DEFAULT

    char           acq_status_messages[IQBLK_BITCHECKS][BUF_D];
    //const char*    _ACQ_STATUS_MESSAGES                       = BITCHECK_SUCCESS_MESSAGE;    // DEFAULT

    const uint32_t valid_bitmask                              = 
        (
            static_cast<uint32_t>(RSA_API::IQBLK_STATUS_INPUT_OVERRANGE)     |    // bit 0
            static_cast<uint32_t>(RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED)    |    // bit 1
            static_cast<uint32_t>(RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR)       |    // bit 2
            static_cast<uint32_t>(RSA_API::IQBLK_STATUS_DATA_XFER_ERROR)          // bit 3
        );


/*
    IQBLK_AcquireIQData()
        all settings must be applied before calling
        the device is automatically placed in the run state
        an IQ block transfer is initiated
        IQBLK bandwith and record length must be valid
*/


/*
    IQBLK_GetIQBandwidth(), IQBLK_SetIQBandwidth()
        bandwidth_hz ; get or set the IQ bandwidth
*/
    double       bandwidth_hz; 
    const double _BANDWIDTH_HZ = INIT_DOUBLE;    // DEFAULT


/*
    IQBLK_GetIQData()
        the record comes back in a single interleaved array ...interleaved
        float* iqData ; IQ data at alternating index
        outLength     ; actual number of IQ samples acquired
        reqLength     ; max is record length set, just use that to avoid partials

        the "I" is even    real
        the "Q" is odd     imag

        0  | 1  | 2  | 3  | ...   
        ------------------------              [0] = I0 + Q0 * sqrt(-1) ...
        I0 | Q0 | I1 | Q1 | ... 
*/
/*
    IQBLK_GetIQDataCplx()
        RSA_API::Cplx32* iqData ; use the API struct
        outLength               ; actual number of IQ samples acquired
        reqLength               ; max is record length set, just use that to avoid partials
    
    each index is a sample and the struct members will be populated
*/
/*
    IQBLK_GetIQDataDeinterleaved()
        float* qData ; I data at alternating index
        float* qData ; I data at alternating index
        outLength    ; actual number of IQ samples acquired
        reqLength    ; max is record length set, just use that to avoid partials

    just uses 2 float*
    index matches sample for both arrays
*/
/*
    actual_buffer_samples ; actual number of IQ sample pairs returned in IQ buffer
    cplx32_v              ; "Cplx32" structs, all IQBLK acquistion functions are transfered here
*/
    int       actual_buffer_samples;
    const int _ACTUAL_BUFFER_SAMPLES               = INIT_INT;           // DEFAULT

    std::vector<RSA_API::Cplx32> cplx32_v;
    const std::size_t            _CPLX32_V_size    = INIT_STL_LENGTH;    // DEFAULT
    const float                  _CPLX32_V_element = INIT_FLOAT;         // DEFAULT


/*
    IQBLK_GetIQRecordLength(), IQBLK_SetIARecordLength()
        record_length ; get/set the number of IQ data samples generated on each acquisition
*/

    int       record_length; 
    const int _RECORD_LENGTH = static_cast<int>(SAMPLES_PER_FRAME);    // DEFAULT


/*
    IQBLK_GetIQSampleRate()
        depends on IQ bandwidth, set bandwidth before querry
            sample_rate ; in samples per second
*/
    double       sample_rate;
    const double _SAMPLE_RATE = INIT_DOUBLE;    // DEFAULT


/*
    IQBLK_GetMaxIQBandwidth()
        max_bandwidth_hz ;  largest IQ bandwidth possible, in Hz
*/
    double max_bandwidth_hz;
    const double _MAX_BANDWIDTH_HZ = INIT_DOUBLE;    // DEFAULT


/*
    IQBLK_GetMaxIQRecordLength()
        varies on bandwidth, set bandwidth first
        don't request more than max
        this allocates the ~2 seconds of IQ data the device can store
        max_record_length ; largest IQ record length can be for 1 block "max samples"
*/
    int       max_record_length;
    const int _MAX_RECORD_LENGTH = INIT_INT;    // DEFAULT


/*
    IQBLK_GetMinIQBandwidth()
        min_bandwidth_hz ; smallest IQ bandwidth possible
*/
    double       min_bandwidth_hz; 
    const double _MIN_BANDWIDTH_HZ = INIT_DOUBLE;    // DEFAULT


/*
    IQBLK_WaitForIQDataReady()
        scoped to the 3 "IQBLK_GetData*" API functions
            int timeout_ms     ; scoped to local function
            bool data_is_ready ; scoped to local function
*/


// extra

    iqblkGetData       getting_select;                             // specify what acquitsition API function will be called
    const iqblkGetData _GETTING_SELECT = iqblkGetData::complex;    // DEFAULT
    
    
};
typedef struct rsa306b_iqblk_struct rsa306b_iqblk_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqblk_struct.h
