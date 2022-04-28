/*
    variables needed for the API group "IFSTREAM" 

    make sure DEVICE_Run() is called at least once before using

    start and stop the IFSTREAM and DEVICE enables to match work

    client must take internal buffers before they over flow, check rate
*/

#ifndef H_rsa306b_ifstream_struct
#define H_rsa306b_ifstream_struct


#include "../../control/resourcez.h"


struct rsa306b_ifstream_struct
{
    // SetDiskFilenameSuffix()
    int file_suffix;    // set from "resourcez.h", determines file suffix appended to output files

    // GetActiveStatus()
    bool is_enabled_adc; // ADC is enabled for streaming data

    // SetEnable()
    bool is_streaming; // start or stop streaming to disk

    // SetDiskFilePath
    char file_path[BUF_B]; // path ADC data is saved to

    // SetDiskFilenameBase()
    char base_name[BUF_B];// base name of the ADC data files

    // SetDiskFileLength()
    int recording_length_ms; // sets recording time in ms of the ADC data

    // SetDiskFileCount()
    int files_to_save; // sets maximum number of files to save

    // GetScalingParameters(), for custom processing and storage
    double scale_factor; // multiply data by this and you get equivelent of 50 ohm termination
    double scale_frequency; // IF frequency the scale factor applies

    // GetAcqParameters(), for the client to get data
    double if_bandwidth_hz;        // usuable IF signal bandwidth in Hz
    double samples_per_second;     // IF data sample rate in samples per second
    double if_center_frequency;    // IF frequency where original center frequency was translated

    // GetEQParameters()
    int points_in_equalization_buffer; // number of points in the equalization buffer
    //float
    // ?

    // GetIFFrames(), 
    //uint8_t 

    // SetOutoutConfiguration(), to set destination data type
    RSA_API::IFSOUTDEST output_configuration_select; // {0: no file, direct to client, 1:r3f, 3:r3h+r3a, 11:CDIF, 12:CDIF+DET}
    
};
typedef struct rsa306b_ifstream_struct rsa306b_ifstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_ifstream_struct.h
