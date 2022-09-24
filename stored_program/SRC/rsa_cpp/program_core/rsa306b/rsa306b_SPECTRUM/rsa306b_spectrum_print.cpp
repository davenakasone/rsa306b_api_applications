/*
    API group "SPECTRUM"  ...select compact or long

    public :
        < 1 >  print_spectrum()
    
    private :
        < 1 >  _print_spectrum_traces_long()
        < 2 >  _print_spectrum_traces_compact()
        
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    only printing first element for large items
*/
CODEZ rsa306b_class::spectrum_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'SPECTRUM' group >>>\n");
    (void)printf("\tmeasurement is enabled  :  %d\n", this->_vars.spectrum.is_enabled_measurement);
    (void)printf("\tfrequency_v.size()      :  %lu\n", this->_vars.spectrum.frequency_v.size());
    (void)printf("\t{LIMITS}\n");
    (void)printf("\t\tmaximum span                  :  %lf\n", this->_vars.spectrum.limits_type.maxSpan);
    (void)printf("\t\tminimum span                  :  %lf\n", this->_vars.spectrum.limits_type.minSpan);
    (void)printf("\t\tmaximum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.maxRBW);
    (void)printf("\t\tminimum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.minRBW);
    (void)printf("\t\tmaximum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.maxVBW);
    (void)printf("\t\tminimum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.minVBW);
    (void)printf("\t\tmaximum trace length          :  %d\n", this->_vars.spectrum.limits_type.maxTraceLength);
    (void)printf("\t\tminimum trace length          :  %d\n", this->_vars.spectrum.limits_type.minTraceLength);
    (void)printf("\t{ACTUAL SETTINGS}\n");
    (void)printf("\t\tactual number of IQ samples   :  %d\n", this->_vars.spectrum.settings_type.actualNumIQSamples);
    (void)printf("\t\tactual starting frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStartFreq);
    (void)printf("\t\tactual stopping frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStopFreq);
    (void)printf("\t\tactual frequency step size    :  %lf\n", this->_vars.spectrum.settings_type.actualFreqStepSize);
    (void)printf("\t\tactual resolution bandwidth   :  %lf\n", this->_vars.spectrum.settings_type.actualRBW);
    (void)printf("\t\tactual video bandwidth        :  %lf\n", this->_vars.spectrum.settings_type.actualVBW);
    (void)printf("\t{CONFIGURED SETTINGS}\n");
    (void)printf("\t\tvideo bandwidth enabled       :  %d\n", this->_vars.spectrum.settings_type.enableVBW);
    (void)printf("\t\tspan                          :  %lf\n", this->_vars.spectrum.settings_type.span);
    (void)printf("\t\tresolution bandwidth          :  %lf\n", this->_vars.spectrum.settings_type.rbw);
    (void)printf("\t\ttrace length                  :  %d\n", this->_vars.spectrum.settings_type.traceLength);
    (void)printf("\t\twindow                        :  ");
    switch (this->_vars.spectrum.settings_type.window)
    {
        case (RSA_API::SpectrumWindow_Kaiser)         : (void)printf("Kaiser\n");          break;
        case (RSA_API::SpectrumWindow_Mil6dB)         : (void)printf("Mil6dB\n");          break;
        case (RSA_API::SpectrumWindow_BlackmanHarris) : (void)printf("Blackman-Harris\n"); break;
        case (RSA_API::SpectrumWindow_Rectangle)      : (void)printf("Rectangle\n");       break;
        case (RSA_API::SpectrumWindow_FlatTop)        : (void)printf("Flat-top\n");        break;
        case (RSA_API::SpectrumWindow_Hann)           : (void)printf("Hann\n");            break;
        default                                       : (void)printf("UNKNOWN\n");         break;
    }
    printf("\t\tvertical units                :  ");
    switch (this->_vars.spectrum.settings_type.verticalUnit)
    {
        case (RSA_API::SpectrumVerticalUnit_dBm)  : (void)printf("dBm\n");    break;
        case (RSA_API::SpectrumVerticalUnit_Watt) : (void)printf("watt\n");   break;
        case (RSA_API::SpectrumVerticalUnit_Volt) : (void)printf("volt\n");   break;
        case (RSA_API::SpectrumVerticalUnit_Amp)  : (void)printf("amp\n");    break;
        case (RSA_API::SpectrumVerticalUnit_dBmV) : (void)printf("dBmV\n");   break;
        default                                   : (void)printf("UNKOWN\n"); break;
    }
    
    for (std::size_t ii = 0; ii < TRACES_306B; ii++)
    {
        (void)printf("\t{TRACE #%d}\n", this->_vars.spectrum.trace_select[ii]+1);
        (void)printf("\t\ttrace_power_v[%lu].size() :  %lu\n", ii, this->_vars.spectrum.trace_power_v[ii].size());
        (void)printf("\t\tpeak index                :  %lu\n", this->_vars.spectrum.peak_index[ii]);
        (void)printf("\t\tis enabled                :  %d\n", this->_vars.spectrum.is_enabled_trace[ii]);
        (void)printf("\t\ttrace points acquired     :  %d\n", this->_vars.spectrum.trace_points_acquired[ii]);
        (void)printf("\t\tacqDataStatus             :  0x%X\n", this->_vars.spectrum.trace_info_type->acqDataStatus);
        (void)printf("\t\ttimestamp                 :  %lu\n", this->_vars.spectrum.trace_info_type->timestamp);
        (void)printf("\t\tdetector                  :  ");
        switch (this->_vars.spectrum.detector_select[ii])
        {
            case (RSA_API::SpectrumDetector_PosPeak)     : (void)printf("positive peak\n");        break;
            case (RSA_API::SpectrumDetector_NegPeak)     : (void)printf("negative peak\n");        break;
            case (RSA_API::SpectrumDetector_AverageVRMS) : (void)printf("average voltage, RMS\n"); break;
            case (RSA_API::SpectrumDetector_Sample)      : (void)printf("sampled\n");              break;
            default                                      : (void)printf("UNKNOWN\n");              break;
        }
    }

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_spectrum_print.cpp
