/*
    special function, combines several API groups

    public :
        < 1 >  spectrum_scanner()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    settings not included in the paramteers are made in advance
*/
CODEZ rsa306b_class::spectrum_scanner
(
    const int    trace_number,
    const double fstart, 
    const double fstop, 
    const double threshold, 
    const int    loitering,
    char*        file_path_name,
    const double reflevel,
    const double rbw,
    const double span,
    const int    tlen
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
        printf("%d\n", __LINE__);
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (file_path_name == NULL)
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
    if 
    (
        (loitering < 1) || 
        (loitering > 69)
    )
    {
        printf("%d\n", __LINE__);
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
    this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    (void)this->trig_set_vars();
    this->vars.config.reference_level_dbm = reflevel;
    if (this->_config_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    this->vars.spectrum.is_enabled_trace[trace_number] = true;
    this->vars.spectrum.detector_select[trace_number]  = RSA_API::SpectrumDetectors::SpectrumDetector_PosPeak;
    this->vars.spectrum.settings_type.rbw              = rbw;
    this->vars.spectrum.settings_type.span             = span;
    this->vars.spectrum.settings_type.traceLength      = tlen;
    if (this->_spectrum_set_vars() != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    
    float       p_avg      = 0;                  // average power for a frequency, once "loitering" points have been acquired
    float       maxp       = -999999999.9;       // indicates maximum power level detected during acquisition
    double      maxf       = maxp;               // indicates frequency that the maximum power level detected occured
    std::size_t vcnt       = 0UL;                // total data counter, incremented for each (frequency, power) pair acquired
    std::vector<float> pow_getter[loitering];    // holds power levels detected at fixed center frequency to assist in averaging
    std::vector<float> collector_pow;            // cummulative power collected over the scan
    std::vector<double> collector_frq;           // cummulative frequency collected over the scan
    

    // std::vectors are prepared for acquisition
    collector_pow.resize(INIT_STL_LENGTH);
    collector_frq.resize(INIT_STL_LENGTH); 
    collector_pow.clear();  
    collector_frq.clear();   

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

        // loitering a few times at each center frequency, when used with averaging, helps smooth the data
        for (int xx = 0; xx < loitering; xx++)
        {
            if (this->spectrum_acquire_data(trace_number) != CODEZ::_0_no_errors)
            {
                return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
            }
            pow_getter[xx].resize(this->_vars.spectrum.trace_power_v[trace_number].size());
            for (std::size_t rr = 0UL; rr < this->_vars.spectrum.trace_power_v[trace_number].size(); rr++)
            {
                pow_getter[xx][rr] = this->_vars.spectrum.trace_power_v[trace_number][rr];
            }
        }

        // selected center frequency has "loitering" (frequency, power) pairs for the trace, find average and max
        maxp = -999999999.9;
        maxf = maxp;

        for (int ii = 0; ii < this->_vars.spectrum.trace_points_acquired[trace_number]; ii++)
        {
            p_avg = 0;
            for (int jj = 0; jj < loitering; jj++)
            {
                p_avg = p_avg + pow_getter[jj][ii];
            }
            p_avg = p_avg / loitering;   // average for the power bin

            // update the cummulative std::vectors
            collector_frq.push_back
            (
                this->_vars.spectrum.settings_type.actualStartFreq + 
                this->_vars.spectrum.settings_type.actualFreqStepSize * ii
            );
            collector_pow.push_back(p_avg);

            if(maxp < p_avg)    // update
            {
                maxp = collector_pow[vcnt];
                maxf = collector_frq[vcnt];
            }
            vcnt++;   // increment running total
        }
        
        // report processing results to stdout
        printf("cummulative:  %9lu,  current:  %5d >>> cf MHz=  %9.3lf  ,  span MHz=  %9.3lf  ,  " ,
            vcnt,
            this->_vars.spectrum.trace_points_acquired[trace_number],
            this->_vars.config.center_frequency_hz/1e6,
            this->_vars.spectrum.settings_type.span/1e6);
        printf("[ max MHz=  %9.3lf  ,  max dBm=  %9.3lf ]  ",
            maxf/1e6,
            maxp);
            if(maxp > threshold) // after aacquring and averaging, this is where you should further interogate the signal
            {
                printf("...THRESHOLD\n");    // a strong signal was identified, good time to do additional processing
            } 
            else
            {
                printf("...noise\n");    // nothing in this spectrum band, move onto the next signal
            }
        cf = cf + (span/2);  // increment
    }
    
    // all spectrum data is acquired

    if 
    (
        collector_frq.size() < 10UL ||
        collector_pow.size() < 10UL
    )
    {
        return this->cutil.report_status_code(CODEZ::_2_error_in_logic);
    }

    // all data was acquired and processed, write the CSV
    if (file_path_name[0] == '\0')
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_t%d__%lu_.%s",
            DATA_DIRECTORY_PROCESSED,
            SPECTRUM_FILE_NAME_BASE,
            trace_number,
            this->_vars.reftime.current.timestamp,
            DATA_DEFAULT_EXT);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    this->_fp_write = fopen(this->_helper, "w");
    if (this->_fp_write == NULL) 
    {
        return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
    }

    (void)sprintf(this->_helper, "%s,%s\n",
        SPECTRUM_FIELD_1,
        SPECTRUM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < vcnt; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.5lf,%0.5f\n",
            collector_frq[idx],
            collector_pow[idx]);
        if(fputs(this->_helper, this->_fp_write) < 0)
        {
            if (fclose(this->_fp_write) != 0)
            {
                return this->cutil.report_status_code(CODEZ::_10_fclose_failed);
            }
            return this->cutil.report_status_code(CODEZ::_31_fputs_failed);
        }
    }

    if(fclose(this->_fp_write) != 0)
    {
        return this->cutil.report_status_code(CODEZ::_16_fclose_failed);
    }
    this->_fp_write = NULL;
    return this->device_stop();
}


////////~~~~~~~~END>  rsa306b_spectrum_scanner.cpp
