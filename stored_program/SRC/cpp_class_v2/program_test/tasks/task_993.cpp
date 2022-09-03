/*
    improvement for model training
    make as many CSV files as needed
*/

#include "../testz.h"

#define GENERATE_ADC 2000         // activate to make 'IFSTREAM' group data
#define GENERATE_SPECTRUM 3000    // activate to make 'SPECTRUM' group data


void task_993()
{
    printf("\n%s()  ,  make some files for learning\n", __func__);
    {
        
        FILE* fptr = NULL;
        int16_t* data_getter = NULL;
        rsa306b_class rsa;
        rsa.device_connect();

        rsa.vars.config.reference_level_dbm = -35;
        rsa.vars.config.center_frequency_hz = 100e6;
        rsa.config_set_vars();

        rsa.vars.spectrum.settings_type.rbw = 0.1e6;
        rsa.vars.spectrum.settings_type.span = 20e6;
        rsa.vars.spectrum.settings_type.traceLength = 1001;
        rsa.spectrum_set_vars();

        rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
        rsa.ifstream_set_vars();

        int reps = 10;    // for ADC and spectrum, for training

    #ifdef GENERATE_ADC

// get the raw data, testing
        sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/atest_data.csv");
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
            (int)(rsa.vars.ifstream.if_data_length/rsa.constants.ADC_SAMPLES_PER_FRAME),
            rsa.constants.ADC_SAMPLES_PER_FRAME);

// get the raw data, training
        sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/atrain_data.csv");
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
            (int)(rsa.vars.ifstream.if_data_length/rsa.constants.ADC_SAMPLES_PER_FRAME),
            rsa.constants.ADC_SAMPLES_PER_FRAME);

    #endif
    #ifdef GENERATE_SPECTRUM

// get the spectrum data, test
        sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/stest_data.csv");
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
        sprintf(rsa.vars.gp.helper, "./program_test/data/outputs_txt/strain_data.csv");
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

    #endif

    }
    printf("\n%s()  ,  task complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


/////////~~~~~~~~END>  task_993.cpp
