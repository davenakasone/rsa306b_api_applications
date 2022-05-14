/*
    raw ADC and spectrum
    one run at 315 MHz,
    other at 100 MHz
*/

#include "../testz.h"

//#define CF315 315

void task_992()
{
    printf("\n%s()  ,  make 100 MHz and 315 MHz, control the macro\n", __func__);
    {
        int reps = 10;    // for ADC and spectrum, for training
        FILE* fptr = NULL;
        int16_t* data_getter = NULL;
        rsa306b_class rsa;
        rsa.device_connect();

        #ifdef CF315
            rsa.vars.config.center_frequency_hz = 315e6;
            rsa.vars.config.reference_level_dbm = -13;
            rsa.vars.spectrum.settings_type.rbw = 1e3;
            rsa.vars.spectrum.settings_type.span = 1e6;
        #else
            rsa.vars.config.reference_level_dbm = -35;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.vars.spectrum.settings_type.rbw = 0.1e6;
            rsa.vars.spectrum.settings_type.span = 20e6;
        #endif
        rsa.config_set_vars();
        rsa.vars.spectrum.settings_type.traceLength = 1001;
        rsa.spectrum_set_vars();
        rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
        rsa.ifstream_set_vars();

// get the ADC data, test
        #ifdef CF315
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/adc_test_315.csv");
        #else
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/adc_test_100.csv");
        #endif
        printf("\n%s  ,  ", rsa.vars.gp.helper);
        fptr = fopen(rsa.vars.gp.helper, "w");
        sprintf(rsa.vars.gp.holder, "x,y,\n");
        fputs(rsa.vars.gp.holder, fptr);
        rsa.device_run();
        RSA_API::IFSTREAM_SetEnable(true);
        RSA_API::IFSTREAM_GetIFDataBufferSize(
            &rsa.vars.ifstream.buffer_size_bytes, 
            &rsa.vars.ifstream.number_of_samples);
        data_getter = new int16_t[rsa.vars.ifstream.number_of_samples];
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
        for (int ii = 0; ii < rsa.vars.ifstream.if_data_length; ii++)
        {
            rsa.vars.ifstream.adc_data_v[ii] = data_getter[ii];
            sprintf(rsa.vars.gp.holder, "%d,%d,\n", 
                ii,
                rsa.vars.ifstream.adc_data_v[ii]);
            fputs(rsa.vars.gp.holder, fptr);
        }
        delete[] data_getter; data_getter = NULL;
        fclose(fptr); fptr = NULL;
        printf("  samples:  %d  ,  frames:  %d  ,  samples per frame:  %ld\n", 
            rsa.vars.ifstream.if_data_length,
            (int)(rsa.vars.ifstream.if_data_length/rsa.vars.constants.ADC_SAMPLES_PER_FRAME),
            rsa.vars.constants.ADC_SAMPLES_PER_FRAME);

// get the ADC data, train
        #ifdef CF315
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/adc_train_315.csv");
        #else
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/adc_train_100.csv");
        #endif
        printf("\n%s  ,  ", rsa.vars.gp.helper);
        fptr = fopen(rsa.vars.gp.helper, "w");
        sprintf(rsa.vars.gp.holder, "x,y,\n");
        fputs(rsa.vars.gp.holder, fptr);
        for (int ii = 0; ii < reps; ii++)
        {
            rsa.device_run();
            RSA_API::IFSTREAM_SetEnable(true);
            RSA_API::IFSTREAM_GetIFDataBufferSize(
                &rsa.vars.ifstream.buffer_size_bytes, 
                &rsa.vars.ifstream.number_of_samples);
            data_getter = new int16_t[rsa.vars.ifstream.number_of_samples];
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
            for (int jj = 0; jj < rsa.vars.ifstream.if_data_length; jj++)
            {
                rsa.vars.ifstream.adc_data_v[jj] = data_getter[jj];
                sprintf(rsa.vars.gp.holder, "%d,%d,\n", 
                    jj,
                    rsa.vars.ifstream.adc_data_v[jj]);
                fputs(rsa.vars.gp.holder, fptr);
            }
            delete[] data_getter; data_getter = NULL;
        }
        fclose(fptr); fptr = NULL;
        printf("  samples:  %d  ,  frames:  %d  ,  samples per frame:  %ld\n", 
            rsa.vars.ifstream.if_data_length*reps,
            (int)(rsa.vars.ifstream.if_data_length/rsa.vars.constants.ADC_SAMPLES_PER_FRAME),
            rsa.vars.constants.ADC_SAMPLES_PER_FRAME);

// get the spectrum data
        #ifdef CF315
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/spec_test_315.csv");
        #else
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/spec_test_100.csv");
        #endif
        printf("\n%s  ,  ", rsa.vars.gp.helper);
        fptr = fopen(rsa.vars.gp.helper, "w");
        sprintf(rsa.vars.gp.holder, "x,y,\n");
        fputs(rsa.vars.gp.holder, fptr);
        rsa.spectrum_aquire();
        for (int ii = 0; ii < rsa.vars.spectrum.trace_points_acquired[0]; ii++)
        {
            sprintf(rsa.vars.gp.holder, "%0.3lf,%0.3f,\n",
                    rsa.vars.spectrum.array_frequency[ii],
                    rsa.vars.spectrum.array_power[0][ii]);
                fputs(rsa.vars.gp.holder, fptr);
        }
        fclose(fptr); fptr = NULL;
        printf("  bins:  %d  with  frames:  %d\n",
            rsa.vars.spectrum.trace_points_acquired[0],
            rsa.vars.spectrum.trace_points_acquired[0]/rsa.vars.spectrum.settings_type.traceLength);

// get the spectrum data, training
        #ifdef CF315
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/spec_train_315.csv");
        #else
            sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/spec_train_100.csv");
        #endif
        printf("\n%s  ,  ", rsa.vars.gp.helper);
        fptr = fopen(rsa.vars.gp.helper, "w");
        sprintf(rsa.vars.gp.holder, "x,y,\n");
        fputs(rsa.vars.gp.holder, fptr);
        for (int ii = 0; ii < reps; ii++)
        {
            rsa.spectrum_aquire();
            for (int jj = 0; jj < rsa.vars.spectrum.trace_points_acquired[0]; jj++)
            {
                sprintf(rsa.vars.gp.holder, "%0.3lf,%0.3f,\n",
                    rsa.vars.spectrum.array_frequency[jj],
                    rsa.vars.spectrum.array_power[0][jj]);
                fputs(rsa.vars.gp.holder, fptr);
            }
        }
        fclose(fptr); fptr = NULL;
        printf("  bins:  %d  with  frames:  %d\n",
            rsa.vars.spectrum.trace_points_acquired[0]*reps,
            rsa.vars.spectrum.trace_points_acquired[0]*reps/rsa.vars.spectrum.settings_type.traceLength);
    }
    printf("\n%s()  ,  task complete\n", __func__);
}


/////////~~~~~~~~END>  task_992.cpp
