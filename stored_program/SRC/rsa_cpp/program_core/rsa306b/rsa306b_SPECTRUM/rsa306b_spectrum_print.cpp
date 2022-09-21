// /*
//     API group "SPECTRUM"  ...select compact or long

//     public :
//         < 1 >  print_spectrum()
    
//     private :
//         < 1 >  _print_spectrum_traces_long()
//         < 2 >  _print_spectrum_traces_compact()
        
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > private
//     only printing first element for large items
// */
// CODEZ rsa306b_class::print_spectrum()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     (void)printf("\n'SPECTRUM' group >>>\n");
//     (void)printf("\t{LIMITS}\n");
//     (void)printf("\t\tmaximum span                  :  %lf\n", this->_vars.spectrum.limits_type.maxSpan);
//     (void)printf("\t\tminimum span                  :  %lf\n", this->_vars.spectrum.limits_type.minSpan);
//     (void)printf("\t\tmaximum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.maxRBW);
//     (void)printf("\t\tminimum resolution bandwidth  :  %lf\n", this->_vars.spectrum.limits_type.minRBW);
//     (void)printf("\t\tmaximum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.maxVBW);
//     (void)printf("\t\tminimum video bandwidth       :  %lf\n", this->_vars.spectrum.limits_type.minVBW);
//     (void)printf("\t\tmaximum trace length          :  %d\n", this->_vars.spectrum.limits_type.maxTraceLength);
//     (void)printf("\t\tminimum trace length          :  %d\n", this->_vars.spectrum.limits_type.minTraceLength);
//     (void)printf("\t{ACTUAL SETTINGS}\n");
//     (void)printf("\t\tactual number of IQ samples   :  %d\n", this->_vars.spectrum.settings_type.actualNumIQSamples);
//     (void)printf("\t\tactual starting frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStartFreq);
//     (void)printf("\t\tactual stopping frequency     :  %lf\n", this->_vars.spectrum.settings_type.actualStopFreq);
//     (void)printf("\t\tactual frequency step size    :  %lf\n", this->_vars.spectrum.settings_type.actualFreqStepSize);
//     (void)printf("\t\tactual resolution bandwidth   :  %lf\n", this->_vars.spectrum.settings_type.actualRBW);
//     (void)printf("\t\tactual video bandwidth        :  %lf\n", this->_vars.spectrum.settings_type.actualVBW);
//     (void)printf("\t{CONFIGURED SETTINGS}\n");
//     (void)printf("\t\tmeasurement is enabled        :  %d\n", this->_vars.spectrum.is_enabled_measurement);
//     (void)printf("\t\tvideo bandwidth enabled       :  %d\n", this->_vars.spectrum.settings_type.enableVBW);
//     (void)printf("\t\tspan                          :  %lf\n", this->_vars.spectrum.settings_type.span);
//     (void)printf("\t\tresolution bandwidth          :  %lf\n", this->_vars.spectrum.settings_type.rbw);
//     (void)printf("\t\ttrace length                  :  %d\n", this->_vars.spectrum.settings_type.traceLength);
//     (void)printf("\t\twindow                        :  ");
//     switch (this->_vars.spectrum.settings_type.window)
//     {
//         case (RSA_API::SpectrumWindow_Kaiser)         : (void)printf("Kaiser\n");          break;
//         case (RSA_API::SpectrumWindow_Mil6dB)         : (void)printf("Mil6dB\n");          break;
//         case (RSA_API::SpectrumWindow_BlackmanHarris) : (void)printf("Blackman-Harris\n"); break;
//         case (RSA_API::SpectrumWindow_Rectangle)      : (void)printf("Rectangle\n");       break;
//         case (RSA_API::SpectrumWindow_FlatTop)        : (void)printf("Flat-top\n");        break;
//         case (RSA_API::SpectrumWindow_Hann)           : (void)printf("Hann\n");            break;
//         default                                       : (void)printf("UNKNOWN\n");         break;
//     }
//     printf("\t\tvertical units                :  ");
//     switch (this->_vars.spectrum.settings_type.verticalUnit)
//     {
//         case (RSA_API::SpectrumVerticalUnit_dBm)  : (void)printf("dBm\n");    break;
//         case (RSA_API::SpectrumVerticalUnit_Watt) : (void)printf("watt\n");   break;
//         case (RSA_API::SpectrumVerticalUnit_Volt) : (void)printf("volt\n");   break;
//         case (RSA_API::SpectrumVerticalUnit_Amp)  : (void)printf("amp\n");    break;
//         case (RSA_API::SpectrumVerticalUnit_dBmV) : (void)printf("dBmV\n");   break;
//         default                                   : (void)printf("UNKOWN\n"); break;
//     }
    
//     // pick one
//     this->_print_spectrum_traces_compact();
//     //this->_print_spectrum_traces_long();
// }


// ////~~~~


