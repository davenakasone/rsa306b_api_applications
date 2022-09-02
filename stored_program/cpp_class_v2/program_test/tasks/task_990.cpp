/*
    there appears to be a problem switching from IQSTREAM
        if the stream goes to the client, then to a file, the API appears to break
    see if you can find a bug
    keep it around the FM-band, since most place have radio stations providing free data
    if you are somewhere with no radio reception, then the data will be all 0

    note that the ouput file incremeter resets when caller leaves scope
    tests: a, b, c, and d work fine, test e is the concern
    test "f" is for future needs

    < 0 >  task_990()
    < 1 >  test_a()
    < 2 >  test_b()
    < 3 >  test_c()
    < 4 >  test_d()
    < 5 >  test_e()
    < 6 >  test_f()
    < 7 >  get_stream()
    < 8 >  stream_to_file()
    < 9 >  stream_to_client()
*/

#include "../testz.h"

// task 990 constants
static const double CONFIG_DBM      = -44.4;                                        // select a power level for the data acquisition, in dBm
static const double CONFIG_CF       = 100.0e6;                                      // select a center frequency for the data acquisition, in Hz
static const double IQS_BW          = 1.56e6;                                       // select a bandwidth for the data acquisition, in Hz
static const int IQS_ACQZ           = 3;                                            // select number of data acquisitions to perform on each data type
static const int TIMEOUT_MS         = 1;                                            // select the timeout for triggered data acquisitions
static const std::size_t V_IDX      = 99;                                           // select an index to display in the std::vector<RSA_API::Cplx*>
static const char OUTFILE_PN[BUF_C] = "./program_test/data/outputs_siq/task990";    // select a path and base name to write output files

static void test_a(rsa306b_class* obj);    // untriggered, file stream, all 4 datatypes, "IQS_ACQZ" times
static void test_b(rsa306b_class* obj);    // untriggered, client stream, all 4 datatypes, "IQS_ACQZ" times
static void test_c(rsa306b_class* obj);    // triggered, file stream, all 4 datatypes, "IQS_ACQZ" times
static void test_d(rsa306b_class* obj);    // triggered, client stream, all 4 datatypes, "IQS_ACQZ" times
static void test_e(rsa306b_class* obj);    // triggered + untriggered, changes everything
//static void test_f(rsa306b_class* obj);    // put the forced trigger here

static void get_stream(rsa306b_class* obj, RSA_API::TriggerMode trig_mode, RSA_API::IQSOUTDEST stream_to);    // call get the stream  
static void stream_to_file(rsa306b_class* obj);                                                               // helper 
static void stream_to_client(rsa306b_class* obj);                                                             // helper


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

        rsa.vars.trig.if_power_level = CONFIG_DBM + 10;                        // change some
        rsa.vars.trig.transition_select = RSA_API::TriggerTransitionEither;
        rsa.vars.trig.source_select = RSA_API::TriggerSourceIFPowerLevel;
        rsa.trig_set_vars();

        rsa.vars.iqstream.bandwidth = IQS_BW;                                        // see "task 990 constants"
        rsa.vars.iqstream.record_time_ms = TIMEOUT_MS;                               // see "task 990 constants"
        rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_TIMESTAMP;        // could change, but should not
        rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;     // could change, but should not
        rsa.iqstream_set_vars();

        // select the test here, use comments to activate and deactivate
        test_a(&rsa);
        test_b(&rsa);
        test_c(&rsa);
        test_d(&rsa);
        test_e(&rsa);
        //test_f(&rsa); // for future tests, uncomment prototype and definition
    }
    printf("\n%s()  ,  test complete\n", __func__);
}


////~~~~


/*
    < 1 >
    freeRun / untriggered
    get all 4 data types, streamed to file
    reapeats acquisition for "IQS_ACQZ"
*/
static void test_a(rsa306b_class* obj)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    < 2 >
    freeRun / untriggered
    get all 4 data types, streamed to client
    reapeats acquisition for "IQS_ACQZ"
*/
static void test_b(rsa306b_class* obj)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
}



////~~~~


/*
    < 3 >
    triggered
    get all 4 data types, streamed to client
    reapeats acquisition for "IQS_ACQZ"
*/
static void test_c(rsa306b_class* obj)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    < 4 >
    triggered
    get all 4 data types, streamed to file
    reapeats acquisition for "IQS_ACQZ"
*/
static void test_d(rsa306b_class* obj)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    < 5 >
    many variations in the IQSTREAM acquisition
*/
static void test_e(rsa306b_class* obj)
{
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
    
    // reverse the sequence
    
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_FILE_SIQ);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::triggered, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
    printf("<%d>  %s()\n", __LINE__, __func__);
    for (int ii = 0; ii < IQS_ACQZ; ii++)
    {
        get_stream(obj, RSA_API::freeRun, RSA_API::IQSOD_CLIENT);
    }
    obj->iqstream_clear_sticky();
}


////~~~~


/*
    < 6 >
    many variations in the IQSTREAM acquisition

static void test_f(rsa306b_class* obj)
{
    printf("\nTODO\n");
}
*/



////~~~~


