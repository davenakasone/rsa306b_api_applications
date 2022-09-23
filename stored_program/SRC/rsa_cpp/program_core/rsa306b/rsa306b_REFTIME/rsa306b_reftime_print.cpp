/*
    API group "REFTIME"

    public :
        < 1 >  print_reftime()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::reftime_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'REFTIME' group >>>\n");

    (void)printf("\tdts                       :  %s\n", this->_vars.reftime.dts);
    (void)printf("\trunning_duration_seconds  :  %lf\n", this->_vars.reftime.running_duration_seconds);
    (void)printf("\ttimestamp_rate            :  %lu\n", this->_vars.reftime.timestamp_rate);
    (void)printf("\tsource_select             :  ");
    switch (this->_vars.reftime.source_select)
    {
        case (RSA_API::RTSRC_NONE)   : (void)printf("none\n"); break;
        case (RSA_API::RTSRC_SYSTEM) : (void)printf("system\n"); break;
        case (RSA_API::RTSRC_GNSS)   : (void)printf("GNSS\n"); break;
        case (RSA_API::RTSRC_USER)   : (void)printf("user\n");break;
        default                      : (void)printf("unknown\n");break;
    }

    (void)printf("\tcurrent.seconds           :  %ld\n", this->_vars.reftime.current.seconds);
    (void)printf("\tcurrent.nanos             :  %lu\n", this->_vars.reftime.current.nanos);
    (void)printf("\tcurrent.timestamp         :  %lu\n", this->_vars.reftime.current.timestamp);

    (void)printf("\tstart.seconds             :  %ld\n", this->_vars.reftime.start.seconds);
    (void)printf("\tstart.nanos               :  %lu\n", this->_vars.reftime.start.nanos);
    (void)printf("\tstart.timestamp           :  %lu\n", this->_vars.reftime.start.timestamp);

    (void)printf("\thelper.seconds            :  %ld\n", this->_vars.reftime.helper.seconds);
    (void)printf("\thelper.nanos              :  %lu\n", this->_vars.reftime.helper.nanos);
    (void)printf("\thelper.timestamp          :  %lu\n", this->_vars.reftime.helper.timestamp);

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_reftime_print.cpp
