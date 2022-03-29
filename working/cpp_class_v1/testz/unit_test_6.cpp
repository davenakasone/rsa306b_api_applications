/*
    unit test # 6, "SPECTRUM" section

    goals:
        - other sections continue to work
        - getters, setters, and blockers work
        - spectrum can be configured
        - data aquisition
        - change cf ...see a seperate test
*/

#include "unit_tests.h"


void unit_test_6 (void)
{
    printf("\n%s()  ,  testing the 'SPECTRUM' section of the class\n", __func__);
    {
        bool measureEnabled = false;
        RSA_API::Spectrum_Limits lims;
        rsa306b rsa;    // constructor is called

        rsa.device_connect();
        rsa.spectrum_get_limits_type(&lims);
        printf("\n\tgot maxRBW:  %lf  , checking rest with print\n", lims.maxRBW);
        rsa.spectrum_print_all();

        measureEnabled = rsa.spectrum_get_measurement_enabled();
        printf("\nmeasurement enabled:  %d\n", measureEnabled);
        
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


////////~~~~~~~~END>  unit_test_6.cpp
