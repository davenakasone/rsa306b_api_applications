/*
    API group "SPECTRUM"

    public :
        < 1 >  spectrum_find_peak_index()
        < 2 >  spectrum_make_frequency_v()
        < 3 >  spectrum_good_bitcheck()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    must use {0, 1, 2}
    guard if users abuse it
*/
CODEZ rsa306b_class::spectrum_find_peak_index
(
    int trace_number
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if 
    (
        (this->_vars.spectrum.trace_points_acquired[trace_number] > 0)  &&
        (this->_vars.spectrum.trace_power_v[static_cast<std::size_t>(trace_number)].size()  == 
            static_cast<std::size_t>(this->_vars.spectrum.trace_points_acquired[trace_number]))
    )
    {
        this->_vars.spectrum.peak_index[trace_number] = 0LU;
        for (int ii = 0; ii < this->_vars.spectrum.trace_points_acquired[trace_number]; ii++)
        {
            if 
            (
                this->_vars.spectrum.trace_power_v[static_cast<std::size_t>(trace_number)][static_cast<std::size_t>(ii)] >
                this->_vars.spectrum.trace_power_v[static_cast<std::size_t>(trace_number)][this->_vars.spectrum.peak_index[trace_number]]
            )
            {
                this->_vars.spectrum.peak_index[trace_number] = static_cast<std::size_t>(ii);
            }
        }
    }
    else
    {
        this->_vars.spectrum.peak_index[trace_number] = INIT_INT;
    }

    return this->_spectrum_copy_peak_index(trace_number);
}


////~~~~


/*
    < 2 > public
    need to have data in the std::vector before calling
*/
CODEZ rsa306b_class::spectrum_make_frequency_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    for (std::size_t ii = 0; ii < TRACES_306B; ii++)
    {
        if 
        (
            (this->_vars.spectrum.settings_type.traceLength != this->_vars.spectrum.trace_points_acquired[ii]) &&
            (this->_vars.spectrum.is_enabled_trace[ii] == true                                               )  
        )
        {
            #ifdef DEBUG_MIN
                (void)snprintf(X_ddts, sizeof(X_ddts), "bad trace length trace[%lu], expcted: %d, got: %d",
                    ii,
                    this->_vars.spectrum.settings_type.traceLength,
                    this->_vars.spectrum.trace_points_acquired[ii]);
                (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
        }
    }
#endif
    
    this->_vars.spectrum.frequency_v.clear();
    this->_vars.spectrum.frequency_v.resize(
        static_cast<std::size_t>(this->_vars.spectrum.settings_type.traceLength));

    for (int ii = 0; ii < this->_vars.spectrum.settings_type.traceLength; ii++)
    {
        this->_vars.spectrum.frequency_v[static_cast<std::size_t>(ii)] =
            this->_vars.spectrum.settings_type.actualStartFreq +
            this->_vars.spectrum.settings_type.actualFreqStepSize * ii;
    }

#ifdef SAFETY_CHECKS
    double temp = 
        this->_vars.spectrum.frequency_v.back() -
        this->vars.spectrum.settings_type.actualStopFreq;
    if ((temp > 1) || (temp < -1))
    {
        #ifdef DEBUG_CUSTOM
            (void)snprintf(X_ddts, sizeof(X_ddts), "mis-matched frequency array; actualStop:  %lf  ,  array:  %lf",
                this->vars.spectrum.settings_type.actualStopFreq,
                this->_vars.spectrum.frequency_v.back());
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CUSTOM_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
#endif

    return this->_spectrum_copy_frequency_v();
}


////~~~~


/*
    < 3 > public
    call after an acquitions
    give a valid trace number {0, 1, 2}
*/
bool rsa306b_class::spectrum_good_bitcheck
(
    int trace_number
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    CODEZ temp = 
    this->cutil.spectrum_acq_status
    (
        this->_vars.ifstream.data_info_type.acqStatus, 
        this->_vars.ifstream.valid_bitmask,
        this->_vars.ifstream.acq_status_messages
    );
    (void)this->_spectrum_copy_acq_status_messages();

    if (temp == CODEZ::_0_no_errors)
    {
        return true;
    }
    else
    {
        return false;
    }
}


////////~~~~~~~~END>  rsa306b_spectrum_helper.cpp
