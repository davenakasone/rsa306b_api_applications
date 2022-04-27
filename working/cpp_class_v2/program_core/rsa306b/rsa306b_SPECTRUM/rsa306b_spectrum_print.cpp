/*
    API group "SPECTRUM"

    public :
        < 1 >  print_spectrum()
    
    private :
        #  none
        
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    only printing first element for large items
*/
void rsa306b_class::print_spectrum()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'SPECTRUM' group >>>\n");
    printf("\t{LIMITS}\n");
    printf("\t\tmaximum span                  :  %lf\n", this->_vars.spectrum.limits_type.maxSpan);
    printf("\t\tminimum span                  :  %lf\n", this->_vars.spectrum.limits_type.minSpan);
    printf("\t\tmaximum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.maxRBW);
    printf("\t\tminimum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.minRBW);
    printf("\t\tmaximum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.maxVBW);
    printf("\t\tminimum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.minVBW);
    printf("\t\tmaximum trace length          :  %d\n", this->_vars.spectrum.limits_type.maxTraceLength);
    printf("\t\tminimum trace length          :  %d\n", this->_vars.spectrum.limits_type.minTraceLength);
    printf("\t{ACTUAL SETTINGS}\n");
    printf("\t\tactual number of IQ samples   :  %d\n", this->_vars.spectrum.settings_type.actualNumIQSamples);
    printf("\t\tactual starting frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStartFreq);
    printf("\t\tactual stopping frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStopFreq);
    printf("\t\tactual frequency step size    :  %lf\n", this->_vars.spectrum.settings_type.actualFreqStepSize);
    printf("\t\tactual resolution bandwidth   :  %lf\n", this->_vars.spectrum.settings_type.actualRBW);
    printf("\t\tactual video bandwidth        :  %lf\n", this->_vars.spectrum.settings_type.actualVBW);
    printf("\t{CONFIGURED SETTINGS}\n");
    printf("\t\ttrace points acquired         :  %d\n", this->_vars.spectrum.trace_points_acquired);
    printf("\t\tmeasurement is enabled        :  %d\n", this->_vars.spectrum.is_enabled_measurement);
    printf("\t\tvideo bandwidth enabled       :  %d\n", this->_vars.spectrum.settings_type.enableVBW);
    printf("\t\tspan                          :  %lf\n", this->_vars.spectrum.settings_type.span);
    printf("\t\tresolution bandwidth          :  %lf\n", this->_vars.spectrum.settings_type.rbw);
    printf("\t\ttrace length                  :  %d\n", this->_vars.spectrum.settings_type.traceLength);
    printf("\t\twindow                        :  ");
    switch (this->_vars.spectrum.settings_type.window)
    {
        case (RSA_API::SpectrumWindow_Kaiser)         : printf("Kaiser\n");          break;
        case (RSA_API::SpectrumWindow_Mil6dB)         : printf("Mil6dB\n");          break;
        case (RSA_API::SpectrumWindow_BlackmanHarris) : printf("Blackman-Harris\n"); break;
        case (RSA_API::SpectrumWindow_Rectangle)      : printf("Rectangle\n");       break;
        case (RSA_API::SpectrumWindow_FlatTop)        : printf("Flat-top\n");        break;
        case (RSA_API::SpectrumWindow_Hann)           : printf("Hann\n");            break;
        default                                       : printf("UNKNOWN\n");         break;
    }
    printf("\t\tvertical units                :  ");
    switch (this->_vars.spectrum.settings_type.verticalUnit)
    {
        case (RSA_API::SpectrumVerticalUnit_dBm)  : printf("dBm\n");    break;
        case (RSA_API::SpectrumVerticalUnit_Watt) : printf("watt\n");   break;
        case (RSA_API::SpectrumVerticalUnit_Volt) : printf("volt\n");   break;
        case (RSA_API::SpectrumVerticalUnit_Amp)  : printf("amp\n");    break;
        case (RSA_API::SpectrumVerticalUnit_dBmV) : printf("dBmV\n");   break;
        default                                   : printf("UNKOWN\n"); break;
    }

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        printf("\t{trace #%d}\n", ii+1);
        printf("\t\tspectrum trace index          :  %d\n", this->_vars.spectrum.traces_select[ii]);
        printf("\t\tspectrum trace name           :  ");
        switch (this->_vars.spectrum.traces_select[ii])
        {
            case (RSA_API::SpectrumTrace1) : printf("SpectrumTrace1\n"); break;
            case (RSA_API::SpectrumTrace2) : printf("SpectrumTrace2\n"); break;
            case (RSA_API::SpectrumTrace3) : printf("SpectrumTrace3\n"); break;
            default                        : printf("UNKNOWN\n");        break;
        }
        printf("\t\ttrace is enabled              :  %d\n", this->_vars.spectrum.is_enabled_trace[ii]);
        printf("\t\tpeak index measured           :  %d\n", this->_vars.spectrum.peak_index[ii]);
        printf("\t\tdata_frequency[0]             :  %lf\n", this->_vars.spectrum.array_frequency[0]);
        printf("\t\tdata_power[0]                 :  %f\n", this->_vars.spectrum.array_power[ii][0]);
        printf("\t\tdetection used                :  ");
        
        switch (this->_vars.spectrum.detectors_select[ii])
        {
            case (RSA_API::SpectrumDetector_PosPeak)     : printf("positive peak\n");        break;
            case (RSA_API::SpectrumDetector_NegPeak)     : printf("negative peak\n");        break;
            case (RSA_API::SpectrumDetector_AverageVRMS) : printf("average voltage, RMS\n"); break;
            case (RSA_API::SpectrumDetector_Sample)      : printf("sampled\n");              break;
            default                                      : printf("UNKNOWN\n");              break;
        }
        this->_vars.gp.acquisition_code = this->_vars.spectrum.trace_info_type->acqDataStatus;
        this->_gp_confirm_aquisition_code();
        printf("\t\taquisition status             :  %u\n", this->_vars.spectrum.trace_info_type->acqDataStatus);
        printf("\t\taquisition status message     :  %s\n", this->_vars.gp.acquisition_message);
        printf("\t\taquisition timestamp          :  %ld\n", this->_vars.spectrum.trace_info_type->timestamp);
        
    }
}


////////~~~~~~~~END>  rsa306b_spectrum_print.cpp
