/*
    unit test # 14, class [siq_manager]

    goals:
    
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut14 = 3;
static void ut14_siq();
static void ut14_decodew();
static void ut14_decodep();
static void ut14_batch();
static void vprint(std::vector<std::string>& anyv, const char* message);    // just a local helper


void unit_test_14()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [siq_manager]\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

   
    ut14_siq();
    ut14_decodew();
    ut14_decodep();
    ut14_batch();
   
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut14_siq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  get some *.siq files...\n", __func__);
#endif                   
//~
    X_util.filez_in.clear();
    X_rsa.device_connect();

    X_rsa.vars.config.center_frequency_hz = 315.0e6;
    X_rsa.vars.config.reference_level_dbm = -15.5;
    X_rsa.config_set_vars();

    X_rsa.vars.iqstream.bandwidth = 10.0e6;
    X_rsa.vars.iqstream.buffer_multiplier = iqsBuff::b2x;
    X_rsa.vars.iqstream.datatype_select = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE;
    X_rsa.vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_FILE_SIQ;
    X_rsa.vars.iqstream.record_time_ms = 1;
    (void)sprintf(X_rsa.vars.iqstream.filename_base, "%s%s_ut13_", 
        DATA_DIRECTORY_RAW,
        IQSTREAM_FILE_NAME_BASE);
    X_rsa.vars.iqstream.suffix_control = static_cast<int>(RSA_API::IQSSDFN_SUFFIX_TIMESTAMP);
    X_rsa.iqstream_set_vars();

    X_rsa.device_run();
    for (int ii = 0; ii < bangz_ut14; ii++)
    {
        (void)X_rsa.iqstream_clear_sticky();
        if (X_rsa.iqstream_record_siq() == CODEZ::_0_no_errors)
        {
            printf("\n%2d of %2d) bitcheck:  %d {1==good}  ,  acqStatus=0x%X {0==good}\n", 
                ii+1,
                bangz_ut14,
                X_rsa.iqstream_good_bitcheck(),
                X_rsa.vars.iqstream.fileinfo_type.acqStatus);
             X_util.filez_in.push_back( X_rsa.vars.iqstream.filenames_0_data);
        }
    }
    X_rsa.device_stop();
    X_rsa.device_disconnect();
    vprint(X_util.filez_in, "siq files are ready");

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}



////~~~~


static void ut14_decodew()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  decoding siq files, writing\n", __func__);
#endif                   
//~

    (void)X_util.batch_decode_write
    (
        DATA_DIRECTORY_RAW, 
        SIQ_RAW_EXT, 
        DATA_DIRECTORY_PROCESSED, 
        TAG_DECODED, 
        EXT_DECODED, 
        0L, 
        0L, 
        X_util.filez_in, 
        X_util.filez_out
    );
    vprint(X_util.filez_in, "raw inputs found");
    vprint(X_util.filez_out, "decoded outputs");

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut14_decodep()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  decoding siq files, printing\n", __func__);
#endif                   
//~

    (void)X_util.batch_decode_print
    (
        DATA_DIRECTORY_RAW, 
        SIQ_RAW_EXT,
        0L, 
        0L, 
        X_util.filez_in
    );
    vprint(X_util.filez_in, "raw inputs found");

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut14_batch()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  batch siq files, parse + IQ plot\n", __func__);
#endif                   
//~

    (void)X_siq.batch_process_files
    (
        DATA_DIRECTORY_RAW, 
        DATA_DIRECTORY_PROCESSED, 
        X_util.filez_in, 
        X_util.filez_out,
        false,
        false);
    vprint(X_util.filez_in, "raw inputs");
    vprint(X_util.filez_out, "outputs made");
    X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    
    (void)X_siq.batch_process_files
    (
        DATA_DIRECTORY_RAW, 
        DATA_DIRECTORY_PROCESSED, 
        X_util.filez_in, 
        X_util.filez_out,
        true,
        false);
    vprint(X_util.filez_in, "raw inputs");
    vprint(X_util.filez_out, "outputs made");
    X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);

    (void)X_siq.batch_process_files
    (
        DATA_DIRECTORY_RAW, 
        DATA_DIRECTORY_PROCESSED, 
        X_util.filez_in, 
        X_util.filez_out,
        false,
        true);
    vprint(X_util.filez_in, "raw inputs");
    vprint(X_util.filez_out, "outputs made");
    X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);

    (void)X_siq.batch_process_files
    (
        DATA_DIRECTORY_RAW, 
        DATA_DIRECTORY_PROCESSED, 
        X_util.filez_in, 
        X_util.filez_out,
        true,
        true);
    vprint(X_util.filez_in, "raw inputs");
    vprint(X_util.filez_out, "outputs made");
    X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void vprint(std::vector<std::string>& anyv, const char* message)
{
    if (anyv.size() > 0)
    {
        printf("\n%s:\n", message);
        for(std::size_t ii = 0; ii < anyv.size(); ii++)
        {
            printf("\t%s\n", anyv[ii].c_str());
        }
    }
    else
    {
        printf("*.size() =  %lu\n", anyv.size());
    }
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_14.cpp
