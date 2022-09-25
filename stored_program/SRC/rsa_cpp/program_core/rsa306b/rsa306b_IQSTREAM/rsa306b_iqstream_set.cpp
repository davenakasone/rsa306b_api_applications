/*
    API group "IQSTREAM"

    public :
        < 1 >  iqstream_set_vars()
    
    private :
        < 1 >  _iqstream_set_vars()
        < 2 >  _iqstream_set_acq_bandwidth()
        < 3 >  _iqstream_set_disk_file_length()
        < 4 >  _iqstream_set_disk_filename_base()
        < 5 >  _iqstream_set_filename_suffix()
        < 6 >  _iqstream_set_iq_data_buffer_size()
        < 7 >  _iqstream_set_output_configuration()
    
    always set the bandwidth first
    bandwidth determines sample rate and available buffer IQ pairs
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::iqstream_set_vars()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    return this->_iqstream_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqstream_set_vars()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    constexpr int callz = 6;
    CODEZ caught_call[callz];

    caught_call[0] = this->_iqstream_set_acq_bandwidth();
    caught_call[1] = this->_iqstream_set_disk_file_length();
    caught_call[2] = this->_iqstream_set_disk_filename_base();
    caught_call[3] = this->_iqstream_set_filename_suffix();
    caught_call[4] = this->_iqstream_set_iq_data_buffer_size();
    caught_call[5] = this->_iqstream_set_output_configuration();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqstream_set_acq_bandwidth()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    this->_iqstream_get_max_acq_bandwidth();
    this->_iqstream_get_min_acq_bandwidth();
    if (this->vars.iqstream.bandwidth < this->_vars.iqstream.bandwidth_min ||
        this->vars.iqstream.bandwidth > this->_vars.iqstream.bandwidth_max  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "bandwidth requested { %0.6lf }  out of range [ %lf : %lf ]",
                this->vars.iqstream.bandwidth,
                this->_vars.iqstream.bandwidth_min,
                this->_vars.iqstream.bandwidth_max);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    RSA_API::ReturnStatus temp =
        RSA_API::IQSTREAM_SetAcqBandwidth
        (
            this->vars.iqstream.bandwidth
        );
    (void)this->_iqstream_get_acq_parameters();    // sample rate depends on this, see p78
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
    no API use to get after set
    the record time determines the size
*/
CODEZ rsa306b_class::_iqstream_set_disk_file_length()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    
    if (this->vars.iqstream.record_time_ms < this->_vars.iqstream.RECORD_MSEC_MIN ||
        this->vars.iqstream.record_time_ms > this->_vars.iqstream.RECORD_MSEC_MAX  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "record time ms, requested{ %d }  out of range [ %d : %d ]",
                this->vars.iqstream.record_time_ms,
                this->_vars.iqstream.RECORD_MSEC_MIN,
                this->_vars.iqstream.RECORD_MSEC_MAX);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    this->_vars.iqstream.record_time_ms = this->vars.iqstream.record_time_ms;
    this->_api_status =
        RSA_API::IQSTREAM_SetDiskFileLength
        (
            this->_vars.iqstream.record_time_ms
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 4 > private
    no API use to get after set
*/
CODEZ rsa306b_class::_iqstream_set_disk_filename_base()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    if (this->vars.iqstream.filename_base == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "allocate the filename-base");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_25_pointer_is_null);
    }

    (void)strcpy(this->_vars.iqstream.filename_base, this->vars.iqstream.filename_base);
    this->_api_status =
        RSA_API::IQSTREAM_SetDiskFilenameBase
        (
            this->_vars.iqstream.filename_base
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
    no API use to get after set
*/
CODEZ rsa306b_class::_iqstream_set_filename_suffix()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    
    if (this->vars.iqstream.suffix_control < 
        (int)RSA_API::IQSSDFN_SUFFIX_NONE  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "suffix not in range,  requested { %d }  ,  required { %d, %d, or >= %d}",
                static_cast<int>(this->vars.iqstream.suffix_control),
                (int)RSA_API::IQSSDFN_SUFFIX_NONE,
                (int)RSA_API::IQSSDFN_SUFFIX_TIMESTAMP,
                static_cast<int>(RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    this->_vars.iqstream.suffix_control = this->vars.iqstream.suffix_control;
    this->_api_status = 
        RSA_API::IQSTREAM_SetDiskFilenameSuffix
        (
            this->_vars.iqstream.suffix_control
        );
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
    see p82
*/
CODEZ rsa306b_class::_iqstream_set_iq_data_buffer_size()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    
    if (this->vars.iqstream.buffer_multiplier != iqsBuff::X_1 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_2 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_3 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_4 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_5 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_6 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_7 &&
        this->vars.iqstream.buffer_multiplier != iqsBuff::X_8  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid buffer multiple selected:  %d",
                this->vars.iqstream.buffer_multiplier);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->_vars.iqstream.pairs_max = INIT_INT;
    for (int ii = 0; ii < IQSTREAM_INTERVALS; ii++)
    {
        if (ii < IQSTREAM_INTERVALS-2)
        {
            if 
            (
                this->_vars.iqstream.bandwidth > IQSTREAM_BANDWIDTH_RANGES[ii][0] &&
                this->_vars.iqstream.bandwidth < IQSTREAM_BANDWIDTH_RANGES[ii][1]  
            )
            {
                this->_vars.iqstream.pairs_max = 
                    IQSTREAM_BUFFER_SIZE_MEDIUM / pow(2, ii);
                break;
            }
        }
        else
        {
            if 
            (
                this->_vars.iqstream.bandwidth > IQSTREAM_BANDWIDTH_RANGES[ii][0] &&
                this->_vars.iqstream.bandwidth < IQSTREAM_BANDWIDTH_RANGES[ii][1] &&
                ii == IQSTREAM_INTERVALS-2                                         
            )
            {
                this->_vars.iqstream.pairs_max = IQSTREAM_BUFFER_SIZE_SMALL;
                break;
            }
            if 
            (
                this->_vars.iqstream.bandwidth > IQSTREAM_BANDWIDTH_RANGES[ii][0] &&
                this->_vars.iqstream.bandwidth < IQSTREAM_BANDWIDTH_RANGES[ii][1] &&
                ii == IQSTREAM_INTERVALS-1                                                       
            )
            {
                this->_vars.iqstream.pairs_max = IQSTREAM_BUFFER_SIZE_LARGE;
                break;
            }
        }
    }
    if (this->_vars.iqstream.pairs_max == INIT_INT)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "failed to set requsted pairs");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->_vars.iqstream.pairs_max = IQSTREAM_BUFFER_SIZE_MEDIUM;
    }
    
    this->_vars.iqstream.buffer_multiplier = this->vars.iqstream.buffer_multiplier;
    this->_vars.iqstream.pairs_max = this->_vars.iqstream.pairs_max * this->_vars.iqstream.buffer_multiplier;
    
    RSA_API::ReturnStatus temp =
        RSA_API::IQSTREAM_SetIQDataBufferSize
        (
            this->_vars.iqstream.pairs_max
        );
    (void)this->_iqstream_get_iq_data_buffer_size();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 7 > private
    no API use to get after set
*/
CODEZ rsa306b_class::_iqstream_set_output_configuration()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    if (this->vars.iqstream.datatype_select != RSA_API::IQSODT_SINGLE            &&
        this->vars.iqstream.datatype_select != RSA_API::IQSODT_INT32             &&
        this->vars.iqstream.datatype_select != RSA_API::IQSODT_INT16             &&
        this->vars.iqstream.datatype_select != RSA_API::IQSODT_SINGLE_SCALE_INT32 )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid number format selected");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT         &&
        this->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_TIQ       &&
        this->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_SIQ       &&
        this->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_SIQ_SPLIT &&
        this->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_MIDAS     &&
        this->vars.iqstream.destination_select != RSA_API::IQSOD_FILE_MIDAS_DET  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid output destination was selected");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    this->_vars.iqstream.datatype_select = this->vars.iqstream.datatype_select;
    this->_vars.iqstream.destination_select = this->vars.iqstream.destination_select;
    this->_api_status =
        RSA_API::IQSTREAM_SetOutputConfiguration
        (
            this->_vars.iqstream.destination_select,
            this->_vars.iqstream.datatype_select
        );
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_iqstream_set.cpp
