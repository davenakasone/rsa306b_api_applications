/*
    the class constructor and destructor + 

    public :
        < 1 >  rsa306b_class()
        < 2 >  ~rsa306b_class()
        < 3 >  clear()
        < 4 >  get_everything()    // INSERT point
    
    private :
        < 1 >  _init_everything()    // INSERT point
        < 2 >  _gp_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
rsa306b_class::rsa306b_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->clear();    // initialize the members, includes composed class instance "cutil"
}


////~~~~


/*
    < 2 > public
*/
rsa306b_class::~rsa306b_class()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

   (void)this->set_api_status(RSA_API::DEVICE_Disconnect());  // insurance
    //(void)this->device_disconnect();    // attempts to disconect, automatic clear() if device was connected

#ifdef DE_BUG
    (void)this->cutil.timer_print_running(1, 2); // only constructor triggering print
    debug_stop();
#endif
}


////~~~~


/*
    < 3 > public
*/
CODEZ rsa306b_class::clear()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int calls = 3;
    CODEZ caught_call[calls];

    caught_call[0] = this->set_api_status(RSA_API::DEVICE_Disconnect()); // insurance
    // if (this->_vars.device.is_connected == true)
    // {
    //     caught_call[0] = this->set_api_status(RSA_API::DEVICE_Disconnect());
    // }
    // else
    // {
    //     caught_call[0] = CODEZ::_0_no_errors;
    // }
    caught_call[1] = this->cutil.clear();         // clear the composed instance
    caught_call[2] = this->_init_everything();    // clear variables in this instance

    return this->cutil.codez_checker(caught_call, calls);
}


////~~~~


/*
    < 4 > public
    copies every variable of the private struct into the public struct
    the class attempts to update the public struct in real time
    this function can be called for insurace or convienence
    deep copy is performed by group, using group copier functions
    this function is unecessary during normal operation
*/
CODEZ rsa306b_class::get_everything()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    constexpr int calls = 10;
    CODEZ caught_call[calls];
    
    caught_call[0]  = this->_align_get_vars   ();
    caught_call[1]  = this->_audio_get_vars   ();
    caught_call[2]  = this->_config_get_vars  ();
    caught_call[3]  = this->_device_get_vars  ();
    caught_call[4]  = this->_ifstream_get_vars();
    caught_call[5]  = this->_iqblk_get_vars   ();
    caught_call[6]  = this->_iqstream_get_vars();
    caught_call[7]  = this->_reftime_get_vars ();
    caught_call[8]  = this->_spectrum_get_vars();
    caught_call[9]  = this->_trig_get_vars    ();

    // INSERT

    return this->cutil.codez_checker(caught_call, calls);
}


////~~~~


/*
    < 1 > private
    initializes all class variables,
        using group initializers
    sets the public struct
*/
CODEZ rsa306b_class::_init_everything()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int calls = 11;
    CODEZ caught_call[calls];

    caught_call[0]  = this->_gp_init      ();
    caught_call[1]  = this->_align_init   ();
    caught_call[2]  = this->_audio_init   ();
    caught_call[3]  = this->_config_init  ();
    caught_call[4]  = this->_device_init  ();
    caught_call[5]  = this->_ifstream_init();
    caught_call[6]  = this->_iqblk_init   ();
    caught_call[7]  = this->_iqstream_init();
    caught_call[8]  = this->_reftime_init ();
    caught_call[9]  = this->_spectrum_init();
    caught_call[10] = this->_trig_init    ();

    // INSERT

    return this->cutil.codez_checker(caught_call, calls);
}


////~~~~


/*
    < 2 > private
    initializes the "general purpose" variables
*/
CODEZ rsa306b_class::_gp_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_fp_write != NULL)
    {
        fclose(this->_fp_write);
        this->_fp_write = NULL;
    }
    this->_api_status = RSA_API::noError;
    (void)memset(this->_helper, '\0', sizeof(this->_helper));
    (void)memset(this->_holder, '\0', sizeof(this->_holder));

    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_constructor.cpp
