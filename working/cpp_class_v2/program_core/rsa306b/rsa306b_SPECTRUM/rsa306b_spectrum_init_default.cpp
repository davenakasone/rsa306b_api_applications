/*
    API group "SPECTRUM", initializing

    public :
        < 1 >  spectrum_default()
    
    private :
        < 1 >  _spectrum_default()
        < 2 >  _spectrum_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::spectrum_default()
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
    this->_spectrum_default();
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_spectrum_default()
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
    this->device_stop();
    this->_vars.gp.api_status = RSA_API::SPECTRUM_SetDefault();
    this->_gp_confirm_api_status();
    this->_spectrum_get_vars();
}


////~~~~


/*
    < 2 > private
    don't need to touch "trace_info_type" or "limits_type"
*/
void rsa306b_class::_spectrum_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    // the traces have to be assigned, they match the enum and never change
    this->_vars.spectrum.traces_select[0] = RSA_API::SpectrumTrace1;
    this->_vars.spectrum.traces_select[1] = RSA_API::SpectrumTrace2;
    this->_vars.spectrum.traces_select[2] = RSA_API::SpectrumTrace3;

    // everything else is as usual
    this->_vars.spectrum.is_enabled_measurement = false;

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->_vars.spectrum.is_enabled_trace[ii] = false;
        this->_vars.spectrum.trace_points_acquired[ii] = this->constants.INIT_INT;
        this->_vars.spectrum.peak_index[ii] = this->constants.INIT_INT;
        this->_vars.spectrum.detectors_select[ii] = RSA_API::SpectrumDetector_AverageVRMS;
        for(int jj = 0; jj < SPECTRUM_DATA_LENGTH; jj++)
        {
            if (ii == 0) 
            {
                this->_vars.spectrum.array_frequency[jj] = this->constants.INIT_DOUBLE;
            }
            this->_vars.spectrum.array_power[ii][jj] = this->constants.INIT_FLOAT;
        }
    }

    this->_vars.spectrum.settings_type.span = this->constants.INIT_DOUBLE;
    this->_vars.spectrum.settings_type.rbw = this->constants.INIT_DOUBLE;
    this->_vars.spectrum.settings_type.enableVBW = false;
    this->_vars.spectrum.settings_type.traceLength = this->constants.INIT_INT;
    this->_vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_FlatTop;
    this->_vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_Amp;

    this->_spectrum_copy_vars();
}


////////~~~~~~~~END>  rsa306b_spectrum_init_default.cpp
