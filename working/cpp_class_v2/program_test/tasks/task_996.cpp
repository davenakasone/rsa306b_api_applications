/*
    get some CSV
*/

#include "../testz.h"


void task_996()
{
    printf("\n%s()  ,  DSP applications\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        r3f_manager_class r3f;
        rsa.device_connect();
    
        FILE* fptr = fopen("./program_test/data/outputs_txt/train_data.csv", "w");
        rsa.vars.config.center_frequency_hz = 100e6;
        rsa.vars.config.reference_level_dbm = -25.9;
        rsa.config_set_vars();

        rsa.vars.spectrum.settings_type.rbw = 1e3;
        rsa.vars.spectrum.settings_type.span = 5e6;
        rsa.vars.spectrum.settings_type.traceLength = 919;
        rsa.spectrum_set_vars();

        for (int ii = 0; ii < 20; ii++)
        {
            rsa.spectrum_aquire();
            for (int jj = 0; jj < 919; jj++)
            {
                snprintf(rsa.vars.gp.helper, BUF_E-1, "%0.3lf,%0.3f\n",
                    rsa.vars.spectrum.array_frequency[jj],
                    rsa.vars.spectrum.array_power[0][jj]);
                fputs(rsa.vars.gp.helper, fptr);
            }
        }
        
        fclose(fptr); fptr = NULL;
        fptr = fopen("./program_test/data/outputs_txt/test_data.csv", "w");

        for (int ii = 0; ii < 5; ii++)
        {
            rsa.spectrum_aquire();
            for (int jj = 0; jj < 919; jj++)
            {
                snprintf(rsa.vars.gp.helper, BUF_E-1, "%0.3lf,%0.3f\n",
                    rsa.vars.spectrum.array_frequency[jj],
                    rsa.vars.spectrum.array_power[0][jj]);
                fputs(rsa.vars.gp.helper, fptr);
            }
        }

        fclose(fptr); fptr = NULL;
        fptr = fopen("./program_test/data/outputs_txt/valid_data.csv", "w");

        rsa.spectrum_aquire();
        for (int jj = 0; jj < 919; jj++)
        {
            snprintf(rsa.vars.gp.helper, BUF_E-1, "%0.3lf,%0.3f\n",
                rsa.vars.spectrum.array_frequency[jj],
                rsa.vars.spectrum.array_power[0][jj]);
            fputs(rsa.vars.gp.helper, fptr);
        }
        fclose(fptr); fptr = NULL;
    }
    printf("\n%s()  ,  files complete\n", __func__);
}


/////////~~~~~~~~END>  task_996.cpp