// /*
//     < 1 > 
// */
// CODEZ rsa306b_class::_print_spectrum_traces_long()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         (void)printf("\t{TRACE #%d}\n", ii+1);
//         (void)printf("\t\tspectrum trace index          :  %d\n", this->_vars.spectrum.traces_select[ii]);
//         (void)printf("\t\tspectrum trace name           :  ");
//         switch (this->_vars.spectrum.traces_select[ii])
//         {
//             case (RSA_API::SpectrumTrace1) : printf("SpectrumTrace1\n"); break;
//             case (RSA_API::SpectrumTrace2) : printf("SpectrumTrace2\n"); break;
//             case (RSA_API::SpectrumTrace3) : printf("SpectrumTrace3\n"); break;
//             default                        : printf("UNKNOWN\n");        break;
//         }
//         (void)printf("\t\ttrace is enabled              :  %d\n", this->_vars.spectrum.is_enabled_trace[ii]);
//         (void)printf("\t\ttrace points acquired         :  %d\n", this->_vars.spectrum.trace_points_acquired[ii]);
//         (void)printf("\t\tpeak index measured           :  %d\n", this->_vars.spectrum.peak_index[ii]);
//         (void)printf("\t\tdata_frequency[0]             :  %lf\n", this->_vars.spectrum.array_frequency[0]);
//         (void)printf("\t\tdata_power[0]                 :  %f\n", this->_vars.spectrum.array_power[ii][0]);
//         (void)printf("\t\tdetection used                :  ");
        
//         switch (this->_vars.spectrum.detectors_select[ii])
//         {
//             case (RSA_API::SpectrumDetector_PosPeak)     : (void)printf("positive peak\n");        break;
//             case (RSA_API::SpectrumDetector_NegPeak)     : (void)printf("negative peak\n");        break;
//             case (RSA_API::SpectrumDetector_AverageVRMS) : (void)printf("average voltage, RMS\n"); break;
//             case (RSA_API::SpectrumDetector_Sample)      : (void)printf("sampled\n");              break;
//             default                                      : (void)printf("UNKNOWN\n");              break;
//         }
//         this->_vars.gp.acquisition_code = this->_vars.spectrum.trace_info_type[ii].acqDataStatus;
//         this->_gp_confirm_aquisition_code();
//         (void)printf("\t\taquisition status             :  %u { 0x%X }\n", 
//             this->_vars.spectrum.trace_info_type[ii].acqDataStatus, 
//             this->_vars.spectrum.trace_info_type[ii].acqDataStatus);
//         (void)printf("\t\taquisition status message     :  %s\n", this->_vars.gp.acquisition_message);
//         (void)printf("\t\taquisition timestamp          :  %ld\n", this->_vars.spectrum.trace_info_type[ii].timestamp); 
//     }
// }


// ////~~~~


// /*
//     < 2 > 
// */
// CODEZ rsa306b_class::_print_spectrum_traces_compact()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     (void)printf("\t{ TRACE # ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii < TRACES_AVAILABLE - 1)
//         {
//             (void)printf("%d , ", ii+1);
//         }
//         else
//         {
//             (void)printf("%d }\n", ii+1);
//         }
        
