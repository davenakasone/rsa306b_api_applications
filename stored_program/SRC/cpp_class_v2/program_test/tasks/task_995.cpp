/*
    chek the YK-3000 transmitter @ 315 MHz
    the antenna might only be good for around 150 MHz
*/

#include "../testz.h"
extern rsa306b_class X_rsa;


void task_995()
{
    printf("\n%s()  ,  see if the antenna catches 315 MHz\n", __func__);
    {
        X_rsa.device_disconnect();
        X_rsa.device_connect();

        X_rsa.vars.config.center_frequency_hz = 315e6;
        X_rsa.vars.config.reference_level_dbm = 3;
        X_rsa.config_set_vars();
        X_rsa.print_config();

        X_rsa.vars.spectrum.settings_type.rbw = 1e3;
        X_rsa.vars.spectrum.settings_type.span = 1e6;
        X_rsa.vars.spectrum.settings_type.traceLength = 919;
        X_rsa.spectrum_set_vars();
        X_rsa.print_spectrum();

        printf("\n");
        for (int ii = 0; ii < 100; ii++)
        {
            X_rsa.spectrum_aquire();
            X_rsa.spectrum_find_peak_index();
            printf("%3d)  max@  %7.2lf MHz  ,  %7.2f dBm\n", 
                ii + 1,
                X_rsa.vars.spectrum.array_frequency[X_rsa.vars.spectrum.peak_index[0]]/1e6,
                X_rsa.vars.spectrum.array_power[0][X_rsa.vars.spectrum.peak_index[0]]);
            X_rsa.spectrum_write_csv();
        }
    }
    printf("\n%s()  ,  task complete, adjust as needed\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


/////////~~~~~~~~END>  task_995.cpp
