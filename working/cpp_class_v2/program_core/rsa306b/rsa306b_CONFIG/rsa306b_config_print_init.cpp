/*
    API group "CONFIG"

    public :
        < 1 >  print_config()
    
    private :
        < 1 >  _config_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    print "AUDIO" group variables to stdout
*/
void rsa306b_class::print_config()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'CONFIG' group >>>\n");
    printf("\treference level (dBm)              :  %lf\n", this->_vars.config.reference_level_dbm);
    printf("\tcenter frequency (Hz)              :  %lf\n", this->_vars.config.center_frequency_hz);
    printf("\tminimum center frequency (Hz)      :  %lf\n", this->_vars.config.min_center_frequency_hz);
    printf("\tmaximum center frequency (Hz)      :  %lf\n", this->_vars.config.max_center_frequency_hz);
    printf("\texternal reference frequency (Hz)  :  %lf\n", this->_vars.config.external_reference_frequency_hz);
    printf("\tfrequency reference source (Hz)    :  ");
    switch (this->_vars.config.frequency_reference_source_select)
    {
        case (RSA_API::FRS_INTERNAL) :
            printf("internal\n");
            break;
        case (RSA_API::FRS_EXTREF) :
            printf("external\n");
            break;
        case (RSA_API::FRS_GNSS) :
            printf("GNSS\n");
            break;
        case (RSA_API::FRS_USER) :
            printf("user-provided\n");
        default :
            printf("unknown\n");
    }
}


////~~~~


/*
    < 1 > private
    initialize "CONFIG" group variables to known values
*/
void rsa306b_class::_config_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_vars.config.reference_level_dbm = this->constants.INIT_DOUBLE;   
    this->_vars.config.center_frequency_hz = this->constants.INIT_DOUBLE; 
    this->_vars.config.min_center_frequency_hz = this->constants.INIT_DOUBLE; 
    this->_vars.config.max_center_frequency_hz= this->constants.INIT_DOUBLE; 
    this->_vars.config.external_reference_frequency_hz = this->constants.INIT_DOUBLE;  

    this->_vars.config.frequency_reference_source_select = RSA_API::FRS_USER;

    this->_config_copy_vars();
}


////////~~~~~~~~END>  rsa306b_config_print_init.cpp
    