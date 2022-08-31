/*
    unit test # 6, "SPECTRUM" section

    goals:
        - other sections continue to work
        - getters, setters, and blockers work
        - spectrum can be configured
        - data aquisition
        - change cf ...see a seperate test
    
    use the public "traces_3_type" struct to get all 3 traces
    this APi group will need 99x tests for furter validation
*/

#include "unit_tests.h"

#define UT6_REPZ 700    // repititions 

//#define UT6_SEC_1 1    // try the getters
//#define UT6_SEC_2 2    // try to configure the spectrum
#define UT6_SEC_3 3    // get some spectrum readings, find peaks


void unit_test_6 (void)
{
    printf("\n%s()  ,  testing the 'SPECTRUM' section of the class\n", __func__);
    {
        rsa306b rsa;    // constructor is called
        rsa.device_connect();

        #ifdef UT6_SEC_1
            bool measureEnabled = false; 
            RSA_API::Spectrum_Limits lims;
            RSA_API::Spectrum_Settings sets; 
            RSA_API::Spectrum_TraceInfo tInfo;
            rsa306b::spectrum_3_traces_type my3;

            measureEnabled = rsa.spectrum_get_measurement_enabled();
            rsa.spectrum_get_limits_type(&lims);
            rsa.spectrum_get_settings_type(&sets);
            rsa.spectrum_get_trace_info_type(&tInfo);
            rsa.spectrum_get_3_traces_type(&my3);
            
            printf("got measurement enabled    :  %d\n", measureEnabled);
            printf("got maxRBW                 :  %lf\n", lims.maxRBW);
            printf("got rbw                    :  %lf\n", sets.rbw);
            printf("got a time stamp           :  %ld\n", tInfo.timestamp);
            printf("got 3rd trace detector type:  %d\n", my3.detector_select[2]);

            printf("checking the rest with 'spectrum_print_all'...\n");
            rsa.spectrum_print_all();
        #endif
        #ifdef UT6_SEC_2
            RSA_API::Spectrum_Settings mySettings;
            rsa306b::spectrum_3_traces_type my3t;
            double myCf = 500e5;
            double myRl = -17;
            double myRbw = -99;
            double mySpan = 12e6;

            rsa.spectrum_get_3_traces_type(&my3t);
            rsa.spectrum_get_settings_type(&mySettings);
            mySettings.rbw = myRbw;
            mySettings.span = mySpan;
            my3t.trace_enabled[2] = true;
            rsa.spectrum_prepare(myCf, myRl, &mySettings, &my3t); // rejected

            myRbw = 90;
            mySpan = 4e3;
            mySettings.rbw = myRbw;
            mySettings.span = mySpan;
            rsa.spectrum_prepare(myCf, myRl, &mySettings, &my3t); // passed
        #endif
        #ifdef UT6_SEC_3
            rsa306b::spectrum_data_collector data;
            RSA_API::Spectrum_Settings t_set;
            rsa306b::spectrum_3_traces_type t_3;
            double cf;
            double rl;
            int pk = -12;

            cf = rsa.config_get_center_frequency_hz();
            rl = rsa.config_get_reference_level_dbm();
            rsa.spectrum_get_3_traces_type(&t_3);
            rsa.spectrum_get_settings_type(&t_set);
            rsa.spectrum_prepare(cf, rl, &t_set, &t_3);
            for (int ii = 0; ii < UT6_REPZ; ii++)
            {
                rsa.spectrum_acquire_trace(RSA_API::SpectrumTrace1);
                pk = rsa.spectrum_index_of_peak_measurement(RSA_API::SpectrumTrace1); // indexed at 0
                rsa.spectrum_collect_data(&data, pk);
                printf("%4d)  max index:  %4d  ,  frequency:  %24.9lf  ,  measurement:  %24.9f\n",
                    ii, pk,
                    data.x_frequency,
                    data.y_measurement[0]);
            }
            rsa.spectrum_print_all();
        #endif
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


////////~~~~~~~~END>  unit_test_6.cpp
