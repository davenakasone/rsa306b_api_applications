/*
    developing the direct IF stream for "IFSTREAM" group
*/

#include "../testz.h"

//#define GET_ADC 54 // toggle


void task_994()
{
    printf("\n%s()  ,  getting IF stream direct to client, no files\n", __func__);
    {
        rsa306b_class rsa;
        rsa.device_connect();

        #ifdef GET_ADC    // develop IFSTREAM_GetIFData()

            rsa.vars.config.reference_level_dbm = -30;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            rsa.ifstream_set_vars();
            FILE* fptr = NULL;

            for (int kk = 0; kk < 10; kk++)
            {
                rsa.device_run();
                RSA_API::IFSTREAM_SetEnable(true);
                RSA_API::IFSTREAM_GetIFDataBufferSize(
                    &rsa.vars.ifstream.buffer_size_bytes, 
                    &rsa.vars.ifstream.number_of_samples);
                int16_t* data_getter = new int16_t[rsa.vars.ifstream.number_of_samples];
                if (!data_getter)
                {
                    #ifdef DEBUG_MIN
                        printf("\n\tfailure allocating '%s'\n", GET_NAME(data_getter));
                    #endif
                    RSA_API::IFSTREAM_SetEnable(false);
                    rsa.device_stop();
                    return;
                }
                RSA_API::IFSTREAM_GetIFData(
                    data_getter, 
                    &rsa.vars.ifstream.if_data_length, 
                    &rsa.vars.ifstream.data_info_type);
                rsa.vars.ifstream.adc_data_v.resize(rsa.vars.ifstream.if_data_length);
                RSA_API::IFSTREAM_SetEnable(false);
                rsa.device_stop();

                sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/getifdata_%d.txt", kk);
                printf("%s\n", rsa.vars.gp.helper);
                fptr = fopen(rsa.vars.gp.helper, "w");
                for (int ii = 0; ii < rsa.vars.ifstream.if_data_length; ii++)
                {
                    rsa.vars.ifstream.adc_data_v[ii] = data_getter[ii];
                    sprintf(rsa.vars.gp.holder, "%d,\n", rsa.vars.ifstream.adc_data_v[ii]);
                    fputs(rsa.vars.gp.holder, fptr);
                }
                printf("%4d)  bytes:  %d  ,  samples:  %d , actual samples: %d\n", 
                    kk, 
                    rsa.vars.ifstream.buffer_size_bytes, 
                    rsa.vars.ifstream.number_of_samples, 
                    rsa.vars.ifstream.if_data_length);
                delete[] data_getter; data_getter = NULL;
                fclose(fptr); fptr = NULL;
            }
            printf("data_info_type.acqStatus       :  %u\n", rsa.vars.ifstream.data_info_type.acqStatus);
            printf("data_info_type.timestamp       :  %ld\n", rsa.vars.ifstream.data_info_type.timestamp);
            printf("data_info_type.triggerCount    :  %d\n", rsa.vars.ifstream.data_info_type.triggerCount);
            printf("data_info_type.triggerIndices  :  %p\n", rsa.vars.ifstream.data_info_type.triggerIndices);

        #else    // develop IFSTREAM_GetIFFrames()

            rsa.vars.config.reference_level_dbm = -30;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
            rsa.ifstream_set_vars();
            rsa.print_ifstream();
            FILE* fptr = NULL;
            uint8_t* frame_data = NULL; // 

            rsa.device_run();
            RSA_API::IFSTREAM_SetEnable(true);
            RSA_API::IFSTREAM_GetIFFrames(
                &frame_data, 
                &rsa.vars.ifstream.frame_bytes, 
                &rsa.vars.ifstream.number_of_frames);

            printf("\nframe_data[end]  =  %u  ,  ADC samples:  %lu\n", 
                frame_data[rsa.vars.ifstream.frame_bytes-1], 
                rsa.vars.ifstream.number_of_frames*rsa.constants.ADC_SAMPLES_PER_FRAME);
            printf("frame_bytes      =  %d\n", rsa.vars.ifstream.frame_bytes);
            printf("number_frames    =  %d\n", rsa.vars.ifstream.number_of_frames);
            int samples_for_frame = rsa.vars.ifstream.frame_bytes / rsa.vars.ifstream.number_of_frames;
            long unsigned int placer = 0;
            rsa.vars.ifstream.framed_adc_data_v.resize(rsa.vars.ifstream.number_of_frames);
            for (int ii = 0; ii < rsa.vars.ifstream.number_of_frames; ii++)
            {
                rsa.vars.ifstream.framed_adc_data_v[ii].resize(rsa.constants.ADC_SAMPLES_PER_FRAME);
                for (int jj = 0; jj < samples_for_frame; jj++)
                {
                    rsa.vars.ifstream.framed_adc_data_v[ii][placer] = 
                        frame_data[ii*jj + jj] | frame_data[ii*jj + jj + 1];
                    placer++;
                    if (placer == rsa.constants.ADC_SAMPLES_PER_FRAME -1) 
                    {
                        placer = 0;
                        break;
                    }
                }
            }
            RSA_API::IFSTREAM_SetEnable(false);
            rsa.device_stop();
            for (int ii = 0; ii < rsa.vars.ifstream.number_of_frames; ii++)
            {
                sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/getifframe_%d.txt", ii);
                fptr = fopen(rsa.vars.gp.helper, "w");
                for (long unsigned int jj = 0; jj < rsa.constants.ADC_SAMPLES_PER_FRAME; jj++)
                {
                    sprintf(rsa.vars.gp.holder, "%d\n", rsa.vars.ifstream.framed_adc_data_v[ii][jj]);
                    fputs(rsa.vars.gp.holder, fptr);
                }
                fclose(fptr);
                fptr = NULL;
            }

        #endif
    }
    printf("\n%s()  ,  task complete\n", __func__);
}


/////////~~~~~~~~END>  task_994.cpp
