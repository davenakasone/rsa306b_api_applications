/*
    unit test # 11, class [rsa_306b] API group 'IQSTREAM'

    goals:
    
        CODEZ iqstream_print                           ()
        CODEZ iqstream_set_vars                        ()
        CODEZ iqstream_acquire_data                    ()
        CODEZ iqstream_record_siq                      ()
        CODEZ iqstream_write_csv   (char* file_path_name)
        CODEZ iqstream_clear_sticky                    ()
        bool  iqstream_good_bitcheck                   ()
        CODEZ iqstream_start                           ()
        CODEZ iqstream_stop                            ()
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut11 = 5;
static void ut11_basic();
static void ut11_siq();
static void ut11_acq();


void unit_test_11()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'IQSTREAM'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();
    ut11_basic();
    ut11_siq();
    ut11_acq();
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


static void ut11_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic IQSTREAM methods\n", __func__);
#endif                   
//~

    X_rsa.iqstream_print();

    X_rsa.vars.config.center_frequency_hz = 315.0e6;
    X_rsa.vars.config.reference_level_dbm = -15.5;
    X_rsa.config_set_vars();

    X_rsa.vars.iqstream.bandwidth = 10.0e6;
    X_rsa.vars.iqstream.buffer_multiplier = iqsBuff::b2x;
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE;
    X_rsa.vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_FILE_SIQ;
    X_rsa.vars.iqstream.record_time_ms = 10;
    (void)sprintf(X_rsa.vars.iqstream.filename_base, "%s%s_ut11_", 
        DATA_DIRECTORY_RAW,
        IQSTREAM_FILE_NAME_BASE);
    X_rsa.vars.iqstream.suffix_control = static_cast<int>(RSA_API::IQSSDFN_SUFFIX_TIMESTAMP);
    X_rsa.iqstream_set_vars();

    X_rsa.iqstream_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut11_siq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  IQSTREAM produce '*.siq' files\n", __func__);
#endif                   
//~

    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut11; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_record_siq() == CODEZ::_0_no_errors)
        {
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut11,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.fileinfo_type.acqStatus);
            printf("\t%s\n", X_rsa.vars.iqstream.filenames_0_data);
        }
    }
    X_rsa.device_stop();
    X_rsa.iqstream_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut11_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  IQSTREAM acquire direclty, then make CSV\n", __func__);
#endif                   
//~

    X_rsa.device_stop();
    X_rsa.vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_CLIENT;
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE;
    X_rsa.iqstream_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut11; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_single__%2d_of_%2d_.csv",
                DATA_DIRECTORY_PROCESSED,
                IQSTREAM_FILE_NAME_BASE,
                ii+1,
                bangz_ut11);
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut11,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.info_type.acqStatus);
            (void)X_rsa.iqstream_write_csv(X_rsa.cutil.helper);
            printf("\t%s\n", X_rsa.cutil.helper);
        }
    }
    X_rsa.device_stop();
    (void)X_rsa.iqstream_clear_sticky();
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE_SCALE_INT32;
    X_rsa.iqstream_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut11; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_scaled__%2d_of_%2d_.csv",
                DATA_DIRECTORY_PROCESSED,
                IQSTREAM_FILE_NAME_BASE,
                ii+1,
                bangz_ut11);
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut11,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.info_type.acqStatus);
            (void)X_rsa.iqstream_write_csv(X_rsa.cutil.helper);
            printf("\t%s\n", X_rsa.cutil.helper);
        }
    }
    X_rsa.device_stop();
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_INT16;
    X_rsa.iqstream_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut11; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_int16__%2d_of_%2d_.csv",
                DATA_DIRECTORY_PROCESSED,
                IQSTREAM_FILE_NAME_BASE,
                ii+1,
                bangz_ut11);
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut11,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.info_type.acqStatus);
            (void)X_rsa.iqstream_write_csv(X_rsa.cutil.helper);
            printf("\t%s\n", X_rsa.cutil.helper);
        }
    }
    X_rsa.device_stop();
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_INT32;
    X_rsa.iqstream_set_vars();
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut11; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s_int32__%2d_of_%2d_.csv",
                DATA_DIRECTORY_PROCESSED,
                IQSTREAM_FILE_NAME_BASE,
                ii+1,
                bangz_ut11);
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut11,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.info_type.acqStatus);
            (void)X_rsa.iqstream_write_csv(X_rsa.cutil.helper);
            printf("\t%s\n", X_rsa.cutil.helper);
        }
    }
    X_rsa.device_stop();
   
//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_11.cpp
