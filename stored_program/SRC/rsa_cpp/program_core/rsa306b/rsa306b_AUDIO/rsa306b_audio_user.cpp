/*
    API group "AUDIO", user functions
    these sacrifice guards for speed
    ensure proper calling sequence

    public :
        < 1 >  audio_acquire_data()
        < 2 >  audio_start()
        < 3 >  audio_stop()

    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    public struct is updated if audio data samples are acquired

    0) user has successfully connected the device
    1) user updates public "vars.audio" struct with desired values
    2) user calls "audio_set_vars()"               // "device_stop()" is called here
    3) user calls "device_run()"                   // if not recently called
    4) user calls "audio_start()"                  // for first audio acquisition only
    5) user calls "audio_acquire_data()"           // this function, call as many times as desired
    6) user calls "audio_stop()"                   // when all audio acquisitons are complete
    7) user calls "device_stop()"                  // if no more acquisitions are desired

    this function is built for speed and sacrifices some of the guards
    all the "set" and "run" checks are omitted because they should have been caught in:
    audio_set_vars()    // limits enforced
    audio_start()       // device is in correct run-state and "_vars.audio.is_demodulating == true"
*/
CODEZ rsa306b_class::audio_acquire_data()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    int16_t* data = NULL;
    if 
    (
        this->cutil.h_new_int16_d1    // dynamic allocation
        (
            data,
            this->_vars.audio.data_samples_requested
        ) != CODEZ::_0_no_errors
    )
    {
        // allocation failed, device audio demodulation is stopped, but device is still in run-state
        return this->audio_stop();
    }

    this->_vars.audio.data_samples_acquired = 0;    // reset acquisition count
    
    // API is called to acquire AUDIO data
    RSA_API::ReturnStatus temp =
        RSA_API::AUDIO_GetData
        (
            data, 
            this->_vars.audio.data_samples_requested, 
            &this->_vars.audio.data_samples_acquired
        );

    (void)this->cutil.h_copy_int16_to_vector_d1    // deep copy int std::vector<int16_t>
    (
        data, 
        this->_vars.audio.data_samples_acquired, 
        this->_vars.audio.data_v
    );
    (void)this->cutil.h_delete_int16_d1(data);    // dynamic deallocation
    
    (void)this->_audio_copy_data_v();      // public struct updates
    return this->set_api_status(temp);
}


////~~~~


/*
    < 2 > public
    user should have called "device_run()" before calling this
    when successful, the user can call "audio_acquire_data()" as many times as desired

    requirements:
        _vars.device.is_connected == true
        _vars.audio.data_samples_requested >= 1
        _vars.audio.data_samples_requested <= _vars.audio.DATA_V_MAX_LENGTH
        _vars.device.is_running == true
*/
CODEZ rsa306b_class::audio_start()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    RSA_API::ReturnStatus temp = RSA_API::AUDIO_Start();
    (void)this->_audio_get_is_demodulating();
    if (this->_vars.audio.is_demodulating == true)
    {
        return this->set_api_status(temp);
    }
    #ifdef DEBUG_MIN
        (void)snprintf(X_ddts, sizeof(X_ddts), "audio.is_demodulating=  %d", this->_vars.audio.is_demodulating);
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif
    return this->cutil.report_status_code(CODEZ::_21_rsa_api_task_failed);
}


////~~~~


/*
    < 3 > public
    user calls "device_stop()" after this, unless more acquisition is desired
*/
CODEZ rsa306b_class::audio_stop()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    RSA_API::ReturnStatus temp = RSA_API::AUDIO_Stop();
    (void)this->_audio_get_is_demodulating();
    if (this->_vars.audio.is_demodulating == false)
    {
        return this->set_api_status(temp);
    }
    #ifdef DEBUG_MIN
        (void)snprintf(X_ddts, sizeof(X_ddts), "audio.is_demodulating=  %d", this->vars.audio.is_demodulating);
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif
    return this->cutil.report_status_code(CODEZ::_21_rsa_api_task_failed);
}


////////~~~~~~~~END>  rsa306b_audio_user.cpp
