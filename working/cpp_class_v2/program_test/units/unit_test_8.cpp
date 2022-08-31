/*
    unit test # 8, "SPECTRUM"

    this group is fundametal to correct spectrum analysis

    goals:
        - getting, setting, copying, and gaurds work
        - valid configurations and changes are always passed to the device
*/

#include "../testz.h"

//#define UT8_a 1    // basic use
//#define UT8_b 2    // make some settings
//#define UT8_c 3    // read a spectrum trace, find peak
//#define UT8_d 4    // read a spectrum trace, write to csv
#define UT8_e 5      // scan, and move, graph output and look at antenna
#define UT8_f 6    // a custom spectogram is produced as a 2D matrix


void unit_test_8 (void)
{
    printf("\n%s()  ,  API group 'SPECTRUM'\n", __func__);
    {
        FILE* fptr = NULL;

        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();
        
        #ifdef UT8_a
            rsa.print_spectrum();
        #endif
        #ifdef UT8_b
            rsa.print_spectrum();
            
            rsa.vars.spectrum.settings_type.rbw = 60e3;
            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.vars.spectrum.settings_type.enableVBW = true;
            rsa.vars.spectrum.settings_type.traceLength = 6969;
            rsa.vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_Mil6dB;
            rsa.vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_Amp;
            
            rsa.vars.spectrum.is_enabled_measurement = true;
            for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
            {
                rsa.vars.spectrum.is_enabled_trace[ii] = true;
                rsa.vars.spectrum.detectors_select[ii] = RSA_API::SpectrumDetector_AverageVRMS;
            }
            rsa.spectrum_set_vars();
            rsa.print_spectrum();
        #endif
        #ifdef UT8_c
            // the spectrum group is automatically preset
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.vars.config.reference_level_dbm = -10.345;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.spectrum.settings_type.rbw = 10e3;
            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.vars.spectrum.settings_type.traceLength = 919;
            rsa.spectrum_set_vars();
            
            rsa.spectrum_aquire();
            rsa.spectrum_find_peak_index();
            printf("\npoints aquired:  %d  ,  peak index:  %d  ,  freq[%d]:  %lf  ,  pow[%d]:  %0.12f\n",
                rsa.vars.spectrum.trace_points_acquired[0],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.array_frequency[rsa.vars.spectrum.peak_index[0]],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.array_power[0][rsa.vars.spectrum.peak_index[0]]);
            rsa.print_spectrum();
        #endif
        #ifdef UT8_d
            // the spectrum group is automatically preset
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.vars.config.reference_level_dbm = -31.345;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.spectrum.settings_type.rbw = 10e3;
            rsa.vars.spectrum.settings_type.span = 100e6;
            rsa.vars.spectrum.settings_type.traceLength = 919;
            rsa.spectrum_set_vars();
            
            rsa.spectrum_aquire();
            rsa.spectrum_find_peak_index();
            rsa.print_spectrum();
            printf("\npoints aquired:  %d  ,  peak index:  %d  ,  freq[%d]:  %lf  ,  pow[%d]:  %f\n",
                rsa.vars.spectrum.trace_points_acquired[0],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.array_frequency[rsa.vars.spectrum.peak_index[0]],
                rsa.vars.spectrum.peak_index[0],
                rsa.vars.spectrum.array_power[0][rsa.vars.spectrum.peak_index[0]]);
            rsa.spectrum_write_csv();
        #endif
        #ifdef UT8_e
            int steps = 200;
            double step_size = 5e5;
            rsa.vars.config.center_frequency_hz = 50e6;
            rsa.vars.config.reference_level_dbm = -25.9;
            rsa.config_set_vars();

            snprintf(rsa.vars.gp.helper, BUF_E-1, "./program_test/data/outputs_txt/freq_v_pow.csv");
            fptr = fopen(rsa.vars.gp.helper, "w");

            rsa.vars.spectrum.settings_type.rbw = 1e3;
            rsa.vars.spectrum.settings_type.span = 5e6;
            rsa.vars.spectrum.settings_type.traceLength = 919;
            rsa.spectrum_set_vars();

            for (int ii = 0; ii < steps; ii++)
            {
                rsa.vars.config.center_frequency_hz = 50e6 + ii * step_size;
                rsa.config_set_vars();

                rsa.spectrum_aquire();
                rsa.spectrum_find_peak_index();
                printf("\ncenter freq:  %14.3lf  ,  freq[%4d]:  %14.3lf  ,  pow[%4d]:  %14.3f\n",
                    rsa.vars.config.center_frequency_hz,
                    rsa.vars.spectrum.peak_index[0],
                    rsa.vars.spectrum.array_frequency[rsa.vars.spectrum.peak_index[0]],
                    rsa.vars.spectrum.peak_index[0],
                    rsa.vars.spectrum.array_power[0][rsa.vars.spectrum.peak_index[0]]);
                
                snprintf(rsa.vars.gp.holder, BUF_F-1, "%0.3lf,%0.3f,\n", 
                    rsa.vars.spectrum.array_frequency[rsa.vars.spectrum.peak_index[0]], 
                    rsa.vars.spectrum.array_power[0][rsa.vars.spectrum.peak_index[0]]);
                fputs(rsa.vars.gp.holder, fptr);
            }
            fclose(fptr); fptr = NULL;
            printf("\n\tsee:  '%s'\n", rsa.vars.gp.helper);
        #endif
        #ifdef UT8_f
            int periods = 919;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.vars.config.reference_level_dbm = -25.9;
            rsa.config_set_vars();

            snprintf(rsa.vars.gp.helper, BUF_E-1, "./program_test/data/outputs_txt/freq_pow_time.csv");
            fptr = fopen(rsa.vars.gp.helper, "w");

            rsa.vars.spectrum.settings_type.rbw = 1e3;
            rsa.vars.spectrum.settings_type.span = 20e6;
            rsa.vars.spectrum.settings_type.traceLength = periods;
            rsa.spectrum_set_vars();
            for (int ii = 0; ii < periods; ii++)
            {
                rsa.spectrum_aquire();
                snprintf(rsa.vars.gp.holder, BUF_F-1, "%0.3lf,", rsa.vars.spectrum.array_frequency[ii]);
                fputs(rsa.vars.gp.holder, fptr);
                for (int jj = 0; jj < periods; jj++)
                {
                    if (jj == periods-1)
                    {
                        snprintf(rsa.vars.gp.holder, BUF_F-1, "%0.3f\n", rsa.vars.spectrum.array_power[0][jj]);
                    }
                    else
                    {
                        snprintf(rsa.vars.gp.holder, BUF_F-1, "%0.3f,", rsa.vars.spectrum.array_power[0][jj]);
                    }
                    fputs(rsa.vars.gp.holder, fptr);
                }
            }
            fclose(fptr); fptr = NULL;
            printf("\n\tsee:  '%s'\n", rsa.vars.gp.helper);
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_8.cpp
