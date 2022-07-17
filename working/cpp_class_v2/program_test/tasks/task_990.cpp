/*
    there appears to be a problem switching from IQSTREAM
        if the stream goes to the client, then to a file, the API appears to break
    see if you can find a bug
    keep it around the FM-band, since most place have radio stations providing free data
    if you are somewhere with no radio reception, then the data will be all 0

    < 0 >  task_990()
    < 1 >
    < 6 > get_file_stream()
    < 7 > get_client_stream()
    < 8 > stream_to_file()
    < 9 > stream_to_client()
*/

#include "../testz.h"

// task 990 constants
static const double CONFIG_DBM      = -33.3;                                     // select a power level for the data acquisition, in dBm
static const double CONFIG_CF       = 100.0e6;                                   // select a center frequency for the data acquisition, in Hz
static const double IQS_BW          = 4.56e6;                                    // select a bandwidth for the data acquisition, in Hz
static const int IQS_ACQZ           = 3;                                         // select number of data acquisitions to perform on each data type
static const int TIMEOUT_MS         = 1;                                         // select the timeout for triggered data acquisitions
static const std::size_t V_IDX      = 99;                                        // select an index to display in the std::vector<RSA_API::Cplx*>
static const char OUTFILE_PN[BUF_C] = "./program_test/data/outputs_siq/t990";    // select a path and base name to write output files


static void test_a(rsa306b_class* obj);    // untriggered, file stream, all 4 datatypes
static void test_b(rsa306b_class* obj);    // untriggered, client stream, all 4 datatypes

static void get_file_stream(rsa306b_class* obj, RSA_API::TriggerMode trig_mode);    // call to make "*.siq" files, all 4 data   
static void get_client_stream(rsa306b_class* obj, RSA_API::TriggerMode trig_mode);    // call to make "*.siq" files  
static void stream_to_file(rsa306b_class* obj);
static void stream_to_client(rsa306b_class* obj, int idx);


/*
    < 0 >
    drives the tests for task #990
*/
void task_990()
{
    printf("\n%s()  ,  make sure IQSTREAM can switch\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        rsa.vars.config.reference_level_dbm = CONFIG_DBM;    // see "task 990 constants"
        rsa.vars.config.center_frequency_hz = CONFIG_CF;     // see "task 990 constants"
        rsa.config_set_vars();

        sprintf(rsa.vars.iqstream.filename_base, OUTFILE_PN);                        // see "task 990 constants"
        rsa.vars.iqstream.bandwidth = IQS_BW;                                        // see "task 990 constants"
        rsa.vars.iqstream.record_time_ms = TIMEOUT_MS;                               // see "task 990 constants"
        rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN;    // could change, but should not
        rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;     // could change, but should not
        rsa.iqstream_set_vars();

        // select the test here, use comments to activate and deactivate
        test_a(&rsa);
        test_b(&rsa);
    }
    printf("\n%s()  ,  test complete\n", __func__);
}

////~~~~

/*
    < 6 >
    needs to know trigger mode, then IQSTREAM files are acquired
    you should verify the "*.siq" file that is output
*/
static void get_file_stream(rsa306b_class* obj, RSA_API::TriggerMode trig_mode)    
{
    obj->vars.trig.mode_select = RSA_API::freeRun;
    obj->trig_set_vars();
    obj->vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
    
    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;    
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_file(obj);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::CplxInt32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT32;    
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_file(obj);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::CplxInt16>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT16;    
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_file(obj);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;    
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_file(obj);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    printing stdout confirms std::vector was populated
    also, you should verify the "*.csv" file that is output
        note that the incremeter resets when caller leaves scope
*/
static void test_b(rsa306b_class* obj)   
{
    obj->vars.trig.mode_select = RSA_API::freeRun;
    obj->trig_set_vars();
    obj->vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;

    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_client(obj, ii);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::CplxInt32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT32;
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_client(obj, ii);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::CplxInt16>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT16;
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_client(obj, ii);
    }
    obj->iqstream_clear_sticky();

    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
    obj->iqstream_set_vars();
    printf("\n");
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        stream_to_client(obj, ii);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    < 8 >
    acquires data from IQSTREAM
    displays the "*.siq" file made
    keep in mind:
        - stream type is handled by class
        - "*.siq" files use same name for header and data (all in one)
*/
static void stream_to_file(rsa306b_class* obj)
{
    obj->iqstream_acquire_data();
    printf("file:  %s  ,  header:  %s\n", 
        obj->vars.iqstream.fileinfo_type.filenames_0,
        obj->vars.iqstream.fileinfo_type.filenames_1);
}


////~~~~


/*
    < 9 >
    acquires data from IQSTREAM
    displays data for an index of interest
    makes a "*.csv" file of all std::vector values
*/
static void stream_to_client(rsa306b_class* obj, int idx)
{
    obj->iqstream_acquire_data();

    switch (obj->vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE) :
            printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[%ld].i =  %f  ,  cplx32_v[%ld].q = %f\n",
                idx,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplx32_v.size(),
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].q);
            snprintf(obj->vars.gp.helper, BUF_E, "%s_cplx32_%d.csv", OUTFILE_PN, idx);
            break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) :
            printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[%ld].i =  %f  ,  cplx32_v[%ld].q = %f\n",
                idx,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplx32_v.size(),
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].q);
            snprintf(obj->vars.gp.helper, BUF_E, "%s_cplx32s_%d.csv", OUTFILE_PN, idx);
            break;
        case (RSA_API::IQSODT_INT16) :
            printf("%4d)  pairs copied:  %d  ,  cplxInt16_v.size() = %ld  ,  cplxInt16_v[%ld].i =  %d  ,  cplxInt16_v[%ld].q = %d\n",
                idx,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplxInt16_v.size(),
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].q);
            snprintf(obj->vars.gp.helper, BUF_E, "%s_cplxInt16_%d.csv", OUTFILE_PN, idx);
            break;
        case (RSA_API::IQSODT_INT32) :
            printf("%4d)  pairs copied:  %d  ,  cplxInt32_v.size() = %ld  ,  cplxInt32_v[%ld].i =  %d  ,  cplxInt32_v[%ld].q = %d\n",
                idx,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplxInt16_v.size(),
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].q);
            snprintf(obj->vars.gp.helper, BUF_E, "%s_cplxInt32_%d.csv", OUTFILE_PN, idx);
            break;
        default :
            printf("\n\t there is a logic error in the IQSTREAM datatype\n");
            return;
    }

    obj->iqstream_make_csv(obj->vars.gp.helper);
    printf("\t%s\n", obj->vars.gp.helper);
}


/////////~~~~~~~~END>  task_990.cpp
