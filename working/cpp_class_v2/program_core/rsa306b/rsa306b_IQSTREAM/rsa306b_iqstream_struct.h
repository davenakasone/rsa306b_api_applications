/*
    variables needed for the API group "IQSTREAM" 

    device is configured before use

    this group places a heavy load on the CPU
    watch acqStatus to ensure speed is sufficient
*/

#ifndef H_rsa306b_iqstream_struct
#define H_rsa306b_iqstream_struct


#include "../../control/resourcez.h"


struct rsa306b_iqstream_struct
{

// IQSTREAM_GetMaxAcqBandwidth()
    double max_bandwidth_hz;    // highest IQ bandwidt the stream can support

// IQSTREAM_GetMinAcqBandwidth()
    double min_bandwidth_hz;    // lowest IQ bandwidth the stream can support

// IQSTREAM_ClearAcqStatus()
// resets "sticky" status bits of "acqStatus", good for client and destination

// IQSTREAM_GetAcqParameters()
// reports processing parameters, given requested bandwidth (set first)
    double actual_bandwidth_hz;    // actual bandwidth IQ stream is being streamed
    double sample_rate;            // sample rate of IQ stream in samples per second

// IQSTREAM_GetDiskFileInfo()
// returns information about previous file output operation
    RSA_API::IQSTRMFILEINFO file_info;    // struct with file information
        // numberSamples: number of IQ sample pairs written to the output file
        // sample0Timestamp: timestamp of the first sample written to the output file
        // triggerSampleIndex: sample index where the trigger event occured, only valid if trigger enabled
        // triggerTimestamp: timestamp of the trigger event, only valid if trigger enabled
        // filenames: uses a wchar_t**, [0]= file name, [1]= header file name, handle the wide character
            // stored in an internal static buffer
    char* name_of_file[BUF_C];      // for file_info.filenames[0], UTF8 to ASCII
    char* name_of_header[BUF_C];    // for file_info.filenames[1], UTF8 to ASCII
        // acqStatus: status for the run interval, sticky and running bit-check required

// IQSTREAM_GetDiskFileWriteStatus()
// to monitor the output file progress
// valid after IQSTREAM_Start(), only need "is_complete" if no trigger used
// infinite file length only is complete when IQSTREAM_Stop() is called
// when triggering, use "is_writting" to abort if no trigger events occur
    // bool is_complete;  state of IQ stream file writing
    // bool is_writing;  useful when triggereing is used, NULL otherwise

// IQSTREAM_GetEnable()
// current IQ stream processing state
    bool is_enabled;  // the stream is or is not ready for output generation

// IQSTREAM_GetIQData()
// IQSTREAM_
// IQSTREAM_
// IQSTREAM_
// IQSTREAM_
// IQSTREAM_
// IQSTREAM_
};
typedef struct rsa306b_iqstream_struct rsa306b_iqstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqstream_struct.h
IQSTREAM_GetMaxAcqBandwidth()
IQSTREAM_GetMinAcqBandwidth()
IQSTREAM_ClearAcqStatus()
IQSTREAM_GetAcqParameters()
IQSTREAM_GetDiskFileInfo()
IQSTREAM_GetDiskFileWriteStatus()
IQSTREAM_GetEnable()
IQSTREAM_GetIQData()