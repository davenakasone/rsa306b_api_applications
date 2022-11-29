/*
    unit test # 12, class [rsa_306b] API group 'IFSTREAM'

    goals:
    
        CODEZ ifstream_print                                     (); 
        CODEZ ifstream_set_vars                                  ();   
        CODEZ ifstream_record_r3f                                ();    
        CODEZ ifstream_acquire_data                              ();    
        CODEZ ifstream_acquire_framed_data                       ();   
        bool  ifstream_good_bitcheck                             ();       
        CODEZ ifstream_write_csv_data        (char* file_path_name);    
        CODEZ ifstream_write_csv_framed_data (char* file_path_name);    
        CODEZ ifstream_write_csv_equalization(char* file_path_name);
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut12 = 5;
static void ut12_basic();
static void ut12_r3f();
static void ut12_acq();
static void ut12_acqf();


void unit_test_12()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'IFSTREAM'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    X_util.clear_data();
    X_rsa.device_connect();

    ut12_basic();
    ut12_r3f();
    ut12_acq();
    ut12_acqf();

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


static void ut12_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic IFSTREAM methods\n", __func__);
#endif                   
//~

    X_rsa.vars.config.reference_level_dbm = -17.7;
    X_rsa.vars.config.center_frequency_hz = 315.002e6;
    X_rsa.config_set_vars();

    (void)X_rsa.ifstream_print();

    X_rsa.vars.ifstream.file_name_suffix = static_cast<int>(RSA_API::IFSSDFN_SUFFIX_TIMESTAMP);
    (void)strcpy(X_rsa.vars.ifstream.file_path, DATA_DIRECTORY_RAW);
    (void)strcpy(X_rsa.vars.ifstream.file_name_base, IFSTREAM_FILE_NAME_BASE);
    X_rsa.vars.ifstream.file_length_max_ms = 11;
    X_rsa.vars.ifstream.file_count = 1;
    X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_FILE_R3F;
    X_rsa.vars.ifstream.is_enabled = false;
    (void)X_rsa.ifstream_set_vars();
    (void)X_rsa.ifstream_print();

    (void)sprintf(X_rsa.cutil.helper, "%s%s_equalization.csv",
        DATA_DIRECTORY_PROCESSED,
        __func__);
    (void)X_rsa.ifstream_write_csv_equalization(X_rsa.cutil.helper);
    printf("\nsee equalization parameters:\n\t%s\n", X_rsa.cutil.helper);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut12_r3f()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  IFSTREAM produce '*.r3f' files\n", __func__);
#endif                   
//~
    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut12; ii++)
    {
        (void)X_rsa.ifstream_record_r3f();
    }
    X_rsa.device_stop();
    
    (void)X_r3f.batch_process_files
    (
        DATA_DIRECTORY_RAW, 
        DATA_DIRECTORY_PROCESSED, 
        X_util.filez_in, 
        X_util.filez_out, 
        true, 
        true, 
        true
    );

    printf("\noriginal files:\n");
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("\t%s\n", X_util.filez_in[ii].c_str());
    }
    printf("\nprocessed the files:\n");
    for (std::size_t ii = 0; ii < X_util.filez_out.size(); ii++)
    {
        printf("\t%s\n", X_util.filez_out[ii].c_str());
    }
    X_rsa.device_stop();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut12_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  IFSTREAM acquire direclty, then make CSV (entire block)\n", __func__);
#endif                   
//~

    X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_CLIENT;
    (void)X_rsa.ifstream_set_vars();
    X_rsa.device_run();

    for (int ii = 0; ii < bangz_ut12; ii++)
    {
        if (X_rsa.ifstream_acquire_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s__%dof%d_.csv",
                DATA_DIRECTORY_PROCESSED,
                __func__,
                ii+1,
                bangz_ut12);
            if (X_rsa.ifstream_write_csv_data(X_rsa.cutil.helper) == CODEZ::_0_no_errors)
            {
                printf("%2d of %2d)  %s\n", ii+1, bangz_ut12, X_rsa.cutil.helper);
            }
        }
    }
    X_rsa.device_stop();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut12_acqf()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  IFSTREAM acquire direclty, then make CSV (framed)\n", __func__);
#endif                   
//~

    X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_CLIENT;
    (void)X_rsa.ifstream_set_vars();
    X_rsa.device_run();

    for (int ii = 0; ii < bangz_ut12; ii++)
    {
        if (X_rsa.ifstream_acquire_framed_data() == CODEZ::_0_no_errors)
        {
            (void)sprintf(X_rsa.cutil.helper, "%s%s__%dof%d_.csv",
                DATA_DIRECTORY_PROCESSED,
                __func__,
                ii+1,
                bangz_ut12);
            if (X_rsa.ifstream_write_csv_framed_data(X_rsa.cutil.helper) == CODEZ::_0_no_errors)
            {
                printf("%2d of %2d)  %s\n", ii+1, bangz_ut12, X_rsa.cutil.helper);
            }
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


////////~~~~~~~~END>  unit_test_12.cpp
