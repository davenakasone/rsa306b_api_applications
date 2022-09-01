/*
    used for making the class to parse "*.siq" files

    < 0 >  task_989()
    < 1 >  basic()
*/

#include "../testz.h"

static const char SIQ_OUT[BUF_C] = "./program_test/data/outputs_siq/task989";    // select a path and base name to write output files, *.siq
static const char CSV_OUT[BUF_C] = "./program_test/data/outputs_siq/task989";    // select a path and base name to write output files, *.csv
static const double CONFIG_DBM   = -44.4;                                        // select a power level for the data acquisition, in dBm
static const double CONFIG_CF    = 100.0e6;                                      // select a center frequency for the data acquisition, in Hz
static const double IQS_BW       = 1.56e6;                                       // select a bandwidth for the data acquisition, in Hz
static const int TIMEOUT_MS      = 1;                                            // select the timeout for triggered data acquisitions

static void basic(siq_manager_class* siq, rsa306b_class* rsa);    // basic test
static void stream_to_file(rsa306b_class* obj);                   // called to generate *.siq


void task_989()
{
    printf("\n%s()  ,  testing and making the 'siq_manager'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        siq_manager_class siq;
        rsa.device_connect();

        // make initial device settings
        rsa.vars.config.reference_level_dbm = CONFIG_DBM;   
        rsa.vars.config.center_frequency_hz = CONFIG_CF;    
        rsa.config_set_vars();
        rsa.vars.trig.if_power_level = CONFIG_DBM + 10;                        
        rsa.vars.trig.transition_select = RSA_API::TriggerTransitionEither;
        rsa.vars.trig.source_select = RSA_API::TriggerSourceIFPowerLevel;
        rsa.trig_set_vars();
        rsa.vars.iqstream.bandwidth = IQS_BW;                                        
        rsa.vars.iqstream.record_time_ms = TIMEOUT_MS;                              
        rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;     
        rsa.iqstream_set_vars();

        // test the siq_manager
        basic(&siq, &rsa);

    }
    printf("\n%s()  ,  test complete\n", __func__);
}


////~~~~


static void basic(siq_manager_class* siq, rsa306b_class* rsa)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    siq->print_header();
    siq->print_data(4,1);
    printf("executuion success:  %d {0==false}\n", siq->execution_success());
    siq->print_data(0,0);

    rsa->vars.trig.mode_select = RSA_API::freeRun;
    rsa->trig_set_vars();
    rsa->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
    rsa->vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_NONE;
    rsa->vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
    rsa->iqstream_set_vars();
    stream_to_file(rsa);

    printf("\nthe file made has :  %ld  bytes\n",
        siq->get_file_byte_length(rsa->vars.iqstream.fileinfo_type.filenames_0));
    siq->decode_and_print(rsa->vars.iqstream.fileinfo_type.filenames_0, 0, 49);
    sprintf(rsa->vars.gp.helper, "%s_decoded.txt", SIQ_OUT);
    siq->decode_and_write(rsa->vars.iqstream.fileinfo_type.filenames_0, rsa->vars.gp.helper, 0, 1500);

    siq->load_file(rsa->vars.iqstream.fileinfo_type.filenames_0);
    siq->print_header();
    siq->print_data(0, 9);
}







////~~~~


/*
    < 9 >
    acquires data from IQSTREAM
    displays the "*.siq" file made
    keep in mind:
        - stream path is handled by the class
        - "*.siq" files use same name for header and data (all in one)
*/
static void stream_to_file(rsa306b_class* obj)
{
    if (obj->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_SIQ)
    {
        printf("\n\twrong file type\n");
        return;
    }

    switch (obj->vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_single_freeRun", SIQ_OUT);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_single_triggered", SIQ_OUT);
            }
            break;
        case (RSA_API::IQSODT_INT32) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int32_freeRun", SIQ_OUT);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int32_triggered", SIQ_OUT);
            }
            break;
        case (RSA_API::IQSODT_INT16) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int16_freeRun", SIQ_OUT);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int16_triggered", SIQ_OUT);
            }
            break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_scaled_freeRun", SIQ_OUT);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_scaled_triggered", SIQ_OUT);
            }
            break;
        default :
            printf("\n\t there is a logic error in the IQSTREAM\n");
            return;
    }

    obj->iqstream_set_vars();
    obj->iqstream_acquire_data();
    printf("pairs copied  :  %ld\n", obj->vars.iqstream.fileinfo_type.numberSamples);
    if (obj->vars.iqstream.fileinfo_type.numberSamples <= 0)
    {
        return;
    }
    printf("file          :  %s\n", obj->vars.iqstream.fileinfo_type.filenames_0);
    printf("header        :  %s\n", obj->vars.iqstream.fileinfo_type.filenames_1);
}


/////////~~~~~~~~END>  task_989.cpp
