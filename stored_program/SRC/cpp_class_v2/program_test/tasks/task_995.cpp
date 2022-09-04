/*
    chek the YK-3000 transmitter @ 315 MHz
    the antenna might only be good for around 150 MHz
*/

#include "../testz.h"
#define REPZ 7
extern rsa306b_class X_rsa;



void task_995()
{
    printf("\n%s()  ,  see if the antenna catches 315 MHz\n", __func__);
    {
        FILE* fptr = NULL;

        // setup
        X_rsa.device_disconnect();
        X_rsa.device_connect();
        
        X_rsa.vars.config.center_frequency_hz = 315e6;
        X_rsa.vars.config.reference_level_dbm = 1;
        X_rsa.config_set_vars();
        
        X_rsa.vars.spectrum.settings_type.rbw = 1e3;
        X_rsa.vars.spectrum.settings_type.span = 20e6;
        X_rsa.vars.spectrum.settings_type.traceLength = 919;
        X_rsa.spectrum_set_vars();
        
        X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_CLIENT;
        X_rsa.ifstream_set_vars();
        
        X_rsa.vars.iqblk.record_length = 1001;
        X_rsa.vars.iqblk.bandwidth_hz = 20e6;
        X_rsa.vars.iqblk.getter = X_rsa.constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED;
        X_rsa.iqblk_set_vars();
        
        X_rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
        X_rsa.vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;
        X_rsa.vars.iqstream.bandwidth = 20e6;                                     
        X_rsa.vars.iqstream.record_time_ms = 8;                                       
        X_rsa.vars.iqstream.buffer_multiplier = X_rsa.constants.IQSTREAM_BUFFER_X_2;     
        X_rsa.iqstream_set_vars();

        // get spectrum data "power vs frequency"
        for (int ii = 0; ii < REPZ; ii++)
        {
            X_rsa.spectrum_aquire();
            X_rsa.spectrum_find_peak_index();
            printf("%3d)  max@  %7.2lf MHz  ,  %7.2f dBm\n", 
                ii,
                X_rsa.vars.spectrum.array_frequency[X_rsa.vars.spectrum.peak_index[0]]/1e6,
                X_rsa.vars.spectrum.array_power[0][X_rsa.vars.spectrum.peak_index[0]]);
            X_rsa.spectrum_write_csv();
        }

        // get IF data "intermidiate frequency as it meets the ADC"
        for (int ii = 0; ii < REPZ; ii++)
        {
            sprintf(X_rsa.vars.gp.helper, "%sifstream_315MHz_%d.csv", 
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
        }
        fclose(fptr); 
        fptr = NULL;

        // get IQ data "intermidiate and quatrature, after mixing, but before FFT"
        for (int ii = 0; ii < REPZ; ii ++)
        {
            X_rsa.iqblk_acquire_data();
            printf(">>>%d  %s\n", ii, X_rsa.vars.gp.holder);
            printf("\t\trequested:  %d  ,  actual:  %d\n", 
                X_rsa.vars.iqblk.record_length, 
                X_rsa.vars.iqblk.actual_buffer_samples);
            printf("\t\tstd::vector,  cplx_v[%d].i=  %0.7f  ,  cplx_v[%d].q=  %0.7f\n", 
                REPZ, 
                X_rsa.vars.iqblk.cplx32_v[REPZ].i,
                REPZ, 
                X_rsa.vars.iqblk.cplx32_v[REPZ].q);
            
            snprintf(X_rsa.vars.gp.holder, BUF_F, "%sIQblk_315MHz_%d.csv",
                X_rsa.constants.DATA_DIRECTORY_PROCESSED,
                ii);
            X_rsa.iqblk_make_csv(X_rsa.vars.gp.holder);
        }
        // for (int ii = 0; ii < REPZ; ii ++)
        // {
        //     snprintf(X_rsa.vars.gp.holder, BUF_F, "%siqblk_315MHz_%d.csv",
        //         X_rsa.vars.gp.helper,
        //         ii);
        //     X_rsa.iqblk_acquire_data();
        //     X_rsa.iqblk_make_csv(X_rsa.vars.gp.holder);

        //     printf(">>>%d  %s\n", ii, X_rsa.vars.gp.holder);
        //     printf("\t\trequested:  %d  ,  actual:  %d\n", 
        //         X_rsa.vars.iqblk.record_length, 
        //         X_rsa.vars.iqblk.actual_buffer_samples);
        //     printf("\t\tstd::vector,  cplx_v[%d].i=  %0.7f  ,  cplx_v[%d].q=  %0.7f\n", 
        //         REPZ, 
        //         X_rsa.vars.iqblk.cplx32_v[REPZ].i,
        //         REPZ, 
        //         X_rsa.vars.iqblk.cplx32_v[REPZ].q);
        // }

        // iqstream is better
        for (int xx = 0; xx < REPZ; xx++)
        {
            X_rsa.iqstream_acquire_data();
            printf("%d)  pairs copied:  %d  ,  cplx32_v.size() = %lu  ,  cplx32_v[%d].i =  %f  ,  cplx32_v[%d].q = %f\n",
                xx,
                X_rsa.vars.iqstream.pairs_copied,
                X_rsa.vars.iqstream.cplx32_v.size(),
                REPZ,
                X_rsa.vars.iqstream.cplx32_v[REPZ].i,
                REPZ,
                X_rsa.vars.iqstream.cplx32_v[REPZ].q);

                snprintf(X_rsa.vars.gp.helper, BUF_E-1, "%sIQstream_315MHz_%d.csv",
                    X_rsa.constants.DATA_DIRECTORY_PROCESSED,
                    xx);
                X_rsa.iqstream_make_csv(X_rsa.vars.gp.helper);
        }
    }
    printf("\n%s()  ,  task complete, adjust as needed\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


/////////~~~~~~~~END>  task_995.cpp
