/*
    API group "SPECTRUM"

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
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (file_path_name == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (fstop < fstart) || 
        (fstart < 0)     || 
        (fstop < 0)
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (fstart < this->vars.config.min_center_frequency_hz) || 
        (fstop > this->vars.config.max_center_frequency_hz)
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        ((fstop - fstart) < rbw) || 
        ((fstop - fstart) < span)
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (loitering < 1) || 
        (loitering > 69)
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)this->device_stop();

    this->vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    this->trig_set_vars();

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
#endif
    
    float*      data       = NULL;               // the raw pointer, dynamically allocated and deallocated, to get data from the API
    float       p_avg      = 0;                  // average power for a frequency, once "loitering" points have been acquired
    bool        is_ready   = false;              // indicator for the API to unblock the program and proceed to data acquisition
    float       maxp       = -999999999.9;       // indicates maximum power level detected during acquisition
    double      maxf       = maxp;               // indicates frequency that the maximum power level detected occured
    double      cf         = 0;                  // marks the current center frequency of the scan
    int         repz       = 0;                  // repititions needed to scan the specified frequency range
    std::size_t vcnt       = 0UL;                // total data counter, incremented for each (frequency, power) pair acquired
    std::vector<float> pow_getter[loitering];    // holds power levels detected at fixed center frequency to assist in averaging
    int         timeout_ms = 0;                  // how long to wait for a scan before skipping it, in milli-seconds
#ifdef TIMEOUT_MS
    timeout_ms = TIMEOUT_MS;
#endif

    repz = ((2 * (fstop - fstart)) / this->_vars.spectrum.settings_type.span);    // determine total acquisitions and create overlap
    vcnt = repz * this->_vars.spectrum.settings_type.traceLength;

    // std::vectors are prepared for acquisition
    this->_vars.spectrum.trace_power_v[trace_number].resize(vcnt);  
    this->_vars.spectrum.trace_power_v[trace_number].clear();       
    this->_vars.spectrum.frequency_v.resize(vcnt);
    this->_vars.spectrum.frequency_v.clear();                                   
    for (int ii = 0; ii < loitering; ii++)
    {
        pow_getter[ii].clear();
        pow_getter[ii].resize(this->_vars.spectrum.settings_type.traceLength);
    }
    vcnt = 0UL;

    // acquire the data from the SPECTRUM group
    for (int xx = 0; xx < repz; xx++)
    {
        (void)this->device_stop();

        // center frequency is adjusted to make overlap, each adjustment automatically stops the device
        //cf = ((xx * this->_vars.spectrum.settings_type.span + this->_vars.spectrum.settings_type.span) / 2) + fstart;
        cf = fstart + (xx * (this->_vars.spectrum.settings_type.span / 2));
    
        this->vars.config.center_frequency_hz = cf;
        (void)this->_config_set_vars();
        this->vars.spectrum.is_enabled_measurement = true;    
        (void)this->_spectrum_set_vars();                     // insurance, also "gets"
        (void)this->device_run();

        // loitering a few times at each center frequency, when used with averaging, helps smooth the data
        for (int yy = 0; yy < loitering; yy++)
        {
            // request a trace, then use the wait time to complete preparation tasks
            (void)this->set_api_status(RSA_API::SPECTRUM_AcquireTrace());
            pow_getter[yy].clear();
            is_ready = false;
            data = NULL;

            #ifdef TIMEOUT_MS
                this->_api_status = RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready);
            #else
                while (is_ready == false)    // block until trace is ready
                {
                    this->_api_status = RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready);  // this could hang the program
                }
            #endif
            this->_report_api_status();
            if (is_ready == false) {continue;}    // if data was not acquired, then start the loop again

            try 
            {
                data = new float[this->_vars.spectrum.settings_type.traceLength];
            }
            catch(...)
            {
                return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
            }

            // API provides (frequency, power) for specified trace at selected center frequency
            this->_api_status = RSA_API::SPECTRUM_GetTrace
                (
                    this->_vars.spectrum.trace_select[trace_number], 
                    this->_vars.spectrum.settings_type.traceLength, 
                    data, 
                    &this->_vars.spectrum.trace_points_acquired[trace_number]
                );
            (void)this->_report_api_status();
            (void)this->_spectrum_copy_trace_points_acquired(trace_number);
            (void)this->_spectrum_get_trace_info_type(trace_number); 
            // bitcheck here, if needed

            // build trace at center frequency until "loitering" samples are collected for each (power, frequency) pair
            for (int zz = 0; zz < this->_vars.spectrum.trace_points_acquired[trace_number]; zz++)
            {
                pow_getter[yy][zz] = data[zz];
            }
            delete [] data;
            data = NULL;
        }
        
        // selected center frequency has "loitering" (frequency, power) pairs for the trace, find average and max
        maxp = -999999999.9;
        maxf = maxp;
        for (int rr = 0; rr < this->_vars.spectrum.trace_points_acquired[trace_number]; rr++)
        {
            p_avg = 0;
            for (int ss = 0; ss < loitering; ss++)
            {
                p_avg = p_avg + pow_getter[ss][rr];
            }
            p_avg = p_avg / loitering;

            this->_vars.spectrum.frequency_v[vcnt] = 
                this->_vars.spectrum.settings_type.actualStartFreq + this->_vars.spectrum.settings_type.actualFreqStepSize * rr;
            this->_vars.spectrum.trace_power_v[trace_number][vcnt] = p_avg;
            
            if(maxp < p_avg)
            {
                maxp = this->_vars.spectrum.trace_power_v[trace_number][vcnt];
                maxf = this->_vars.spectrum.frequency_v[vcnt];
            }
            vcnt++;
        }
        printf("points:  %9lu got %5d  ,  scan:  %5d of %5d >>> cf MHz=  %9.3lf  ,  span MHz=  %9.3lf  ,  " ,
            vcnt,
            this->_vars.spectrum.trace_points_acquired[trace_number],
            xx+1,
            repz,
            this->_vars.config.center_frequency_hz/1e6,
            this->_vars.spectrum.settings_type.span/1e6);
        printf("[ max MHz=  %9.3lf  ,  max dBm=  %9.3lf ]  ",
            maxf/1e6,
            maxp);
            if(maxp > threshold) // after aacquring and averaging, this is where you should further interogate the signal
            {
                printf("...THRESHOLD\n");    // good time to get IF and IQ data, a strong signal was identified
            } 
            else
            {
                printf("...noise\n");    // nothing in this spectrum band, move onto the next signal
            }
        this->vars.spectrum.is_enabled_measurement = false;
        (void)this->_spectrum_set_vars();
        (void)this->device_stop();
    }

    // all data was acquired and processed, write the CSV
    if (file_path_name[0] == '\0')
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%d__%lu_.%s",
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
            this->_vars.spectrum.frequency_v[idx],
            this->_vars.spectrum.trace_power_v[trace_number][idx]);
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
