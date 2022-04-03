/*
    real time "SPECTRUM" section adjustments, write to file

    the "SPECTRUM" function group is the most basic measurement group
    it is important to understand it because all the other groups use it

    also want to see where the antenna is capable

    this is a heavy test, usually actions should be minimized between analysis
*/

#include "unit_tests.h"


void vvv_997()
{
    printf("\n%s()  ,  moving the spectrum and writting to files\n", __func__);

    const char file_path[] = "./testz/test_outputs/";
    FILE* f_ptr = NULL;
    char help[BUF_E];

    const double STEP = 1e6;
    const int REPZ = 10;
    const int STEPZ = 6000;
    rsa306b::spectrum_data_collector data;
    RSA_API::Spectrum_Settings t_set;
    rsa306b::spectrum_3_traces_type t_3;
    double cf;
    double rl;
    double span = 1e6;
    int pk = -12;

    rsa306b rsa;           
    rsa.device_connect(); 

    cf = 100e6;
    rl = rsa.config_get_reference_level_dbm();
    rsa.spectrum_get_3_traces_type(&t_3);
    rsa.spectrum_get_settings_type(&t_set);
    t_set.span = span;

    for (int ii = 0; ii < STEPZ; ii++)
    {
        cf = cf + ii * STEP;
        rsa.spectrum_prepare(cf, rl, &t_set, &t_3);
        snprintf(help, BUF_E-1, "%scf_%0.1lf.txt", file_path, cf);
        f_ptr = fopen(help, "w");

        for (int jj = 0; jj < REPZ; jj++)
        {
            rsa.spectrum_acquire_trace(RSA_API::SpectrumTrace1);
            pk = rsa.spectrum_index_of_peak_measurement(RSA_API::SpectrumTrace1); // indexed at 0
            rsa.spectrum_collect_data(&data, pk);

            snprintf(help, BUF_E-1, "%4d)  max index:  %4d  ,  frequency:  %14.9lf  ,  measurement:  %14.9f\n",
                jj, pk,
                data.x_frequency,
                data.y_measurement[0]);
            fputs(help, f_ptr);
        }
        snprintf(help, BUF_E-1, "\n\n\t\t>>> SUCCESS\n\n");
        fputs(help, f_ptr);
        fclose(f_ptr);
        f_ptr = NULL;
    }
    rsa.spectrum_print_all(); 

    printf("\n%s()  ,  test complete\n", __func__); 
}


/////////~~~~~~~~END>  vvv_997.cpp
