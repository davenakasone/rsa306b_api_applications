/*
    variables needed for the API group "IQBLK" 

    device is configured before use

    find out which data getter is fastest, only use that one
    the API has many good options, but speed is the priority
*/

#ifndef H_rsa306b_iqblk_struct
#define H_rsa306b_iqblk_struct


#include "../rsa306b_constants.h"


struct rsa306b_iqblk_struct
{
    // managing the 3 API data acquistion functions for the IQBLK group
    // all acquistions handle "errorDataNotReady"
    uint8_t getter;                               // determines the API function to get data, see "resourcez.h"
    int actual_buffer_samples;                // actual number of IQ sample pairs returned in IQ buffer
    //int sample_pairs_requested;               // IQ pairs requested by the user, max set in "IQBLK_SetIQRecordLength()"
    std::vector<RSA_API::Cplx32> cplx32_v;    // "Cplx32" structs, all API acquistion functions are transfered here
        // IQBLK_GetIQData()
            // for getting a single IQ array
            // even index stores "I" data, the real part
            // odd index stores "Q" data, the imaginary part
            // float* data_iq;    // scoped to local function
        // IQBLK_GetIQDataCplx()
            // for getting IQ block data record directly in "Cplx32" array
            // RSA_API::Cplx32* cplx32;    // scoped to local function
        // IQBLK_GetIQDataDeinterleaved()
            // for getting all the "I" and all the "Q" data isolated
            // float* data_i;   // scoped to local function
            // float* data_q;   // scoped to local function

    // IQBLK_GetAcqInfo()
    RSA_API::IQBLK_ACQINFO acq_info_type;    // an API struct with 4 uint* variables
    char bitcheck[BUF_D];                    // contains bitcheck result and the status message

    // IQBLK_AquireData()... automatic run state, configurations needed, no args

    // IQBLK_WaitForIQDataReady()... scoped to the 3 "IQBLK_GetData*" API functions
        // int timeout_ms;        // scoped to local function
        // bool data_is_ready;    // scoped to local function

    // IQBLK_GetIQSampleRate()... depends on IQ bandwidth, set bandwidth before querry
    double sample_rate;    // samples per second

    // IQBLK_GetIQBandwidth() + IQBLK_SetIQBandwidth()
    double bandwidth_hz;        // IQ bandwidth in Hz [public sets, private gets]
    // IQBLK_GetMaxIQBandwidth()
    double max_bandwidth_hz;    // largest IQ bandwidth possible
    // IQBLK_GetMinIQBandwidth()
    double min_bandwidth_hz;    // smallest IQ bandwidth possible

    // IQBLK_GetIQRecordLength() + IQBLK_SetIARecordLength()
        // has a range [ 2 : 104.8576e6 ] sample pairs, [public sets, private gets]
    int record_length; // the number of IQ data samples generated on each acquisition
    // IQBLK_GetMaxIQRecordLength()
        // 2 seconds is the max, bandwidth dependent
    int max_record_length;    // largest IQ record length can be for 1 block "max samples"
};
typedef struct rsa306b_iqblk_struct rsa306b_iqblk_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqblk_struct.h
