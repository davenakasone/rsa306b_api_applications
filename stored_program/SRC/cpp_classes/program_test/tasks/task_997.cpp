/*
    demonstration for DSP people
    < 1 >  display variables in use
    < 2 >  scan a spectrum range
    < 3 >  read the ADC (IF), process and store the results
*/

#include "../testz.h"
// extern rsa306b_class X_rsa;
// extern r3f_manager_class X_r3f;
// extern timer_class X_timer;


void task_997()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  DSP applications\n", __func__);
X_timer.time_split_start();                      
#endif    
////~~~~

    X_rsa.device_disconnect();
    X_rsa.device_connect();
    
    // < 1 >  display data aquisition components
    printf("\n\tprimary variables and constants in use:\n");
    X_rsa.print_everything();

    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
    
    // < 2 >  RSA catches FM band, even with limited antenna { show picture }
    int steps                             = 20;
    double step_size                      = 5e5;
    X_rsa.vars.config.center_frequency_hz = 50e6;
    X_rsa.vars.config.reference_level_dbm = -25.9;
    X_rsa.config_set_vars();

    X_rsa.vars.spectrum.settings_type.rbw         = 1e3;
    X_rsa.vars.spectrum.settings_type.span        = 5e6;
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
    }
            
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
    
    // < 3 >  IFSTREAM, decode, and parse
    X_rsa.vars.config.reference_level_dbm = -25;
    X_rsa.vars.config.center_frequency_hz = 100e6;
    X_rsa.config_set_vars();

    X_rsa.vars.ifstream.file_count                  = 1;
    X_rsa.vars.ifstream.file_length_ms              = 30;
    X_rsa.vars.ifstream.file_name_suffix            = RSA_API::IFSSDFN_SUFFIX_NONE;
    X_rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    strcpy(X_rsa.vars.ifstream.file_path, X_rsa.constants.DATA_DIRECTORY_RAW);
    strcpy(X_rsa.vars.ifstream.file_name_base, "task997_");
    X_rsa.ifstream_set_vars();
    X_rsa.ifstream_record_file();
    X_rsa.print_ifstream();

    snprintf(X_rsa.vars.gp.helper, BUF_E-1, "%s%s.r3f", 
        X_rsa.vars.ifstream.file_path, 
        X_rsa.vars.ifstream.file_name_base);
    snprintf(X_rsa.vars.gp.holder, BUF_F-1, "%s%s_decoded.txt", 
        X_rsa.constants.DATA_DIRECTORY_PROCESSED,
        X_rsa.vars.ifstream.file_name_base);
    X_r3f.file_decode(X_rsa.vars.gp.helper, X_rsa.vars.gp.holder, 0, 5000, false);

    X_r3f.prepare_plot_from_adc(X_rsa.vars.ifstream.file_path, 
        X_rsa.constants.DATA_DIRECTORY_PROCESSED);

    snprintf(X_rsa.vars.gp.holder, BUF_F-1, "%s%s_processed.txt", 
        X_rsa.constants.DATA_DIRECTORY_PROCESSED,
        X_rsa.vars.ifstream.file_name_base);
    X_r3f.file_process(X_rsa.vars.gp.helper, X_rsa.vars.gp.holder, false);

    snprintf(X_rsa.vars.gp.holder, BUF_F-1, "%s%s_IQplot.txt", 
        X_rsa.constants.DATA_DIRECTORY_PROCESSED,
        X_rsa.vars.ifstream.file_name_base);
    X_r3f.prepare_plot_from_iq(X_rsa.vars.gp.helper, X_rsa.vars.gp.holder);
    
    snprintf(X_rsa.vars.gp.holder, BUF_F-1, "%s%s_header.txt", 
        X_rsa.constants.DATA_DIRECTORY_PROCESSED,
        X_rsa.vars.ifstream.file_name_base);
    X_r3f.prepare_plot_from_header(X_rsa.vars.gp.holder);

////~~~~
#ifdef WAIT_ENTER_CLEAR
X_timer.time_split_stop();
X_timer.print_both();
printf("\n%s()  ,  demonstration complete\n", __func__);
wait_enter_clear();
#endif
}


/////////~~~~~~~~END>  task_997.cpp
