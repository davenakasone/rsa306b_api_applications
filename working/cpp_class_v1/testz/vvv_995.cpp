/*
    real time "SPECTRUM" to find the antenna capabilities
    same as "vvv_996" , but try to change the trigger
*/

#include "unit_tests.h"


void vvv_995()
{
    printf("\n%s()  , checking antenna\n", __func__);
    rsa306b rsa;           
    rsa.device_connect(); 

    float maxPower = -999999.9;
    float powerTrail = -9e9;
    double maxCf= -99999.9;

    const double STEP = 1e6;
    const int REPZ = 100;
    const int STEPZ = 60;

    rsa306b::trig_type trig_t;
    rsa.trig_get_settings(&trig_t);
    rsa.trig_print_all();
    trig_t.position_percent = 10;
    trig_t.if_power_level = -30;
    trig_t.source_select = RSA_API::TriggerSourceIFPowerLevel;
    trig_t.transition_select = RSA_API::TriggerTransitionEither;
    //trig_t.mode_select = RSA_API::triggered;
    rsa.trig_prepare(&trig_t);
    rsa.trig_print_all();

    rsa306b::spectrum_data_collector data;
    RSA_API::Spectrum_Settings t_set;
    rsa306b::spectrum_3_traces_type t_3;
    double cf = 50e6;
    double rl;
    double span = 5e6;
    int pk = -12;

    rl = -50;
    rsa.spectrum_get_3_traces_type(&t_3);
    rsa.spectrum_get_settings_type(&t_set);
    //t_set.span = span;

    for (int ii = 0; ii < STEPZ; ii++)
    {
        cf = cf + ii * STEP;
        rl++;
        rsa.spectrum_prepare(cf, rl, &t_set, &t_3);
        printf("checking  ,  cf =  %19.1lf  ,  rl=  %12.1lf ...", cf, rl);
        for (int jj = 0; jj < REPZ; jj++)
        {
            rsa.spectrum_acquire_trace(RSA_API::SpectrumTrace1);
            pk = rsa.spectrum_index_of_peak_measurement(RSA_API::SpectrumTrace1); // indexed at 0
            rsa.spectrum_collect_data(&data, pk);
            powerTrail = data.y_measurement[0];
        }
        if (powerTrail > maxPower)
        {
            maxPower = powerTrail;
            maxCf = cf;
        }
        printf("  found max power =  %19.8f\n", maxPower);
    }

    rsa.spectrum_print_all(); 
    printf("\n\nthe largest dBm:  %f    @    cf:  %lf MHz\n", maxPower, maxCf/1e6);
    printf("\n%s()  ,  test complete\n", __func__); 
}


/////////~~~~~~~~END>  vvv_995.cpp
