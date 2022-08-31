/*
    chek the YK-3000 transmitter @ 315 MHz
    the antenna might only be good for around 150 MHz
*/

#include "../testz.h"


void task_995()
{
    printf("\n%s()  ,  see if the antenna catches 315 MHz\n", __func__);
    {
        rsa306b_class rsa;
        rsa.device_connect();

        rsa.vars.config.center_frequency_hz = 315e6;
        rsa.vars.config.reference_level_dbm = 3;
        rsa.config_set_vars();
        rsa.print_config();

        rsa.vars.spectrum.settings_type.rbw = 1e3;
        rsa.vars.spectrum.settings_type.span = 1e6;
        rsa.vars.spectrum.settings_type.traceLength = 919;
        rsa.spectrum_set_vars();
        rsa.print_spectrum();

        printf("\n");
        for (int ii = 0; ii < 10; ii++)
        {
            rsa.spectrum_aquire();
            rsa.spectrum_find_peak_index();
            printf("%3d)  max@  %7.2lf MHz  ,  %7.2f dBm\n", 
                ii + 1,
                rsa.vars.spectrum.array_frequency[rsa.vars.spectrum.peak_index[0]]/1e6,
                rsa.vars.spectrum.array_power[0][rsa.vars.spectrum.peak_index[0]]);
        }
    }
    printf("\n%s()  ,  task complete, adjust as needed\n", __func__);
}


/////////~~~~~~~~END>  task_995.cpp
