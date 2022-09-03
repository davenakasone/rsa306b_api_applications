/*
    API group "xxx"

    public :
        < 1 >  spectrum_aquire()
        < 2 >  spectrum_find_peak_index()
        < 3 >  spectrum_write_csv()
    
    private :
        < 1 >  _spectrum_make_array_frequency()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::spectrum_aquire()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

    int timeout_ms = 100;
    bool is_ready = false;
    this->vars.spectrum.is_enabled_measurement = true;
    this->_spectrum_set_is_enabled_measurement();
    this->device_run();
    this->_vars.gp.api_status = RSA_API::SPECTRUM_AcquireTrace();
    this->_gp_confirm_api_status();

    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready);
    this->_gp_confirm_api_status();
    // while (is_ready == false)
    // {
    //     RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready);
    // }

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        if (this->_vars.spectrum.is_enabled_trace[ii] == true)
        {
            this->_vars.gp.api_status = 
                RSA_API::SPECTRUM_GetTrace(
                    this->_vars.spectrum.traces_select[ii], 
                    this->_vars.spectrum.settings_type.traceLength, 
                    this->_vars.spectrum.array_power[ii], 
                    &this->_vars.spectrum.trace_points_acquired[ii]);
            this->_gp_confirm_api_status();
            this->_spectrum_get_trace_info_type(ii);
            this->_spectrum_copy_array_power(ii);
        }
        else
        {
            this->_vars.spectrum.trace_points_acquired[ii] = 
                this->constants.INIT_INT;
        }
        this->_spectrum_copy_trace_points_aquired(ii);
    }
    this->vars.spectrum.is_enabled_measurement = false;
    this->_spectrum_set_is_enabled_measurement();
    this->device_stop();

    this->_spectrum_make_array_frequency();
}


////~~~~


/*
    < 2 > public
*/
void rsa306b_class::spectrum_find_peak_index()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }


    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        if (this->_vars.spectrum.trace_points_acquired[ii] != 
            this->constants.INIT_INT                  )
        {
            this->_vars.spectrum.peak_index[ii] = 0;
            for (int jj = 0; jj < this->_vars.spectrum.trace_points_acquired[ii]; jj++)
            {
                if (this->_vars.spectrum.array_power[ii][jj] >
                    this->_vars.spectrum.array_power[ii][this->_vars.spectrum.peak_index[ii]])
                {
                    this->_vars.spectrum.peak_index[ii] = jj;
                }
            }
        }
        else
        {
            this->_vars.spectrum.peak_index[ii] = this->constants.INIT_INT;
        }
        this->_spectrum_copy_peak_index(ii);
    }
}


////~~~~


/*
    < 3 > public
    does not nead a connected device, 
    just writes arrays to file as is
    might want to allow user to select a file-path-name and trace?
*/
void rsa306b_class::spectrum_write_csv()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_fptr_write != NULL)
    {
        fclose(this->_fptr_write);
    }    
    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        if (this->_vars.spectrum.trace_points_acquired[ii] != this->constants.INIT_INT &&
            this->_vars.spectrum.is_enabled_trace[ii] == true                           )
        {
            snprintf(this->_vars.gp.holder, BUF_F-1, "%s_%lu_freqVpow_trace_%d.csv",
                this->constants.DATA_DIRECTORY_PROCESSED,
                this->_vars.spectrum.trace_info_type[ii].timestamp,
                ii);
            this->_fptr_write = fopen(this->_vars.gp.holder, "w");
            if (this->_fptr_write == NULL)
            {
                #ifdef DEBUG_MIN
                    printf("\n\tinvalid output path for CSV\n");
                #endif
                return;
            }
            snprintf(this->_vars.gp.helper, BUF_B-1, "frequency,power\n");
            fputs(this->_vars.gp.helper, this->_fptr_write);
            for (int jj = 0; jj < this->_vars.spectrum.trace_points_acquired[ii]; jj++)
            {
                if (jj == this->_vars.spectrum.trace_points_acquired[ii])
                {
                    snprintf(this->_vars.gp.helper, BUF_E-1, "%lf,%f",
                        this->_vars.spectrum.array_frequency[jj],
                        this->_vars.spectrum.array_power[ii][jj]);
                }
                else
                {
                    snprintf(this->_vars.gp.helper, BUF_E-1, "%lf,%f\n",
                        this->_vars.spectrum.array_frequency[jj],
                        this->_vars.spectrum.array_power[ii][jj]);
                }
                fputs(this->_vars.gp.helper, this->_fptr_write);
            }
            fclose(this->_fptr_write);
            this->_fptr_write = NULL;
            #ifdef DEBUG_MAX
                printf("\n\t%s()  ,  file ready:  %s\n", 
                    __func__, this->_vars.gp.holder);
            #endif
        }
    }
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_spectrum_make_array_frequency()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

    this->_spectrum_get_settings_type();
    for (int ii = 0; ii < this->_vars.spectrum.settings_type.traceLength; ii++)
    {
        this->_vars.spectrum.array_frequency[ii] =
            this->_vars.spectrum.settings_type.actualStartFreq +
            this->_vars.spectrum.settings_type.actualFreqStepSize * ii;
    }
    #ifdef DEBUG_MIN
        double temp = this->_vars.spectrum.array_frequency
                        [this->_vars.spectrum.settings_type.traceLength-1] -
                        this->vars.spectrum.settings_type.actualStopFreq;
        if ((temp > 1) || (temp < -1))
        {
            printf("\n\tmismatched frequency array:  %lf\n", temp);
        }
    #endif
    this->_spectrum_copy_array_frequency();
}


////////~~~~~~~~END>  rsa306b_spectrum_user.cpp