/*
    < 7 >
    caller prvovides:
        - streaming class instance with active connection
        - trigger mode
        - streaming destination
    all 4 data types are streamed
        client streams use a "*.csv" file to display std::vector<Cplx*>
        file streams should only be "*.siq" files
*/
static void get_stream
(
    rsa306b_class* obj, 
    RSA_API::TriggerMode trig_mode, 
    RSA_API::IQSOUTDEST stream_to
) 
{
    if (trig_mode != RSA_API::freeRun && trig_mode != RSA_API::triggered)
    {
        printf("\n\t!!! invalid trigger mode\n");
        return;
    }
    if (stream_to != RSA_API::IQSOD_CLIENT && stream_to != RSA_API::IQSOD_FILE_SIQ)
    {
        printf("\n\t!!! invalid stream destination\n");
        return;
    }
    obj->vars.trig.mode_select = trig_mode;
    obj->vars.iqstream.destination_select = stream_to;

    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
    stream_to_client(obj);
    stream_to_file(obj);

    // std::vector<RSA_API::CplxInt32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT32;
    stream_to_client(obj);
    stream_to_file(obj);

    // std::vector<RSA_API::CplxInt16>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_INT16;
    stream_to_client(obj);
    stream_to_file(obj);

    // std::vector<RSA_API::Cplx32>
    obj->vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
    stream_to_client(obj);
    stream_to_file(obj);

    printf("\n");
}


////~~~~


/*
    < 8 >
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
        return;
    }

    switch (obj->vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_single_freeRun", OUTFILE_PN);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_single_triggered", OUTFILE_PN);
            }
            break;
        case (RSA_API::IQSODT_INT32) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int32_freeRun", OUTFILE_PN);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int32_triggered", OUTFILE_PN);
            }
            break;
        case (RSA_API::IQSODT_INT16) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int16_freeRun", OUTFILE_PN);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_int16_triggered", OUTFILE_PN);
            }
            break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) :
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_scaled_freeRun", OUTFILE_PN);
            }
            else
            {
                sprintf(obj->vars.iqstream.filename_base, "%s_scaled_triggered", OUTFILE_PN);
            }
            break;
        default :
            printf("\n\t there is a logic error in the IQSTREAM datatype\n");
            return;
    }

    obj->trig_set_vars();
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


////~~~~


/*
    < 9 >
    acquires data from IQSTREAM
    displays data for an index of interest
    makes a "*.csv" file of all std::vector values
*/
static void stream_to_client(rsa306b_class* obj)
{
    if (obj->vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT)
    {
        return;
    }
    obj->trig_set_vars();
    obj->reftime_get_vars();
    obj->iqstream_set_vars();
    obj->iqstream_acquire_data();
    switch (obj->vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE) :
            if (obj->vars.iqstream.cplx32_v.size() <= obj->constants.INIT_STL_LENGTH)
            {
                return;
            }
            printf("%ld)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[%ld].i =  %f  ,  cplx32_v[%ld].q = %f\n",
                obj->vars.reftime.current.timestamp,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplx32_v.size(),
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].q);
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_single_freeRun.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            else
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_single_triggered.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            break;
        case (RSA_API::IQSODT_INT32) :
            if (obj->vars.iqstream.cplxInt32_v.size() <= obj->constants.INIT_STL_LENGTH)
            {
                return;
            }
            printf("%ld)  pairs copied:  %d  ,  cplxInt32_v.size() = %ld  ,  cplxInt32_v[%ld].i =  %d  ,  cplxInt32_v[%ld].q = %d\n",
                obj->vars.reftime.current.timestamp,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplxInt16_v.size(),
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].q);
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_int32_freeRun.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            else
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_int32_triggered.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            break;
        case (RSA_API::IQSODT_INT16) :
            if (obj->vars.iqstream.cplxInt16_v.size() <= obj->constants.INIT_STL_LENGTH)
            {
                return;
            }
            printf("%ld)  pairs copied:  %d  ,  cplxInt16_v.size() = %ld  ,  cplxInt16_v[%ld].i =  %d  ,  cplxInt16_v[%ld].q = %d\n",
                obj->vars.reftime.current.timestamp,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplxInt16_v.size(),
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplxInt16_v[V_IDX].q);
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_int16_freeRun.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            else
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_int16_triggered.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) :
            if (obj->vars.iqstream.cplx32_v.size() <= obj->constants.INIT_STL_LENGTH)
            {
                return;
            }
            printf("%ld)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[%ld].i =  %f  ,  cplx32_v[%ld].q = %f\n",
                obj->vars.reftime.current.timestamp,
                obj->vars.iqstream.pairs_copied,
                obj->vars.iqstream.cplx32_v.size(),
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].i,
                V_IDX,
                obj->vars.iqstream.cplx32_v[V_IDX].q);
            if (obj->vars.trig.mode_select == RSA_API::freeRun)
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_scaled_freeRun.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            else
            {
                snprintf(obj->vars.gp.helper, BUF_E, "%s_%ld_scaled_triggered.csv", 
                    OUTFILE_PN, obj->vars.reftime.current.timestamp);
            }
            break;
        default :
            printf("\n\t there is a logic error in the IQSTREAM datatype\n");
            return;
    }
    obj->iqstream_make_csv(obj->vars.gp.helper);
    printf("\t%s\n", obj->vars.gp.helper);
}


/////////~~~~~~~~END>  task_990.cpp
