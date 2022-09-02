/*
    unit test # 5, "CONFIG" section

    goals:
        - other sections continue to work
        - getters, setters, and blockers work
        - basic configurations can be made
        - basic configuration changes are possible
*/

#include "unit_tests.h"

struct ut5
{
    double cf;
    double cf_max;
    double cf_min;
    double rl;
    double f_ext;
    RSA_API::FREQREF_SOURCE source;

}; typedef struct ut5 ut5;

void ut5_get_print(ut5* stc, rsa306b* cls);


void unit_test_5 (void)
{
    printf("\n%s()  ,  testing the 'CONFIG' section of the class\n", __func__);
    {
        ut5 test;       // holds test variables
        rsa306b rsa;    // constructor is called

        // test getters and setters, and blockers
        ut5_get_print(&test, &rsa);    
        rsa.config_print_all();
        rsa.device_connect();
        ut5_get_print(&test, &rsa);    
        rsa.config_print_all();

        // make an alignment
        test.cf = 100e6;
        test.rl = -44;
        rsa.config_update_cf_rl(test.cf, test.rl);
        test.cf = rsa.config_get_center_frequency_hz();
        test.rl = rsa.config_get_reference_level_dbm();
        printf("\nset center frequency:  %lf Hz\n", test.cf);
        printf("set reference level :  %lf dbm\n", test.rl);
        rsa.config_print_all();
        test.cf = 100e9;
        test.rl = -44;
        rsa.config_update_cf_rl(test.cf, test.rl);
        test.cf = 1e9;
        test.rl = 444;
        rsa.config_update_cf_rl(test.cf, test.rl);
        rsa.device_disconnect();

        // use internal reference (try external at the lab)
        rsa.device_connect();
        test.source = RSA_API::FRS_INTERNAL;
        rsa.config_use_external_reference_source(test.source);
        rsa.config_print_all();
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


void ut5_get_print
(
    ut5* stc, 
    rsa306b* cls
)
{
    stc->cf = cls->config_get_center_frequency_hz();
    stc->cf_min = cls->config_get_center_frequency_min_hz();
    stc->cf_max = cls->config_get_center_frequency_max_hz();
    stc->rl = cls->config_get_reference_level_dbm();
    stc->f_ext = cls->config_get_external_frequency_reference_hz();
    stc->source = cls->config_get_frequency_reference_source();
    printf("\nget CONFIG information >>>\n");
    printf("\texternal frequency          :  %lf  Hz\n", stc->f_ext);
    printf("\tmin center frequency        :  %lf  Hz\n", stc->cf_min);
    printf("\tcenter frequency            :  %lf  Hz\n", stc->cf);
    printf("\tmax center frequency        :  %lf  Hz\n", stc->cf_max);
    printf("\treference level             :  %lf  dBm\n", stc->rl);
    printf("\tfrequency reference source  :  ");
    switch (stc->source)
    {
        case (RSA_API::FRS_INTERNAL) :
            printf("internal\n");
            break;
        case (RSA_API::FRS_EXTREF) :
            printf("external\n");
            break;
        case (RSA_API::FRS_GNSS) :
            printf("GNSS\n");
            break;
        case (RSA_API::FRS_USER) :
            printf("user-provided\n");
        default :
            printf("unknown\n");
    }
}


////////~~~~~~~~END>  unit_test_5.cpp
