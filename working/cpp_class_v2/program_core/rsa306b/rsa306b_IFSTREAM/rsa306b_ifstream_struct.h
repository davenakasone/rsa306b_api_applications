/*
    variables needed for the API group "IFSTREAM" 

    make sure DEVICE_Run() is called at least once before using

    start and stop the IFSTREAM and DEVICE enables in sequence

    where is the bit-check?
*/

#ifndef H_rsa306b_ifstream_struct
#define H_rsa306b_ifstream_struct


#include "../rsa306b_constants.h"


struct rsa306b_ifstream_struct
{

// using "SetOutoutConfiguration()"
// this determines if a file is produced
// "IFSTREAM_SetDiskFileMode()" is obsolete
    RSA_API::IFSOUTDEST output_configuration_select;    // to set destination data type
        // {0: no file, direct to client, 1:r3f, 3:r3h+r3a, 11:CDIF, 12:CDIF+DET}


// used internally to enable IF stream and query transfer status
// user should not alter, but can reference

    bool is_active;         // status of streaming to disk      , GetActiveStatus()
    bool is_enabled_adc;    // ADC is enabled for streaming data, SetEnable()


// for writting IF stream to a file
// <file path> <filename base> <suffix> . <ext> , use ".r3f"
// see "rsa306b_constants_class.h" for default settings

    int file_name_suffix;          // determines file suffix appended to output files, SetDiskFilenameSuffix()
    char file_path[BUF_B];         // path ADC data is saved to                      , SetDiskFilePath()
    char file_name_base[BUF_B];    // base name of the ADC data files                , SetDiskFilenameBase()
    int file_length_ms;            // sets recording time in ms of the ADC data      , SetDiskFileLength()
    int file_count;                // sets maximum number of files to save           , SetDiskFileCount()
    

// for receiving the IF stream directly into the program
// client must take internal buffers before they overflow
// check rate, and don't do to much processing until data is acquired
// internal dynamically allocated data types are supplemented with safer STL data types

    // GetIFData(), retrieves the entire ADC buffer
    // the API struct "IFSTRMDATAINFO" is what would be in the footer of a "*.r3f" file
    int if_data_length;                        // number of signed 16-bit samples returned
    RSA_API::IFSTRMDATAINFO data_info_type;    // contains aquisition information, "aqcStatus" needs a bit check
    std::vector<int16_t> adc_data_v;           // collects internal buffer "if_data_getter" is placed on

    // GetIFDataBufferSize(), call to prepare "GetIFData()"
    int buffer_size_bytes;    // size in bytes for "if_data_getter" when calling "GetIFData()" .../2
    int number_of_samples;    // number of 16-bit samples "GetIFData()" will return

    // GetIFFrames(), retrieves availible frames
    int frame_bytes;                                        // frame data length, in bytes (includes data + footer)
    int number_of_frames;                                   // number of of frames acquired
    std::vector<std::vector<int16_t>> framed_adc_data_v;    // frame index and ADC sample value
    
    // GetEQParameters(), this correction data is used for proper analysis
    int points_in_equalization_buffer;    // number of points in the equalization buffer
    std::vector<float> eq_frequency_v;    // collects "freq_getter" in Hz
    std::vector<float> eq_amplitude_v;    // collects "ampl_getter" in dB
    std::vector<float> eq_phase_v;        // collects "phase_getter" in degrees

    // GetScalingParameters(), to align data
    double scale_factor;       // multiply ADC data for equivelent of 50 ohm termination
    double scale_frequency;    // IF frequency the scale factor applies

    //GetAcqParameters(), for the client to get data
    double if_bandwidth_hz;        // usuable IF signal bandwidth in Hz
    double samples_per_second;     // IF data sample rate in samples per second
    double if_center_frequency;    // IF frequency where original center frequency was translated
};
typedef struct rsa306b_ifstream_struct rsa306b_ifstream_struct;


#endif


////////~~~~~~~~END>  rsa306b_ifstream_struct.h
