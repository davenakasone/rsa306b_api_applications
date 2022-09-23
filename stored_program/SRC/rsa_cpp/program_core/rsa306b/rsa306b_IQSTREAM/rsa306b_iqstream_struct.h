/*
    variables needed for the API group "IQSTREAM" 
    IQSTREAM_GetMaxAcqBandwidth()
    IQSTREAM_GetMinAcqBandwidth()
    IQSTREAM_ClearAcqStatus()
    IQSTREAM_GetAcqParameters()
    IQSTREAM_GetDiskFileInfo()
    IQSTREAM_GetDiskFileWriteStatus()
    IQSTREAM_GetEnable()
    IQSTREAM_GetIQData()
    IQSTREAM_GetIQDataBufferSize()
    IQSTREAM_SetAcqBandwidth()
    IQSTREAM_SetDiskFileLength()
    IQSTREAM_SetDiskFilenameBase()
    IQSTREAM_SetDiskFilenameSuffix()
    IQSTREAM_SetDataBufferSize()
    IQSTREAM_SetOutputConfiguration()
    IQSTREAM_Start()
    IQSTREAM_Stop()
    IQSTREAM_WaitForIQDataReady()

    active :

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"

    device must be configured before use

    this group places a heavy load on the CPU
    watch acqStatus to ensure speed is sufficient
    wchar_t to char is used to identify "*.siq" file outputs

    there are 2x "acqStatus", but only one is valid at a time
    depends if streaming to a client or file
*/

#ifndef H_rsa306b_iqstream_struct
#define H_rsa306b_iqstream_struct


#include "../../control/resourcez.h"


// constexpr helpers
constexpr char IQSTREAM_FILE_NAME_BASE[] = "iqstream";
constexpr int IQSTREAM_BITCHECKS         =  13;    //  status bits [0:5], [16:21], + summary, for both "*acqStatus" 
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