//     }
//     (void)printf("\t\tspectrum trace index          :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15d", this->_vars.spectrum.traces_select[ii]);
//             (void)printf("       <> ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15d", this->_vars.spectrum.traces_select[ii]);
//             (void)printf("         <> ");
//         }
//         else
//         {
//             (void)printf("%15d\n", this->_vars.spectrum.traces_select[ii]);
//         }
//     }
//     (void)printf("\t\tspectrum trace name           :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii < TRACES_AVAILABLE - 1)
//         {
//             switch (this->_vars.spectrum.traces_select[ii])
//             {
//                 case (RSA_API::SpectrumTrace1) : printf("SpectrumTrace1        <>  "); break;
//                 case (RSA_API::SpectrumTrace2) : printf("SpectrumTrace2         <>  "); break;
//                 case (RSA_API::SpectrumTrace3) : printf("SpectrumTrace3        <>  "); break;
//                 default                        : printf("UNKNOWN               <>  "); break;
//             }
//         }
//         else
//         {
//             switch (this->_vars.spectrum.traces_select[ii])
//             {
//                 case (RSA_API::SpectrumTrace1) : printf("SpectrumTrace1\n"); break;
//                 case (RSA_API::SpectrumTrace2) : printf("SpectrumTrace2\n"); break;
//                 case (RSA_API::SpectrumTrace3) : printf("SpectrumTrace3\n"); break;
//                 default                        : printf("UNKNOWN\n"); break;
//             }
//         }
//     }
//     (void)printf("\t\ttrace is enabled              :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15d", this->_vars.spectrum.is_enabled_trace[ii]);
//             (void)printf("       <> ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15d", this->_vars.spectrum.is_enabled_trace[ii]);
//             (void)printf("         <> ");
//         }
//         else
//         {
//             (void)printf("%15d\n", this->_vars.spectrum.is_enabled_trace[ii]);
//         }
//     }
//     (void)printf("\t\ttrace points acquired         :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15d", this->_vars.spectrum.trace_points_acquired[ii]);
//             (void)printf("       <> ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15d", this->_vars.spectrum.trace_points_acquired[ii]);
//             (void)printf("         <> ");
//         }
//         else
//         {
//             printf("%15d\n", this->_vars.spectrum.trace_points_acquired[ii]);
//         }
//     }
//     (void)printf("\t\tpeak index measured           :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15d", this->_vars.spectrum.peak_index[ii]);
//             (void)printf("       <> ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15d", this->_vars.spectrum.peak_index[ii]);
//             (void)printf("         <> ");
//         }
//         else
//         {
//             (void)printf("%15d\n", this->_vars.spectrum.peak_index[ii]);
//         }
//     }
//     (void)printf("\t\tdata_frequency[0]             :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15.3lf", this->_vars.spectrum.array_frequency[0]);
//             (void)printf("       <> ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15.3lf", this->_vars.spectrum.array_frequency[0]);
//             (void)printf("         <> ");
//         }
//         else
//         {
//             (void)printf("%15.3lf\n", this->_vars.spectrum.array_frequency[0]);
//         }
//     }
//     (void)printf("\t\tdata_power[0]                 :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15.3f", this->_vars.spectrum.array_power[ii][0]);
//             (void)printf("       <>");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15.3f", this->_vars.spectrum.array_power[ii][0]);
//             (void)printf("          <> ");
//         }
//         else
//         {
//             (void)printf("%15.3f\n", this->_vars.spectrum.array_power[ii][0]);
//         }
//     }
//     (void)printf("\t\tdetection used                :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii < TRACES_AVAILABLE - 1)
//         {
//             switch (this->_vars.spectrum.detectors_select[ii])
//             {
//                 case (RSA_API::SpectrumDetector_PosPeak)     : (void)printf("positive peak         <>   "); break;
//                 case (RSA_API::SpectrumDetector_NegPeak)     : (void)printf("negative peak         <>   "); break;
//                 case (RSA_API::SpectrumDetector_AverageVRMS) : (void)printf("average voltage RMS   <>   "); break;
//                 case (RSA_API::SpectrumDetector_Sample)      : (void)printf("sampled               <>   "); break;
//                 default                                      : (void)printf("UNKNOWN               <>   "); break;
//             }
//         }
//         else
//         {
//             switch (this->_vars.spectrum.detectors_select[ii])
//             {
//                 case (RSA_API::SpectrumDetector_PosPeak)     : (void)printf("positive peak\n");       break;
//                 case (RSA_API::SpectrumDetector_NegPeak)     : (void)printf("negative peak\n");       break;
//                 case (RSA_API::SpectrumDetector_AverageVRMS) : (void)printf("average voltage RMS\n"); break;
//                 case (RSA_API::SpectrumDetector_Sample)      : (void)printf("sampled\n");             break;
//                 default                                      : (void)printf("UNKNOWN\n");             break;
//             }
//         }
//     }
//     (void)printf("\t\taquisition status             :  "); 
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         this->_vars.gp.acquisition_code = this->_vars.spectrum.trace_info_type[ii].acqDataStatus;
//         this->_gp_confirm_aquisition_code();
//         if (ii == 0)
//         {
//             (void)printf("%5u { 0x%4X }", 
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus,
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus);
//             (void)printf("      <>  ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%5u { 0x%4X }", 
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus,
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus);
//             (void)printf("       <> ");
//         }
//         else
//         {
//             (void)printf("%5u { 0x%4X }\n", 
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus,
//                 this->_vars.spectrum.trace_info_type[ii].acqDataStatus);
//         }
//     }
//     (void)printf("\t\taquisition status message     :  ");
//     char temp[10]; // first 10-1 chars....
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         this->_vars.gp.acquisition_code = this->_vars.spectrum.trace_info_type[ii].acqDataStatus;
//         this->_gp_confirm_aquisition_code();
//         (void)strncpy(temp, this->_vars.gp.acquisition_message, 10-1);
//         if (ii == 0)
//         {
//             (void)printf("%s", temp);
//             (void)printf("             <>        ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%s", temp);
//             (void)printf("        <>        ");
//         }
//         else
//         {
//             (void)printf("%s\n", temp);
//         }
//     }  
//     (void)printf("\t\taquisition timestamp          :  ");
//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         if (ii == 0)
//         {
//             (void)printf("%15ld", this->_vars.spectrum.trace_info_type[ii].timestamp);
//             (void)printf("       <>   ");
//         }
//         else if (ii == 1)
//         {
//             (void)printf("%15ld", this->_vars.spectrum.trace_info_type[ii].timestamp);
//             (void)printf("       <>    ");
//         }
//         else
//         {
//             (void)printf("%15ld\n", this->_vars.spectrum.trace_info_type[ii].timestamp);
//         }
//     }
// }

// ////////~~~~~~~~END>  rsa306b_spectrum_print.cpp
