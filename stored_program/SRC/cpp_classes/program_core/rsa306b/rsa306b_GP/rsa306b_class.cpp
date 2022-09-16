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

    (void)this->_confirm
    (
        RSA_API::DEVICE_Disconnect()
    );
    (void)this->clear();    // initialize the members, includes composed class instance "cutil"

#ifdef DEBUGS_WILL_PRINT
    (void)this->cutil.timer_print_running(1,2);
#endif
#ifdef DE_BUG
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

    int opz = 2;
    CODEZ catch_opz[opz];

    this->_api_status = RSA_API::DEVICE_Disconnect();
    catch_opz[0] = this->_report_api_status();

    catch_opz[1] = this->cutil.clear();
    
    catch_opz[2] = this->_init_everything();

    return this->cutil.codez_checker(catch_opz, opz);
}


////~~~~


/*
    < 4 > public
    copies every variable of the private struct into the public struct
    the class attempts to update the public struct in real time
    this function can be called for insurace or convienence
    deep copy is performed by group, using group copier functions
*/
CODEZ rsa306b_class::get_everything()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int getz = 10;
    CODEZ catch_getz[getz];
    
    catch_getz[0]  = this->_align_get_vars();
    catch_getz[1]  = this->_audio_get_vars();
    catch_getz[2]  = this->_config_get_vars();
    catch_getz[3]  = this->_device_get_vars();
    catch_getz[4]  = this->_ifstream_get_vars();
    catch_getz[5]  = this->_iqblk_get_vars();
    catch_getz[6]  = this->_iqstream_get_vars();
    catch_getz[7]  = this->_reftime_get_vars();
    catch_getz[8]  = this->_spectrum_get_vars();
    catch_getz[9]  = this->_trig_get_vars();

    // INSERT

    return this->cutil.codez_checker(catch_getz, getz);
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

    constexpr int initz = 11;
    CODEZ catch_initz[initz];

    catch_initz[0]  = this->_gp_init();
    catch_initz[1]  = this->_align_init();
    catch_initz[2]  = this->_audio_init();
    catch_initz[3]  = this->_config_init();
    catch_initz[4]  = this->_device_init();
    catch_initz[5]  = this->_ifstream_init();
    catch_initz[6]  = this->_iqblk_init();
    catch_initz[7]  = this->_iqstream_init();
    catch_initz[8]  = this->_reftime_init();
    catch_initz[9]  = this->_spectrum_init();
    catch_initz[10] = this->_trig_init();

    // INSERT

    return this->cutil.codez_checker(catch_initz, initz);
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
        if (fclose(this->_fp_write) != 0)
        {
            (void)this->cutil.report_status_code(CODEZ::_10_fclose_failed);
        }
    }
    this->_fp_write = NULL;

    this->_api_status = RSA_API::noError;
    memset(this->_helper, '\0', sizeof(this->_helper));
    memset(this->_holder, '\0', sizeof(this->_holder));

    return this->cutil.get_status_code();
}


////////~~~~~~~~END>  rsa306b_constructor.cpp
