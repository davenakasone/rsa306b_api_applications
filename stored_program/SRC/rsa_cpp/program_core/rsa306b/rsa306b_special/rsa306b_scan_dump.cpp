/*
    special function, combines several API groups

    public :
        < 1 >  scan_dump()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    settings not included in the paramteers are made in advance
*/
CODEZ rsa306b_class::scan_dump                    
(
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const int    trace_number,
    const double rbw,
    const double span,
    const int    tlen,
    const double threshold, 
    int record_ms,
    char* active_directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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
    if (active_directory == NULL)
    {
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (fstop < fstart) || 
        (fstart < 0)     || 
        (fstop < 0)
    )
    {
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (fstart < this->vars.config.min_center_frequency_hz) || 
        (fstop > this->vars.config.max_center_frequency_hz)
    )
    {
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        ((fstop - fstart) < rbw) || 
        ((fstop - fstart) < span)
    )
    {
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if ((fstart - (span/2)) < 0)
    {
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
#endif
    (void)this->device_stop();

    float maxp = -999.999;       
    double cf = fstart;

    // a directory is created for output that may or may not occur during this trace
    this->reftime_get_vars();
    (void)sprintf(active_directory, "%s_%lu/", DATA_DIRECTORY_SEQUENCED, this->_vars.reftime.current.timestamp);
    if (this->cutil.exe_mkdir(active_directory) != CODEZ::_0_no_errors)
    {
        printf("%s\n", active_directory);
        return this->cutil.get_status_code();
    }

    // TRIG, ensure triggers are off
    this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    if (this->trig_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }

    // CONFIG reference level is set to parameter (center frequency will change accross range)
    this->vars.config.reference_level_dbm = reflevel;
    if (this->_config_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }

    // the SPECTRUM is set to parameters
    this->vars.spectrum.is_enabled_trace[trace_number] = true;
    this->vars.spectrum.detector_select[trace_number]  = RSA_API::SpectrumDetectors::SpectrumDetector_PosPeak;
    this->vars.spectrum.settings_type.rbw              = rbw;
    this->vars.spectrum.settings_type.span             = span;
    this->vars.spectrum.settings_type.traceLength      = tlen;
    if (this->_spectrum_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }

    // the IQSTREAM is preset to output SIQ files
    this->vars.iqstream.bandwidth = span;
    this->vars.iqstream.record_time_ms     = record_ms;
    this->vars.iqstream.suffix_control     = static_cast<int>(RSA_API::IQSSDFN_SUFFIX_TIMESTAMP);
    this->vars.iqstream.datatype_select    = RSA_API::IQSOUTDTYPE::IQSODT_SINGLE;
    this->vars.iqstream.buffer_multiplier  = iqsBuff::b2x;
    this->vars.iqstream.destination_select = RSA_API::IQSOUTDEST::IQSOD_FILE_SIQ;
    (void)sprintf(this->vars.iqstream.filename_base, "%s%s", active_directory, IQSTREAM_FILE_NAME_BASE);
    if (this->iqstream_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }

    // the IFSTREAM is preset to output R3F files
    (void)strcpy(this->vars.ifstream.file_path, active_directory);
    (void)strcpy(this->vars.ifstream.file_name_base, IFSTREAM_FILE_NAME_BASE);
    this->vars.ifstream.file_count                = 1;
    this->vars.ifstream.is_enabled                = false;
    this->vars.ifstream.file_name_suffix          = static_cast<int>(RSA_API::IFSSDFN_SUFFIX_TIMESTAMP);
    this->vars.ifstream.file_length_max_ms        = record_ms;
    this->vars.ifstream.output_destination_select = RSA_API::IFSOUTDEST::IFSOD_FILE_R3F;
    if (this->ifstream_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }

    // acquire the data from the SPECTRUM group, changing the center frequency every iteration
    while (cf < fstop)
    {
        // move the center frequency
        this->vars.config.center_frequency_hz = cf;
        (void)this->_config_set_center_frequency_hz();

        // begin by collecting SPECTRUM data
        this->vars.spectrum.is_enabled_measurement = true;    
        (void)this->_spectrum_set_vars();               
        
        // check the spectrum at current center frequency
        (void)this->device_run();
        if (this->spectrum_acquire_data(trace_number) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
        this->device_stop();

        // see if any measurement exceeded the threshold
        if (this->spectrum_find_peak_index(trace_number) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
        maxp = this->_vars.spectrum.trace_power_v[trace_number][this->_vars.spectrum.peak_index[trace_number]];
        printf("cf=  %15.5lf MHz  ,  dBm=  %12.6f  ...", cf/1.0e6, maxp);
        if ( maxp > threshold)
        {
             // threshold was exceeded, get the SPECTRUM data
            (void)printf("writing files\n");
            (void)this->reftime_get_vars();
            (void)sprintf(this->_holder, "%s%s_%lu.%s", 
                active_directory, 
                SPECTRUM_FILE_NAME_BASE, 
                this->_vars.reftime.current.timestamp,
                DATA_DEFAULT_EXT);
            (void)this->spectrum_make_frequency_v();
            (void)this->spectrum_write_csv(this->_holder, trace_number);
            this->vars.spectrum.is_enabled_measurement = false;   
            (void)this->_spectrum_set_vars();  
            
            // threshold was exceeded, get the R3F file
            (void)this->ifstream_set_vars();
            (void)this->device_run();
            (void)this->ifstream_record_r3f();
            (void)this->device_stop();

            // threshold was exceeded, get the SIQ file
            (void)this->iqstream_set_vars();
            (void)this->device_run();
            (void)this->iqstream_record_siq();
            (void)this->device_stop();
        }
        else
        {
            printf("threshold not exceeded\n");
        }
        cf = cf + span/2;  // increment
    }
    return this->device_stop();
}


////////~~~~~~~~END>  rsa306b_scan_dump.cpp
