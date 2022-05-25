/*
    variables needed for the API group "IQBLK" 

    device is configured before use

    find out which data getter is fastest, only use that one
    the API has many good options, but speed is the priority
*/

#ifndef H_rsa306b_iqblk_struct
#define H_rsa306b_iqblk_struct


#include "../../control/resourcez.h"


struct rsa306b_iqblk_struct
{
    // IQBLK_GetAcqInfo()
    RSA_API::IQBLK_ACQINFO acq_info_type; // needs a bit-check

    // IQBLK_AquireData() ... automatic run state, configurations needed, no args
    // IQBLK_WaitForIQDataReady() ...nest this and contain
    int timeout_ms; // remove later
    bool data_is_ready; // remove later

    // IQBLK_GetIQData()
    // need to handle "errorDataNotReady"
    // even index stores "I" data, the real part
    // odd index stores "Q" data, the imaginary part
    //std::vector<float> iq_data_v; // to hold IQ data for processing...see if "cplx32_v" works
    float* data_iq; // scope to the function, remove this when done

    int actual_buffer_samples; // actual number of IQ sample pairs returned in IQ buffer
    int sample_pairs_requested; // IQ pairs requested by the user, max set in "IQBLK_SetIQRecordLength()"

    // IQBLK_GetIQDataCplx()
    // need to handle "errorDataNotReady"
    // for getting IQ block data record in "Cplx32" array
    std::vector<RSA_API::Cplx32> cplx32_v; // to hold IQ data in "Cplx32" structs
    RSA_API::Cplx32* cplx32; // scope to function, remove this when done
    // try to share "iq_buffer_sample_pairs" and "iq_sample_pairs_requested" if possible

    // IQBLK_GetDataDeinterleaved()
    // need to handle "errorDataNotReady"
    // for getting all the "I" and all the "Q" data isolated
    float* data_i; // scope to the function, remove this when done
    float* data_q; // scope to the function, remove this when done
    //std::vector<float> i_data_v; // to hold I data for processing...see if "cplx32_v" works
    //std::vector<float> q_data_v; // to hold Q data for processing...see if "cplx32_v" works
    // try to share "iq_buffer_sample_pairs" and "iq_sample_pairs_requested" if possible

    // IQBLK_GetIQSampleRate()
    // depends on IQ bandwidth, set bandwidth before querry
    double sample_rate; // samples per second ?

    // IQBLK_GetIQBandwidth(), IQBLK_SetIQBandwidth()
    double bandwidth_hz;    // IQ bandwidth in Hz [public to private]
    // IQBLK_GetMaxIQBandwidth()
    double max_bandwidth_hz; // largest IQ bandwidth possible
    // IQBLK_GetMinIQBandwidth()
    double min_bandwidth_hz; // smallest IQ bandwidth possible

    // IQBLK_GetIQRecordLength(), IQBLK_SetIARecordLength()
    int record_length; // the number of IQ data samples generated on each acquisition
    // has a range [ 2 : 104.8576e6 ] samples ?
    // IQBLK_GetMaxIQRecordLength()
    // 2 seconds is the max, bandwidth dependent
    int max_record_length; // largest IQ record length can be for 1 block "max samples"
};
typedef struct rsa306b_iqblk_struct rsa306b_iqblk_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqblk_struct.h

/*

    // Complex data type definitions
		typedef struct
		{
			float i;
			float q;
		} Cplx32;
		typedef struct
		{
			int32_t i;
			int32_t q;
		} CplxInt32;
		typedef struct
		{
			int16_t i;
			int16_t q;
		} CplxInt16;
*/