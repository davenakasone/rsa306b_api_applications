/*
    unit test # 9, API group "IFSTREAM"

    this section is used to write .r3f files
    more capabilities should be added to handle real-time ADC processing
    IF data is the basis for time-domain calculations

    goals:
        - getters, setters, copiers working correctly
        - a valid "*.r3f" file can be written
        - client can receive the data stream
*/

#include "../testz.h"

//#define UT9_a 1    // basic test
//#define UT9_b 2    // make an output file
//#define UT9_c 3    // make several output files and process them to raw ADC
#define UT9_d 4    // ADC data direct to client, entire buffer
#define UT9_e 5    // ADC data direct to client, entire buffer, frame by frame

void unit_test_9 (void)
{
    printf("\n%s()  ,  API group 'IFSTREAM'\n", __func__);
    {
        FILE* fptr = NULL;
        rsa306b_class rsa;
        cpu_timer_class cpu;
        r3f_manager_class r3f;
        rsa.device_connect();

        #ifdef UT9_a
            rsa.print_ifstream();

            rsa.vars.ifstream.file_count = 3;
            rsa.vars.ifstream.file_length_ms = 3000;
            strcpy(rsa.vars.ifstream.file_name_base, "toppy");
            rsa.vars.ifstream.file_name_suffix = 9;
            strcpy(rsa.vars.ifstream.file_path, "sloppy");
            rsa.vars.ifstream.is_enabled_adc = true;
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_MIDAS_DET;
            rsa.ifstream_set_vars();
            
            rsa.print_ifstream();
        #endif
        #ifdef UT9_b
            rsa.vars.config.reference_level_dbm = -45;
            rsa.vars.config.center_frequency_hz = 150e6;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.ifstream.file_count = 1;
            rsa.vars.ifstream.file_length_ms = 30;
            //strcpy(rsa.vars.ifstream.file_name_base, "tryR3F");
            rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_TIMESTAMP;
            //strcpy(rsa.vars.ifstream.file_path, "./program_test/data/outputs_r3f/");
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            rsa.ifstream_set_vars();

            rsa.ifstream_record_file(); // using default settings
            rsa.print_ifstream();
        #endif
        #ifdef UT9_c
            rsa.vars.config.reference_level_dbm = -45;
            rsa.vars.config.center_frequency_hz = 150e6;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.ifstream.file_length_ms = 10;
            rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_TIMESTAMP;
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            rsa.ifstream_set_vars();
            rsa.print_ifstream();

            int repz = 3;
            for (int ii = 0; ii < repz; ii++)
            {
                rsa.ifstream_record_file();
            }
            r3f.prepare_plot_from_adc(rsa.vars.ifstream.file_path, rsa.vars.constants.IFSTREAM_CSV_PATH);
        #endif
        #ifdef UT9_d
            rsa.vars.config.reference_level_dbm = -30;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.vars.spectrum.settings_type.rbw = 1e5;
            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.spectrum_set_vars();
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            rsa.ifstream_set_vars();
            for (int ii = 0; ii < 3*UT9_d; ii++)
            {
                sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/getifdata_%d.txt", ii);
                fptr = fopen(rsa.vars.gp.helper, "w");
                rsa.ifstream_acquire_adc_data();
                sprintf(rsa.vars.gp.holder, "%4d)  bytes:  %d  ,  samples:  %d , actual samples: %d\n", 
                    ii, 
                    rsa.vars.ifstream.buffer_size_bytes, 
                    rsa.vars.ifstream.number_of_samples, 
                    rsa.vars.ifstream.if_data_length);
                fputs(rsa.vars.gp.holder, fptr);
                sprintf(rsa.vars.gp.holder, "data_info_type.acqStatus       :  %u\n", 
                    rsa.vars.ifstream.data_info_type.acqStatus);
                fputs(rsa.vars.gp.holder, fptr);
                sprintf(rsa.vars.gp.holder, "data_info_type.timestamp       :  %ld\n", 
                    rsa.vars.ifstream.data_info_type.timestamp);
                fputs(rsa.vars.gp.holder, fptr);
                sprintf(rsa.vars.gp.holder, "data_info_type.triggerCount    :  %d\n", 
                    rsa.vars.ifstream.data_info_type.triggerCount);
                fputs(rsa.vars.gp.holder, fptr);
                sprintf(rsa.vars.gp.holder, "data_info_type.triggerIndices  :  %p\n\n", 
                    rsa.vars.ifstream.data_info_type.triggerIndices);
                fputs(rsa.vars.gp.holder, fptr);
                for (int jj = 0; jj < rsa.vars.ifstream.if_data_length; jj++)
                {
                    sprintf(rsa.vars.gp.holder, "%d,\n", rsa.vars.ifstream.adc_data_v[jj]);
                    fputs(rsa.vars.gp.holder, fptr);
                }
                printf("entire ADC buffer acquired, see:  '%s'\n", rsa.vars.gp.helper);
                fclose(fptr); fptr = NULL;
            }
            rsa.print_ifstream();
        #endif
        #ifdef UT9_e
            rsa.vars.config.reference_level_dbm = -30;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.vars.spectrum.settings_type.rbw = 1e5;
            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.spectrum_set_vars();
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            rsa.ifstream_set_vars();
            for (int ii = 0; ii < 3*UT9_e; ii++)
            {
                sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/getifdata_framed_%d.txt", ii);
                fptr = fopen(rsa.vars.gp.helper, "w");
                rsa.ifstream_acquire_adc_frames();

                sprintf(rsa.vars.gp.holder, "%4d)  frame bytes:  %d  ,  number of frames:  %d , actual samples: %lu\n\n", 
                    ii, 
                    rsa.vars.ifstream.frame_bytes, 
                    rsa.vars.ifstream.number_of_frames, 
                    rsa.vars.constants.ADC_SAMPLES_PER_FRAME*rsa.vars.ifstream.number_of_frames);
                fputs(rsa.vars.gp.holder, fptr);

                for (long unsigned int jj = 0; jj < rsa.vars.ifstream.framed_adc_data_v.size(); jj++)
                {
                    for (long unsigned int kk = 0; kk < rsa.vars.ifstream.framed_adc_data_v[ii].size(); kk++)
                    {
                        sprintf(rsa.vars.gp.holder, "%d,\n", rsa.vars.ifstream.framed_adc_data_v[jj][kk]);
                        fputs(rsa.vars.gp.holder, fptr);     
                    }
                }
                printf("entire ADC buffer acquired, by frame, see:  '%s'\n", rsa.vars.gp.helper);
                fclose(fptr); fptr = NULL;
            }
            rsa.print_ifstream();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_9.cpp
