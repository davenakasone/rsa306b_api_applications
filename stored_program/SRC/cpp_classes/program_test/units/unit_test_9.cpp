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

#define UT9_a 1    // basic test
#define UT9_b 2    // make an output file
#define UT9_c 3    // make several output files and process them to raw ADC
#define UT9_d 4    // ADC data direct to client, entire buffer
#define UT9_e 5    // ADC data direct to client, entire buffer, frame by frame
extern rsa306b_class X_rsa;
extern r3f_manager_class X_r3f;


void unit_test_9 (void)
{
    printf("\n%s()  ,  API group 'IFSTREAM'\n", __func__);
    {
        FILE* fptr = NULL;
        cpu_timer_class cpu;
        r3f_manager_class r3f;
        X_rsa.device_disconnect();
        X_rsa.device_connect();

        #ifdef UT9_a

            X_rsa.print_ifstream();

            X_rsa.vars.ifstream.file_count = 3;
            X_rsa.vars.ifstream.file_length_ms = 3000;
            strcpy(X_rsa.vars.ifstream.file_name_base, "toppy");
            X_rsa.vars.ifstream.file_name_suffix = 9;
            strcpy(X_rsa.vars.ifstream.file_path, "sloppy");
            X_rsa.vars.ifstream.is_enabled_adc = true;
            X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_MIDAS_DET;
            X_rsa.ifstream_set_vars();
            
            X_rsa.print_ifstream();

        #if defined (UT9_b) || (UT9_c) || (UT9_d) || (UT9_e)
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT9_b

            X_rsa.vars.config.reference_level_dbm = -45;
            X_rsa.vars.config.center_frequency_hz = 150e6;
            X_rsa.config_set_vars();
            X_rsa.print_config();

            X_rsa.vars.ifstream.file_count = 1;
            X_rsa.vars.ifstream.file_length_ms = 30;
            strcpy(X_rsa.vars.ifstream.file_name_base, X_rsa.constants.IFSTREAM_FILE_NAME_BASE);
            X_rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_TIMESTAMP;
            strcpy(X_rsa.vars.ifstream.file_path, X_rsa.constants.DATA_DIRECTORY_RAW);
            X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            X_rsa.ifstream_set_vars();

            X_rsa.ifstream_record_file(); // using default settings
            X_rsa.print_ifstream();

        #if (UT9_c) || (UT9_d) || (UT9_e)
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT9_c

            X_rsa.vars.config.reference_level_dbm = -45;
            X_rsa.vars.config.center_frequency_hz = 150e6;
            X_rsa.config_set_vars();
            X_rsa.print_config();

            X_rsa.vars.ifstream.file_length_ms = 10;
            X_rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_INCRINDEX_MIN;
            X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            X_rsa.ifstream_set_vars();
            X_rsa.print_ifstream();

            int repz = 3;
            for (int ii = 0; ii < repz; ii++)
            {
                X_rsa.ifstream_record_file();
            }
            X_r3f.prepare_plot_from_adc(X_rsa.vars.ifstream.file_path, X_rsa.constants.DATA_DIRECTORY_PROCESSED);
        
        #if defined (UT9_d) || (UT9_e)
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT9_d

            printf("\n");
            X_rsa.vars.config.reference_level_dbm = -30;
            X_rsa.vars.config.center_frequency_hz = 100e6;
            X_rsa.config_set_vars();
            X_rsa.vars.spectrum.settings_type.rbw = 1e5;
            X_rsa.vars.spectrum.settings_type.span = 1e6;
            X_rsa.spectrum_set_vars();
            X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            X_rsa.ifstream_set_vars();
            for (int ii = 0; ii < 3*UT9_d; ii++)
            {
                sprintf(X_rsa.vars.gp.helper, "%sgotIFdata_%d.csv", 
                    X_rsa.constants.DATA_DIRECTORY_PROCESSED,
                    ii);
                fptr = fopen(X_rsa.vars.gp.helper, "w");
                sprintf(X_rsa.vars.gp.helper, "ADC\n");
                fputs(X_rsa.vars.gp.helper, fptr);
                X_rsa.ifstream_acquire_adc_data();

                printf(X_rsa.vars.gp.holder, "%4d)  bytes:  %d  ,  samples:  %d , actual samples: %d\n", 
                    ii, 
                    X_rsa.vars.ifstream.buffer_size_bytes, 
                    X_rsa.vars.ifstream.number_of_samples, 
                    X_rsa.vars.ifstream.if_data_length);
                //fputs(X_rsa.vars.gp.holder, fptr);
                printf(X_rsa.vars.gp.holder, "data_info_type.acqStatus       :  %u\n", 
                    X_rsa.vars.ifstream.data_info_type.acqStatus);
                //fputs(X_rsa.vars.gp.holder, fptr);
                printf(X_rsa.vars.gp.holder, "data_info_type.timestamp       :  %lu\n", 
                    X_rsa.vars.ifstream.data_info_type.timestamp);
                //fputs(X_rsa.vars.gp.holder, fptr);
                printf(X_rsa.vars.gp.holder, "data_info_type.triggerCount    :  %d\n", 
                    X_rsa.vars.ifstream.data_info_type.triggerCount);
                //fputs(X_rsa.vars.gp.holder, fptr);
                printf(X_rsa.vars.gp.holder, "data_info_type.triggerIndices  :  %p\n\n", 
                    X_rsa.vars.ifstream.data_info_type.triggerIndices);
                //fputs(X_rsa.vars.gp.holder, fptr);
                for (int jj = 0; jj < X_rsa.vars.ifstream.if_data_length; jj++)
                {
                    if (jj == X_rsa.vars.ifstream.if_data_length-1)
                    {
                        sprintf(X_rsa.vars.gp.holder, "%d", X_rsa.vars.ifstream.adc_data_v[jj]);
                    }
                    else
                    {
                        sprintf(X_rsa.vars.gp.holder, "%d,\n", X_rsa.vars.ifstream.adc_data_v[jj]);
                    }
                    fputs(X_rsa.vars.gp.holder, fptr);
                }
                printf("entire ADC buffer acquired, see:  '%s'\n", X_rsa.vars.gp.helper);
                fclose(fptr); fptr = NULL;
            }
            X_rsa.print_ifstream();
        
        #ifdef UT9_e
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT9_e

            printf("\n");
            X_rsa.vars.config.reference_level_dbm = -30;
            X_rsa.vars.config.center_frequency_hz = 100e6;
            X_rsa.config_set_vars();
            X_rsa.vars.spectrum.settings_type.rbw = 1e5;
            X_rsa.vars.spectrum.settings_type.span = 1e6;
            X_rsa.spectrum_set_vars();
            X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            X_rsa.ifstream_set_vars();
            for (int ii = 0; ii < 5; ii++)
            {
                sprintf(X_rsa.vars.gp.helper, "%s/IFdata_frame_%d.csv", 
                    X_rsa.constants.DATA_DIRECTORY_PROCESSED,
                    ii);
                fptr = fopen(X_rsa.vars.gp.helper, "w");
                sprintf(X_rsa.vars.gp.helper, "ADC\n");
                fputs(X_rsa.vars.gp.helper, fptr);
                X_rsa.ifstream_acquire_adc_frames();

                printf(X_rsa.vars.gp.holder, "%4d)  frame bytes:  %d  ,  number of frames:  %d , actual samples: %lu\n\n", 
                    ii, 
                    X_rsa.vars.ifstream.frame_bytes, 
                    X_rsa.vars.ifstream.number_of_frames, 
                    X_rsa.constants.ADC_SAMPLES_PER_FRAME*X_rsa.vars.ifstream.number_of_frames);
                //fputs(X_rsa.vars.gp.holder, fptr);

                for (std::size_t jj = 0; jj < X_rsa.vars.ifstream.framed_adc_data_v.size(); jj++)
                {
                    for (std::size_t kk = 0; kk < X_rsa.vars.ifstream.framed_adc_data_v[ii].size(); kk++)
                    {
                        if (kk == X_rsa.vars.ifstream.framed_adc_data_v[ii].size()-1)
                        {
                            sprintf(X_rsa.vars.gp.holder, "%d", X_rsa.vars.ifstream.framed_adc_data_v[jj][kk]);
                        }
                        else
                        {
                            sprintf(X_rsa.vars.gp.holder, "%d,\n", X_rsa.vars.ifstream.framed_adc_data_v[jj][kk]);
                        }
                        fputs(X_rsa.vars.gp.holder, fptr);     
                    }
                }
                printf("entire ADC buffer acquired, by frame, see:  '%s'\n", X_rsa.vars.gp.helper);
                fclose(fptr); fptr = NULL;
            }
            X_rsa.print_ifstream();

        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_9.cpp
