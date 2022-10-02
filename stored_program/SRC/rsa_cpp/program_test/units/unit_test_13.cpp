/*
    unit test # 13, class [r3f_manager]

    goals:
    
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut13 = 3;
static void ut13_r3f();
static void ut13_decodew();
static void ut13_decodep();
static void ut13_batch();


void unit_test_13()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [r3f_manager]'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    ut13_r3f();
    ut13_decodew();
    ut13_decodep();
    ut13_batch();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut13_r3f()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  make some r3f files\n", __func__);
#endif                   
//~

    X_rsa.device_connect();

    X_rsa.vars.config.reference_level_dbm = -17.7;
    X_rsa.vars.config.center_frequency_hz = 315.002e6;
    X_rsa.config_set_vars();

    X_rsa.vars.ifstream.file_name_suffix = static_cast<int>(RSA_API::IFSSDFN_SUFFIX_TIMESTAMP);
    (void)strcpy(X_rsa.vars.ifstream.file_path, DATA_DIRECTORY_RAW);
    (void)strcpy(X_rsa.vars.ifstream.file_name_base, IFSTREAM_FILE_NAME_BASE);
    X_rsa.vars.ifstream.file_length_max_ms = 1;
    X_rsa.vars.ifstream.file_count = 1;
    X_rsa.vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_FILE_R3F;
    X_rsa.vars.ifstream.is_enabled = false;
    (void)X_rsa.ifstream_set_vars();

    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut13; ii++)
    {
        (void)X_rsa.ifstream_record_r3f();
    }
    X_rsa.device_stop();

    (void)X_util.h_batch_match_extension(X_rsa.vars.ifstream.file_path, "r3f", X_util.filez_in, true);
    printf("\nmade some R3F files:\n");
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("\t%s\n", X_util.filez_in[ii].c_str());
    }
    
    X_rsa.device_disconnect();
}


////~~~~


static void ut13_decodew()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  decoding r3f files, writing\n", __func__);
#endif                   
//~

    (void)X_r3f.batch_decode_write(DATA_DIRECTORY_RAW, DATA_DIRECTORY_PROCESSED, 0L, 0L, X_util.filez_in, X_util.filez_out);
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("\n%luof%lu)  %s\n", ii+1, X_util.filez_in.size(), X_util.filez_in[ii].c_str());
        printf("\t%s\n", X_util.filez_out[ii].c_str());
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}

////~~~~


static void ut13_decodep()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  decoding r3f files, printing\n", __func__);
#endif                   
//~

    (void)X_r3f.batch_decode_print(DATA_DIRECTORY_RAW, 0L, 0L, X_util.filez_in);
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("\n%luof%lu)  %s\n", ii+1, X_util.filez_in.size(), X_util.filez_in[ii].c_str());
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut13_batch()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  batch r3f files, parse + 2 plots\n", __func__);
#endif                   
//~
    int cnt = 0;
    (void)X_r3f.batch_load_file(DATA_DIRECTORY_RAW, DATA_DIRECTORY_PROCESSED, X_util.filez_in, X_util.filez_out);
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("\n%luof%lu)  %s\n", ii+1, X_util.filez_in.size(), X_util.filez_in[ii].c_str());
        printf("\t%s\n", X_util.filez_out[cnt].c_str());
        cnt++;
        printf("\t%s\n", X_util.filez_out[cnt].c_str());
        cnt++;
        printf("\t%s\n", X_util.filez_out[cnt].c_str());
        cnt++;
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_13.cpp
