/*
    demonstration for DSP people
*/

#include "../testz.h"


void task_997()
{
    printf("\n%s()  ,  DSP applications\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        r3f_manager_class r3f;
        rsa.device_connect();
    /*
    // < 1 >  display data aquisition components
        printf("\n\tprimary variables and constants in use:\n");
        rsa.print_everything();

    wait_enter_clear();
    // < 2 >  RSA catches FM band, even with limited antenna { show picture }
        int steps = 200;
        double step_size = 5e5;
        rsa.vars.config.center_frequency_hz = 50e6;
        rsa.vars.config.reference_level_dbm = -25.9;
        rsa.config_set_vars();

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
        }
            
    wait_enter_clear();
    */
    // < 3 >  IFSTREAM, decode, and parse
        rsa.vars.config.reference_level_dbm = -25;
        rsa.vars.config.center_frequency_hz = 100e6;
        rsa.config_set_vars();

        rsa.vars.ifstream.file_count = 1;
        rsa.vars.ifstream.file_length_ms = 30;
        strcpy(rsa.vars.ifstream.file_name_base, "ee482");
        rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_NONE;
        strcpy(rsa.vars.ifstream.file_path, "./program_test/data/outputs_r3f/");
        rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
        rsa.ifstream_set_vars();

        rsa.ifstream_record_file();
        rsa.print_ifstream();
        snprintf(rsa.vars.gp.helper, BUF_E-1, "%s%s.r3f", rsa.vars.ifstream.file_path, rsa.vars.ifstream.file_name_base);

        snprintf(rsa.vars.gp.holder, BUF_F-1, "./program_test/data/outputs_txt/decode.txt");
        r3f.file_decode(rsa.vars.gp.helper, rsa.vars.gp.holder, 0, 5000, false);

        r3f.prepare_plot_from_adc(rsa.vars.ifstream.file_path, "./program_test/data/outputs_txt/");

        snprintf(rsa.vars.gp.holder, BUF_F-1, "./program_test/data/outputs_txt/processed.txt");
        r3f.file_process(rsa.vars.gp.helper, rsa.vars.gp.holder, false);

        snprintf(rsa.vars.gp.holder, BUF_F-1, "./program_test/data/outputs_txt/iq.txt");
        r3f.prepare_plot_from_iq(rsa.vars.gp.helper, rsa.vars.gp.holder);
        
        snprintf(rsa.vars.gp.holder, BUF_F-1, "./program_test/data/outputs_txt/header.txt");
        r3f.prepare_plot_from_header(rsa.vars.gp.holder);
    }
    printf("\n%s()  ,  demonstration complete\n", __func__);
}


/////////~~~~~~~~END>  task_997.cpp
