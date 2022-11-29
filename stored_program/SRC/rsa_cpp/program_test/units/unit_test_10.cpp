/*
    unit test # 10, class [rsa_306b] API group 'IQBLK'

    goals:
    
        CODEZ iqblk_print                           ()
        CODEZ iqblk_set_vars                        ()
        CODEZ iqblk_acquire_data                    ()
        bool  iqblk_good_bitcheck                   () 
        CODEZ iqblk_make_csv    (char* file_path_name)
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut10 = 5;
static void ut10_basic();
static void ut10_acq();

void unit_test_10()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'IQBLK'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    X_util.clear_data();
    X_rsa.device_connect();

    ut10_basic();
    ut10_acq();

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


static void ut10_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic IQBLK methods\n", __func__);
#endif                   
//~

    X_rsa.iqblk_print();
    X_rsa.vars.config.center_frequency_hz = 315.02e6;
    X_rsa.vars.config.reference_level_dbm = -12.3;
    X_rsa.config_set_vars();

    X_rsa.vars.iqblk.record_length = 2222;
    X_rsa.vars.iqblk.getting_select = iqblkGetData::deinterleaved;
    X_rsa.vars.iqblk.bandwidth_hz = 20e6;
    X_rsa.iqblk_set_vars();
    X_rsa.iqblk_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut10_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic IQBLK acquire and write csv\n", __func__);
#endif                   
//~

    X_rsa.device_stop();
    X_rsa.device_prepare_for_run();
    X_rsa.vars.iqblk.getting_select = iqblkGetData::complex;
    X_rsa.iqblk_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut10; ii++)
    {
        if (X_rsa.iqblk_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_complex__%d_of_%d_.csv",
                DATA_DIRECTORY_PROCESSED,
                __func__,
                ii+1,
                bangz_ut10);
            X_rsa.iqblk_write_csv(X_rsa.cutil.helper);
            printf("%s\n", X_rsa.cutil.helper);
        }
    }
    printf("\n");
    X_rsa.device_stop();
    X_rsa.device_prepare_for_run();
    X_rsa.vars.iqblk.getting_select = iqblkGetData::interleaved;
    X_rsa.iqblk_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut10; ii++)
    {
        if (X_rsa.iqblk_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_interleaved__%d_of_%d_.csv",
                DATA_DIRECTORY_PROCESSED,
                __func__,
                ii+1,
                bangz_ut10);
            X_rsa.iqblk_write_csv(X_rsa.cutil.helper);
            printf("%s\n", X_rsa.cutil.helper);
        }
    }
    printf("\n");
    X_rsa.device_stop();
    X_rsa.device_prepare_for_run();
    X_rsa.vars.iqblk.getting_select = iqblkGetData::deinterleaved;
    X_rsa.iqblk_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut10; ii++)
    {
        if (X_rsa.iqblk_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_deinterleaved__%d_of_%d_.csv",
                DATA_DIRECTORY_PROCESSED,
                __func__,
                ii+1,
                bangz_ut10);
            X_rsa.iqblk_write_csv(X_rsa.cutil.helper);
            printf("%s\n", X_rsa.cutil.helper);
        }
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_10.cpp
