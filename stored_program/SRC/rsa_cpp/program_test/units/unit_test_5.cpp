/*
    unit test # 5, class [rsa_306b] API group 'CONFIG'

    goals:
    
        CODEZ config_print   ();
        CODEZ config_preset  ();
        CODEZ config_set_vars();
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut4 = 5;
static void ut5_basic();
static void ut5_preset();


void unit_test_5()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'CONFIG'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);
    X_rsa.device_connect();

    ut5_basic();
    ut5_preset();
    
    X_rsa.device_disconnect();
//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut5_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic CONFIG methods\n", __func__);
#endif                   
//~

    X_rsa.config_print();
    X_rsa.vars.config.center_frequency_hz = 315.5e6;
    X_rsa.vars.config.frequency_reference_source_select = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;
    X_rsa.vars.config.reference_level_dbm = -33.3;
    printf("\nchanges made...\n");
    X_rsa.config_set_vars();
    X_rsa.config_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut5_preset()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  running the alignment\n", __func__);
#endif                   
//~

    printf("\nchanges made...\n");
    X_rsa.vars.config.center_frequency_hz = 2445.5e6;
    X_rsa.vars.config.frequency_reference_source_select = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;
    X_rsa.vars.config.reference_level_dbm = -77.7;
    X_rsa.config_set_vars();
    X_rsa.config_print();

    printf("\npreset applied...\n");
    X_rsa.config_preset();
    X_rsa.config_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_5.cpp