struct rsa306b_iqstream_struct
{
    char acqStatus_message[IQSTREAM_BITCHECKS][BUF_C];    // maintains results of both "acqStatus" vars
   
/*
    IQSTREAM_Start()
        initializes the IQ stream and begins data output
        check for allocation and correct file opening
        data flow starts after call, have collection point ready
        use TRIG_ForceTrigger() if trigger event does not occur
*/

/*
    IQSTREAM_Stop()
        stream halts, output stops
*/

/*
    IQSTREAM_ClearAcqStatus()
        resets "sticky" status bits of "acqStatus"
        good for client and destination
*/

/*
    IQSTREAM_WaitForIQDataReady()
        blocks until IQ stream is ready or timeout is reached
        use a timeout=0 for hard poll
        local variables :
            int  timeout_ms
            bool is_ready
*/

/*
    IQSTREAM_GetDiskFileWriteStatus()
        to monitor the output file progress
        valid after IQSTREAM_Start(), only need "is_complete" if no trigger used
        infinite file length only is complete when IQSTREAM_Stop() is called
        when triggering, use "is_writting" to abort if no trigger events occur
        local variables :    
            bool is_complete    // state of IQ stream file writing
            bool is_writing     // useful when triggereing is used, NULL otherwise

*/


// IQSTREAM_SetAcqBandwidth()
// user requests acquisition bandwidth here
// sets to closest legal range, see table p.78
// determines output sample rate when set, should be first parameter set
// instrument must stop, then set the bandwidth; new setting takes effect next run()
    double bandwidth;    // bandwidth of acquisition in Hz

// IQSTREAM_GetMaxAcqBandwidth()
    double bandwidth_max;    // highest IQ bandwidth the stream can support

// IQSTREAM_GetMinAcqBandwidth()
    double bandwidth_min;    // lowest IQ bandwidth the stream can support

// IQSTREAM_GetAcqParameters()
// reports processing parameters, given requested bandwidth (set first)
    //share "bandwidth_hz"
    double sample_rate;    // sample rate of IQ stream in samples per second

// IQSTREAM_GetDiskFileInfo()
// returns information about previous file output operation
    RSA_API::IQSTRMFILEINFO fileinfo_type;    // struct with file information
        // numberSamples: number of IQ sample pairs written to the output file
        // sample0Timestamp: timestamp of the first sample written to the output file
        // triggerSampleIndex: sample index where the trigger event occured, only valid if trigger enabled
        // triggerTimestamp: timestamp of the trigger event, only valid if trigger enabled
        // filenames: uses a wchar_t**, [0]= file name, [1]= header file name, handle the wide character
            // stored in an internal static buffer...see addition to "RSA_API.h"
            //char name_of_file[BUF_D];      // for file_info.filenames[0], UTF8 to ASCII "wchar_t* to char*"
            //char name_of_header[BUF_D];    // for file_info.filenames[1], UTF8 to ASCII "wchar_t* to char*"
        // acqStatus: status for the run interval, sticky and running bit-check required

// IQSTREAM_GetEnable()
// current IQ stream processing state
    bool is_enabled;    // the stream is or is not ready for output generation

// IQSTREAM_GetIQData()
// allows client application to retrieve IQ blocks created by the stream
// data blocks are copied out of the buffer, allocate "iq_data", call IQSTREAM_GetBufferSize()
// any pointer type will be accepted, but try to use the Cplx* predefined types
// don't poll "pairs_copied" in a tight loop
// must collect data to keep up with (samples per second / max size)
// internal buffer can only hold 500 msec of IQ stream
    //void* data_buffer;                  // pointer to the IQ buffer
    int pairs_copied;                   // sample IQ pairs copied from the IQ buffer, 0= no data availible
    RSA_API::IQSTRMIQINFO info_type;    // struct with stream information, NULL if not wanted
        // timestamp: timestamp of the first sample in the block
        // triggerCount: number of trigger events that occured in the block, max of 100 allowed
        // triggerIndices: list of sample indices where trigger occured, overwritten after 100
        // scaleFactor: converts int16 and int32 data to standard voltage values, 1.0 for floats
        // acqStatus: status flags for run, needs a bit-check, clear sticky
    // collections stored in std::vector according to format selected
    std::vector<RSA_API::Cplx32> cplx32_v;
    std::vector<RSA_API::CplxInt16> cplxInt16_v;
    std::vector<RSA_API::CplxInt32> cplxInt32_v;

// IQSTREAM_GetIQDataBufferSize()
// maximum number of IQ samples IQSTREAM_GetIQData() can return
// only applicable if client receives the IQ stream directly
// to set buffer size, first IQSTREAM_SetAcqBandwidth()
// buffer size depends on bandwidth
    int pairs_max;   // depends on buffer multiple, user only needs multiple 

// IQSTREAM_SetDiskFileLength()
// 0: no time limit, must call IQSTREAM_Stop() to terminate storage
// >0: file output ends after specified milli-seconds
    int record_time_ms;    // time period in milli-seconds IQ stream is written to file

// complete output file:  <filenameBase><suffix><.ext>
// <filenameBase> is set by IQSTREAM_SetDiskFilenameBase()
// <suffix> is set by IQSTREAM_SetDiskFilenameSuffix()
// <.ext> is set by IQSTREAM_SetOutputConfiguration()
// if seperate data and header files are made, the names and paths are identical, extension changes

// IQSTREAM_SetDiskFilenameBase()
// not using the wide character function
// do not include extension, that is automatically placed
    char filename_base[BUF_C];

// IQSTREAM_SetDiskFilenameSuffix()
// determine what is appended to the base filename
// -2  :  no suffix, must change output files manually
// -1  :  timestamp as suffix
// >=0 : 5-digit auto incrementing index, each Start()
    int suffix_control;

// IQSTREAM_SetDataBufferSize()
// user requests IQ sample pairs to be returned
// 0: resets to default
// 1: resets to minimum size
// 1,000,000: resets to maximum size...see p82
// only valid if the client directly receives the IQ stream
    // works with pairs max 
    int buffer_multiplier;

// IQSTREAM_SetOutputConfiguration()
// output destination and type
// any valid destination
// any valid data type, but use the existing types
// stream is interleaved IQIQIQ...
    RSA_API::IQSOUTDEST destination_select;    // where the stream will be sent
    RSA_API::IQSOUTDTYPE datatype_select;      // what data type to stream
};
typedef struct rsa306b_iqstream_struct rsa306b_iqstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqstream_struct.h
