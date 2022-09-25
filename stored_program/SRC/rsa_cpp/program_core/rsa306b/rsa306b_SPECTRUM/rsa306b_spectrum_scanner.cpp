/*
    API group "SPECTRUM"

    public :
        < 1 >  spectrum_scanner()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    settings should already be made, device is running
*/
CODEZ rsa306b_class::spectrum_scanner
(
    int trace_number,
    double fstart, 
    double fstop, 
    double threshold, 
    int loitering,
    char* file_path_name,
    double reflevel,
    double rbw,
    double span,
    int tlen
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    this->device_stop();
    
    this->vars.config.reference_level_dbm = reflevel;
    this->_config_set_vars();

    this->vars.spectrum.settings_type.rbw = rbw;
    this->vars.spectrum.settings_type.span = span;
    this->vars.spectrum.settings_type.traceLength = tlen;
    (void)this->_spectrum_set_vars();

    
    float maxp = -999999999.9;
    double maxf = maxp;
    double cf = 0;
    int repz = ((fstop - fstart) / this->_vars.spectrum.settings_type.span);
    //std::size_t dlen = (repz + 1) * this->_vars.spectrum.settings_type.traceLength;
    //this->_vars.spectrum.trace_power_v[trace_number].resize(dlen);
    //this->_vars.spectrum.frequency_v.resize(dlen);
    this->_vars.spectrum.trace_power_v[trace_number].clear();
    this->_vars.spectrum.frequency_v.clear();
    std::size_t vcnt = 0UL;
printf("\n%lu  %lu   %d\n", this->_vars.spectrum.trace_power_v[trace_number].size(), this->_vars.spectrum.frequency_v.size(), repz);
    for (int xx = 0; xx < repz; xx++)
    {
        cf = xx * this->_vars.spectrum.settings_type.span + this->_vars.spectrum.settings_type.span + fstart;
        this->vars.config.center_frequency_hz = cf;
        this->_config_set_vars();
        this->vars.spectrum.is_enabled_measurement = true;
        (void)this->_spectrum_set_vars();
        (void)this->device_run();

        for (int yy = 0; yy < loitering; yy++)
        {
            (void)this->set_api_status(RSA_API::SPECTRUM_AcquireTrace());
            float* data    = NULL;
            bool is_ready  = false;
            int timeout_ms = 1;

            data = new float[this->_vars.spectrum.settings_type.traceLength]; 
            while (is_ready == false)
            {
                (void)RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready); 
            }

            this->_api_status = RSA_API::SPECTRUM_GetTrace
                (
                    this->_vars.spectrum.trace_select[trace_number], 
                    this->_vars.spectrum.settings_type.traceLength, 
                    data, 
                    &this->_vars.spectrum.trace_points_acquired[trace_number]
                );
            (void)this->_report_api_status();
            (void)this->_spectrum_get_trace_info_type(trace_number); 

            maxp = -999999999.9;
            maxf = maxp;
            for (int kk = 0; kk < this->_vars.spectrum.trace_points_acquired[trace_number]; kk++)
            {
                // this->_vars.spectrum.frequency_v[vcnt] = 
                //     this->_vars.spectrum.settings_type.actualStartFreq +
                //     this->_vars.spectrum.settings_type.actualFreqStepSize * kk;

                // this->_vars.spectrum.trace_power_v[trace_number][vcnt] = data[kk]; 
                this->_vars.spectrum.trace_power_v[trace_number].push_back(data[kk]);
                this->_vars.spectrum.frequency_v.push_back(
                    this->_vars.spectrum.settings_type.actualStartFreq +
                    this->_vars.spectrum.settings_type.actualFreqStepSize * kk);
                if(maxp < data[kk])
                {
                    maxp = this->_vars.spectrum.trace_power_v[trace_number][vcnt];
                    maxf = this->_vars.spectrum.frequency_v[vcnt];
                }
                vcnt++;
            }
            delete [] data;
            data = NULL;
            printf("%12lu  ,  %5d of %5d ,  %5d  ,  %5d  )  maxMHz=  %15.3lf  ,  maxdBm=  %15.3lf",
                vcnt,
                xx,
                repz,
                yy,
                this->_vars.spectrum.trace_points_acquired[trace_number],
                maxf/1e6,
                maxp);
            if(maxp > threshold) // this is where to process
            {
                printf("   THRESHOLD exceeded\n");
            } 
            else
            {
                printf("  ...just noise\n");
            }
        }
        this->vars.spectrum.is_enabled_measurement = false;
        (void)this->_spectrum_set_vars();
    }

    if (file_path_name[0] == '\0')
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%d__%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            SPECTRUM_FILE_NAME_BASE,
            trace_number,
            this->_vars.reftime.current.timestamp,
            DATA_OUTPUT_EXTENSTION);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    this->_fp_write = fopen(this->_helper, "w");
    if (this->_fp_write == NULL) { return CODEZ::_13_fopen_failed;}

    (void)sprintf(this->_helper, "%s,%s\n",
        SPECTRUM_FIELD_1,
        SPECTRUM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < vcnt; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.5lf,%0.5f\n",
            this->_vars.spectrum.frequency_v[idx],
            this->_vars.spectrum.trace_power_v[trace_number][idx]);
        (void)fputs(this->_helper, this->_fp_write);
    }

    fclose(this->_fp_write); 
    this->_fp_write = NULL;
    this->device_stop();
    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  rsa306b_spectrum_scanner.cpp
