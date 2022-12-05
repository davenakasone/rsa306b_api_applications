/*
    special function, combines several API groups

    public :
        < 1 >  triggered_dump()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    settings not included in the paramteers are made in advance
*/
CODEZ rsa306b_class::triggered_dump                
(
    const int    loitering,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const double triglevel,
    const int    trace_number,
    const double rbw,
    const double span,
    const int    tlen,
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
    if 
    (
        (fstop < fstart) || 
        (fstart < this->vars.config.min_center_frequency_hz) || 
        (fstop > this->vars.config.max_center_frequency_hz)  ||
        (active_directory == NULL) ||
        ((fstop - fstart) < rbw) || 
        ((fstop - fstart) < span) ||
        (loitering < 0) ||
        (loitering > 69)
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
#endif     
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
    (void)sprintf(active_directory, "%striggered_%lu/", 
        DATA_DIRECTORY_SEQUENCED, 
        this->_vars.reftime.current.timestamp);
    if (this->cutil.exe_mkdir(active_directory) != CODEZ::_0_no_errors)
    {
        printf("%s\n", active_directory);
        return this->cutil.get_status_code();
    }

    // DEVICE, ensure trigger event is set as query
    this->_vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);
    this->vars.device.event_id = this->_vars.device.event_id;

    // TRIG, ensure triggers are off
    this->vars.trig.mode_select       = RSA_API::TriggerMode::triggered;
    this->vars.trig.if_power_level    = triglevel;
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
    this->vars.iqstream.buffer_multiplier  = iqsBuff::b4x;
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

    std::size_t cnt = static_cast<std::size_t>(0);
    // acquire the data from the SPECTRUM group, changing the center frequency every iteration
    while (cf <= fstop)
    {
        (void)this->device_stop();  
        this->vars.trig.mode_select = RSA_API::TriggerMode::triggered;
        (void)this->_trig_set_mode_select();
        
        // move the center frequency
        this->vars.config.center_frequency_hz = cf;
        (void)this->_config_set_center_frequency_hz();

        // begin by collecting SPECTRUM data
        this->vars.spectrum.is_enabled_measurement = true;    
        (void)this->_spectrum_set_vars();               
        (void)this->device_run();

        for (int lot = 0; lot < loitering; lot++)
        {
            cnt++;
            (void)printf("%5lu [%2d / %2d]  cf=  %15.5lf MHz  ,  ", 
                cnt, lot+1, loitering, cf/1.0e6);
            if (this->device_check_event() == false)
            {
                printf("no trigger...\n");
                continue;
            }
            
            this->device_stop();
            this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
            (void)this->_trig_set_mode_select();
            this->device_run();

            (void)this->spectrum_acquire_data(trace_number);
            (void)this->spectrum_make_frequency_v();
            (void)this->spectrum_find_peak_index(trace_number);

            printf("TRIGGERED,  max_dBm=  %12.6f  @  %15.6lf MHz,  writting files\n",
                this->_vars.spectrum.trace_power_v[trace_number][this->_vars.spectrum.peak_index[trace_number]],
                this->_vars.spectrum.frequency_v[this->_vars.spectrum.peak_index[trace_number]]/1.0e6);
            (void)this->reftime_get_vars();

            (void)sprintf(this->_holder, "%s%s_%lu.%s", 
                active_directory, 
                SPECTRUM_FILE_NAME_BASE, 
                this->_vars.reftime.current.timestamp,
                DATA_DEFAULT_EXT);
            (void)this->spectrum_write_csv(this->_holder, trace_number);
            (void)this->ifstream_record_r3f();
            (void)this->iqstream_record_siq();
        }
        cf = cf + span/2;  // increment
    }
    (void)this->device_stop(); 
    this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    return this->trig_set_vars();
}


////////~~~~~~~~END>  rsa306b_triggered_dump.cpp
