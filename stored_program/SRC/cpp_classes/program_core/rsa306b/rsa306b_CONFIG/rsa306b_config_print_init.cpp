// /*
//     API group "CONFIG"

//     public :
//         < 1 >  print_config()
    
//     private :
//         < 1 >  _config_init()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > public
//     print "AUDIO" group variables to stdout
// */
// CODEZ rsa306b_class::print_config()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     (void)printf("\n'CONFIG' group >>>\n");
//     (void)printf("\treference level (dBm)              :  %lf\n", this->_vars.config.reference_level_dbm);
//     (void)printf("\tcenter frequency (Hz)              :  %lf\n", this->_vars.config.center_frequency_hz);
//     (void)printf("\tminimum center frequency (Hz)      :  %lf\n", this->_vars.config.min_center_frequency_hz);
//     (void)printf("\tmaximum center frequency (Hz)      :  %lf\n", this->_vars.config.max_center_frequency_hz);
//     (void)printf("\texternal reference frequency (Hz)  :  %lf\n", this->_vars.config.external_reference_frequency_hz);
//     (void)printf("\tfrequency reference source (Hz)    :  ");
//     switch (this->_vars.config.frequency_reference_source_select)
//     {
//         case (RSA_API::FRS_INTERNAL) : (void)printf("internal\n")     ; break;
//         case (RSA_API::FRS_EXTREF)   : (void)printf("external\n")     ; break;
//         case (RSA_API::FRS_GNSS)     : (void)printf("GNSS\n")         ; break;
//         case (RSA_API::FRS_USER)     : (void)printf("user-provided\n"); break;
//         default                      : (void)printf("unknown\n")      ; break;
//     }
// }


// ////~~~~


// /*
//     < 1 > private
//     initialize "CONFIG" group variables to known values
// */
// CODEZ rsa306b_class::_config_init()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     this->_vars.config.reference_level_dbm               = INIT_DOUBLE;   
//     this->_vars.config.center_frequency_hz               = INIT_DOUBLE; 
//     this->_vars.config.min_center_frequency_hz           = INIT_DOUBLE; 
//     this->_vars.config.max_center_frequency_hz           = INIT_DOUBLE; 
//     this->_vars.config.external_reference_frequency_hz   = INIT_DOUBLE;  
//     this->_vars.config.frequency_reference_source_select = RSA_API::FRS_USER;

//     this->_config_copy_vars();
// }


// ////////~~~~~~~~END>  rsa306b_config_print_init.cpp
    