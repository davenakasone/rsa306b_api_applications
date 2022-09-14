/*
    API group "REFTIME"

    public :
        < 1 >  print_reftime()
    
    private :
        < 1 >  _init_reftime()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::print_reftime()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    printf("\n'REFTIME' group >>>\n");
    printf("\tcurrent time (nano)         :  %lu\n", this->_vars.reftime.current.nanos);
    printf("\tcurrent time (seconds)      :  %lu\n", this->_vars.reftime.current.seconds);
    printf("\tcurrent time (timestamp)    :  %lu\n", this->_vars.reftime.current.timestamp);
    printf("\tstart time (nano)           :  %lu\n", this->_vars.reftime.start.nanos);
    printf("\tstart time (seconds)        :  %lu\n", this->_vars.reftime.start.seconds);
    printf("\tstart time (timestamp)      :  %lu\n", this->_vars.reftime.start.timestamp);
    printf("\thelper time (nano)          :  %lu\n", this->_vars.reftime.helper.nanos);
    printf("\thelper time (seconds)       :  %lu\n", this->_vars.reftime.helper.seconds);
    printf("\thelper time (timestamp)     :  %lu\n", this->_vars.reftime.helper.timestamp);
    printf("\tdate time stamp             :  %s\n", this->_vars.reftime.dts);
    printf("\trunning duration (seconds)  :  %lf\n", this->_vars.reftime.running_duration);
    printf("\ttimestamp rate              :  %lu\n", this->_vars.reftime.timestamp_rate);
    printf("\ttime source                 :  ");
    switch (this->_vars.reftime.source_select)
    {
        case (RSA_API::RTSRC_NONE)   : printf("none\n"); break;
        case (RSA_API::RTSRC_SYSTEM) : printf("system\n"); break;
        case (RSA_API::RTSRC_GNSS)   : printf("GNSS\n"); break;
        case (RSA_API::RTSRC_USER)   : printf("user\n");break;
        default                      : printf("unknown\n");break;
    }
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_reftime_init()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.reftime.current.nanos     = INIT_UINT;
    this->_vars.reftime.current.seconds   = INIT_UINT;
    this->_vars.reftime.current.timestamp = INIT_UINT;

    this->_vars.reftime.start.nanos     = INIT_UINT;
    this->_vars.reftime.start.seconds   = INIT_UINT;
    this->_vars.reftime.start.timestamp = INIT_UINT;

    this->_vars.reftime.helper.nanos     = INIT_UINT;
    this->_vars.reftime.helper.seconds   = INIT_UINT;
    this->_vars.reftime.helper.timestamp = INIT_UINT;
    
    memset(this->_vars.reftime.dts , '\0'      , BUF_C);
    strncpy(this->_vars.reftime.dts, INIT_CHARP, BUF_C-1);

    this->_vars.reftime.running_duration = INIT_DOUBLE;
    this->_vars.reftime.source_select    = RSA_API::RTSRC_USER;
    this->_vars.reftime.timestamp_rate   = INIT_UINT;
}


////////~~~~~~~~END>  rsa306b_x.cpp
