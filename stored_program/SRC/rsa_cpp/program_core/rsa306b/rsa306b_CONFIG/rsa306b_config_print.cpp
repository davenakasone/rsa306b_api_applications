/*
    API group "CONFIG"

    public :
        < 1 >  config_print()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    print "CONFIG" group variables to stdout
*/
CODEZ rsa306b_class::config_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'CONFIG' group >>>\n");
    (void)printf("\treference level (dBm)              :  %lf\n", this->_vars.config.reference_level_dbm);
    (void)printf("\tcenter frequency (Hz)              :  %lf\n", this->_vars.config.center_frequency_hz);
    (void)printf("\tminimum center frequency (Hz)      :  %lf\n", this->_vars.config.min_center_frequency_hz);
    (void)printf("\tmaximum center frequency (Hz)      :  %lf\n", this->_vars.config.max_center_frequency_hz);
    (void)printf("\texternal reference frequency (Hz)  :  %lf\n", this->_vars.config.external_reference_frequency_hz);
    (void)printf("\tfrequency reference source (Hz)    :  ");
    switch (this->_vars.config.frequency_reference_source_select)
    {
        case (RSA_API::FRS_INTERNAL) : (void)printf("internal\n")     ; break;
        case (RSA_API::FRS_EXTREF)   : (void)printf("external\n")     ; break;
        case (RSA_API::FRS_GNSS)     : (void)printf("GNSS\n")         ; break;
        case (RSA_API::FRS_USER)     : (void)printf("user-provided\n"); break;
        default                      : (void)printf("unknown\n")      ; break;
    }
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_config_print.cpp
       