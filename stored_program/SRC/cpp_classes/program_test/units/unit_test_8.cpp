/*
    unit test # 8, "SPECTRUM"

    this group is fundametal to correct spectrum analysis

    goals:
        - getting, setting, copying, and gaurds work
        - valid configurations and changes are always passed to the device
*/

#include "../testz.h"

#define UT8_a 2    // make some settings
#define UT8_b 3    // read a spectrum trace, find peak
#define UT8_c 4    // read a spectrum trace, write to csv
#define UT8_d 5    // scan, and move, make csv
extern rsa306b_class X_rsa;


void unit_test_8 (void)
{
    printf("\n%s()  ,  API group 'SPECTRUM'\n", __func__);
    {
        cpu_timer_class cpu;
        X_rsa.device_disconnect();
        X_rsa.device_connect();
        
        #ifdef UT8_a

            X_rsa.print_spectrum();
            
            X_rsa.vars.spectrum.settings_type.rbw = 60e3;
            X_rsa.vars.spectrum.settings_type.span = 1e6;
            X_rsa.vars.spectrum.settings_type.enableVBW = true;
            X_rsa.vars.spectrum.settings_type.traceLength = 6969;
            X_rsa.vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_Mil6dB;
            X_rsa.vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_Amp;
            
            X_rsa.vars.spectrum.is_enabled_measurement = true;
            for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
            {
                X_rsa.vars.spectrum.is_enabled_trace[ii] = true;
                X_rsa.vars.spectrum.detectors_select[ii] = RSA_API::SpectrumDetector_AverageVRMS;
            }
            X_rsa.spectrum_set_vars();
            X_rsa.print_spectrum();

        #if defined (UT8_b) || (UT8_c) || (UT8_d)
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT8_b

            // the spectrum group is automatically preset
            X_rsa.config_preset();
            X_rsa.vars.config.center_frequency_hz = 100e6;
            X_rsa.vars.config.reference_level_dbm = -10.345;
            X_rsa.config_set_vars();
            X_rsa.print_config();

            X_rsa.vars.spectrum.settings_type.rbw = 10e3;
            X_rsa.vars.spectrum.settings_type.span = 1e6;
            X_rsa.vars.spectrum.settings_type.traceLength = 919;
            X_rsa.spectrum_set_vars();
            
            X_rsa.spectrum_aquire();
            X_rsa.spectrum_find_peak_index();
            printf("\npoints aquired:  %d  ,  peak index:  %d  ,  freq[%d]:  %lf  ,  pow[%d]:  %0.12f\n",
                X_rsa.vars.spectrum.trace_points_acquired[0],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.array_frequency[X_rsa.vars.spectrum.peak_index[0]],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.array_power[0][X_rsa.vars.spectrum.peak_index[0]]);
            X_rsa.print_spectrum();

        #if defined (UT8_c) || (UT8_d)
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT8_c

            X_rsa.vars.config.center_frequency_hz = 100e6;
            X_rsa.vars.config.reference_level_dbm = -31.345;
            X_rsa.config_set_vars();
            X_rsa.print_config();

            X_rsa.vars.spectrum.settings_type.rbw = 10e3;
            X_rsa.vars.spectrum.settings_type.span = 100e6;
            X_rsa.vars.spectrum.settings_type.traceLength = 919;
            X_rsa.spectrum_set_vars();
            
            X_rsa.spectrum_aquire();
            X_rsa.spectrum_find_peak_index();
            X_rsa.print_spectrum();
            printf("\npoints aquired:  %d  ,  peak index:  %d  ,  freq[%d]:  %lf  ,  pow[%d]:  %f\n",
                X_rsa.vars.spectrum.trace_points_acquired[0],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.array_frequency[X_rsa.vars.spectrum.peak_index[0]],
                X_rsa.vars.spectrum.peak_index[0],
                X_rsa.vars.spectrum.array_power[0][X_rsa.vars.spectrum.peak_index[0]]);
            X_rsa.spectrum_write_csv();
            printf("\nsee the CSV that got made:  %s...\n", X_rsa.constants.DATA_DIRECTORY_PROCESSED);
        #if UT8_d
            #ifdef WAIT_ENTER_CLEAR
                wait_enter_clear();
            #endif
        #endif
        #endif
        #ifdef UT8_d

            int steps = 10;
            double step_size = 5e5;
            X_rsa.vars.config.center_frequency_hz = 50e6;
            X_rsa.vars.config.reference_level_dbm = -25.9;
            X_rsa.config_set_vars();

            X_rsa.vars.spectrum.settings_type.rbw = 1e3;
            X_rsa.vars.spectrum.settings_type.span = 5e6;
            X_rsa.vars.spectrum.settings_type.traceLength = 919;
            X_rsa.spectrum_set_vars();

            for (int ii = 0; ii < steps; ii++)
            {
                X_rsa.vars.config.center_frequency_hz = 50e6 + ii * step_size;
                X_rsa.config_set_vars();

                X_rsa.spectrum_aquire();
                X_rsa.spectrum_find_peak_index();
                printf("\ncenter freq:  %14.3lf  ,  freq[%4d]:  %14.3lf  ,  pow[%4d]:  %14.3f\n",
                    X_rsa.vars.config.center_frequency_hz,
                    X_rsa.vars.spectrum.peak_index[0],
                    X_rsa.vars.spectrum.array_frequency[X_rsa.vars.spectrum.peak_index[0]],
                    X_rsa.vars.spectrum.peak_index[0],
                    X_rsa.vars.spectrum.array_power[0][X_rsa.vars.spectrum.peak_index[0]]);
                X_rsa.spectrum_write_csv();
            }

        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_8.cpp
