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
    const int    smode,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const int    trace_number,
    const double rbw,
    const double span,
    const int    tlen,
    const double threshold, 
    int          record_ms,
    char*        active_directory
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
    // if ((fstart - (span/2)) < 0)
    // {
    //     printf("%d\n", __LINE__);
    //     return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    // }
#endif
    float maxp = -999.999;       
    double cf;
    if (fstart < (span/2))
    {
        cf = span/2;
    }
    else
    {
        cf = fstart;
    }
    (void)this->device_stop();

    // a directory is created for output that may or may not occur during this trace
    this->reftime_get_vars();
    if (smode == static_cast<int>(sMode::smode_1))
    {
        (void)sprintf(active_directory, "%severything_%lu/", 
            DATA_DIRECTORY_SEQUENCED, 
            this->_vars.reftime.current.timestamp);
    }
    else if (smode == static_cast<int>(sMode::smode_2))
    {
        (void)sprintf(active_directory, "%sthreshold_%lu/", 
            DATA_DIRECTORY_SEQUENCED, 
            this->_vars.reftime.current.timestamp);
    }
    else
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->cutil.exe_mkdir(active_directory) != CODEZ::_0_no_errors)
    {
        printf("%s\n", active_directory);
        return this->cutil.get_status_code();
    }

    // DEVICE, ensure trigger event is set as query
    this->_vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);
    this->vars.device.event_id = this->_vars.device.event_id;

    // TRIG, ensure triggers are off
    this->vars.trig.mode_select       = RSA_API::TriggerMode::freeRun;
    this->vars.trig.if_power_level    = threshold;
    this->vars.trig.position_percent  = this->vars.trig.POSITION_PERCENT_MAX / 2;
    this->vars.trig.source_select     = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;
    this->vars.trig.transition_select = RSA_API::TriggerTransitionLH;
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
        (void)this->device_stop();  

        // move the center frequency
        this->vars.config.center_frequency_hz = cf;
        (void)this->_config_set_center_frequency_hz();

        // begin by collecting SPECTRUM data
        this->vars.spectrum.is_enabled_measurement = true;    
        (void)this->_spectrum_set_vars();               
        
        (void)this->device_run();

        // check the spectrum at current center frequency
        if (this->spectrum_acquire_data(trace_number) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }

        // find max power, match with frequency
        if (this->spectrum_find_peak_index(trace_number) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
        maxp = this->_vars.spectrum.trace_power_v[trace_number][this->_vars.spectrum.peak_index[trace_number]];
        (void)this->spectrum_make_frequency_v();
        printf("cf=  %15.5lf MHz  ,  max_dBm=  %12.6f  @  %15.5lf MHz    ", 
            cf/1.0e6, 
            maxp,
            this->_vars.spectrum.frequency_v[this->_vars.spectrum.peak_index[trace_number]]/1.0e6);
        (void)this->reftime_get_vars();

        if (smode == sMode::smode_1)    // dump everything, regarless of threshold
        {
            (void)printf("writing files...");
            (void)sprintf(this->_holder, "%s%s_%lu.%s", 
                active_directory, 
                SPECTRUM_FILE_NAME_BASE, 
                this->_vars.reftime.current.timestamp,
                DATA_DEFAULT_EXT);
            (void)this->spectrum_write_csv(this->_holder, trace_number);
            (void)this->ifstream_record_r3f();
            (void)this->iqstream_record_siq();
        }
        if ((smode == sMode::smode_2) && (maxp > threshold))    // only dump files if threshold exceeded
        {
            (void)printf("threshold exceeded, writing files...");
            (void)sprintf(this->_holder, "%s%s_%lu.%s", 
                active_directory, 
                SPECTRUM_FILE_NAME_BASE, 
                this->_vars.reftime.current.timestamp,
                DATA_DEFAULT_EXT);
            (void)this->spectrum_write_csv(this->_holder, trace_number);
            (void)this->ifstream_record_r3f();
            (void)this->iqstream_record_siq();
        }
        printf("\n");
        cf = cf + span/2;  // increment
    }
    (void)this->device_stop();
    this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    return this->trig_set_vars();
}


////////~~~~~~~~END>  rsa306b_scan_dump.cpp
