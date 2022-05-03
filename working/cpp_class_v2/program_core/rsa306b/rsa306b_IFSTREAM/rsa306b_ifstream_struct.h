/*
    variables needed for the API group "IFSTREAM" 

    make sure DEVICE_Run() is called at least once before using

    start and stop the IFSTREAM and DEVICE enables to match work

    client must take internal buffers before they over flow, check rate

    <file path> <filename base> <suffix> . <ext>  // use ".r3f"
*/

#ifndef H_rsa306b_ifstream_struct
#define H_rsa306b_ifstream_struct


#include "../../control/resourcez.h"


struct rsa306b_ifstream_struct
{
    // SetDiskFilenameSuffix()
    int file_name_suffix;    // set from "resourcez.h", determines file suffix appended to output files

    // SetDiskFilePath()
    char file_path[BUF_B]; // path ADC data is saved to

    // SetDiskFilenameBase()
    char file_name_base[BUF_B];// base name of the ADC data files

    // SetDiskFileLength()
    int file_length_ms; // sets recording time in ms of the ADC data

    // SetDiskFileCount()
    int file_count; // sets maximum number of files to save

    // SetOutoutConfiguration(), to set destination data type
    RSA_API::IFSOUTDEST output_configuration_select; // {0: no file, direct to client, 1:r3f, 3:r3h+r3a, 11:CDIF, 12:CDIF+DET}

    // GetActiveStatus()
    bool is_active; // status of streaming to disk

    // SetEnable()
    bool is_enabled_adc; // ADC is enabled for streaming data


    //# TODO
    // build these later for real-time IF streaming, same parser:
    /*
    // GetEQParameters()
    int points_in_equalization_buffer; // number of points in the equalization buffer
    float** eq_frequency_getter; // receives internal buffer
    float** eq_amplitude_getter;// receives internal buffer
    float** eq_phase_getter;// receives internal buffer
    std::vector<float> eq_frequency_v; // collects "freq_getter" in Hz
    std::vector<float> eq_amplitude_v; // collects "ampl_getter" in dB
    std::vector<float> eq_phase_v; // collects "phase_getter" in degrees

    // GetIFFrames(), minimal information
    uint8_t* frame_data; // do not have to allocate, pointer to buffer with IF frames
    int frame_bytes; // frame data length, in bytes (includes data + footer)
    int number_of_frames; // number of of frames acquired

    // GetIFData(), lots of information
    int16_t* if_data_getter; // receives data buffer
    int if_data_length; // number of signed 16-bit samples returned
    RSA_API::IFSTRMDATAINFO data_info_type; // contains aquisition information, "aqcStatus" needs a bit check

    // GetIDDataBufferSize(),
    int data_buffer_size_bytes; // size in bytes that "if_data_getter" must be allocated (/2)
    // use "if_data_length" to get number of samples that will be returned

    // GetScalingParameters(), for custom processing and storage
    double scale_factor; // multiply data by this and you get equivelent of 50 ohm termination
    double scale_frequency; // IF frequency the scale factor applies

    // GetAcqParameters(), for the client to get data
    double if_bandwidth_hz;        // usuable IF signal bandwidth in Hz
    double samples_per_second;     // IF data sample rate in samples per second
    double if_center_frequency;    // IF frequency where original center frequency was translated
    */
};
typedef struct rsa306b_ifstream_struct rsa306b_ifstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_ifstream_struct.h
