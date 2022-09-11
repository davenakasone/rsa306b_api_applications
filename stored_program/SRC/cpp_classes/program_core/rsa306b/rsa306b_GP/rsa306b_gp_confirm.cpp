/*
    "general purpose" group, confirmation functions

    public :
        #  none
    
    private :
        < 1 >  _gp_confirm_api_status()
        < 2 >  _gp_confirm_call_status()
        < 3 >  _gp_confirm_return()
        < 4 >  _gp_confirm_aquisition_code()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    matches current state of the ReturnStatus variable to the enum
    indicates if an error has occured, otherwise does nothing
    good practice to call after each API function is used, unless speed is needed
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b_class::_gp_confirm_api_status()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        this->_device_get_error_string();
        #ifdef DEBUG_MIN
            snprintf(X_dstr, sizeof(X_dstr), "API ERROR  %4d  !!!  %s", 
                static_cast<int>(this->_vars.gp.api_status),
                this->_vars.device.error_string);
            debug_record(true);
        #endif
    }
    this->_gp_copy_api_status();
}


////~~~~


/*
    private < 2 >
    called to indicate error conditions 
    good practice to get the return value, then call
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b_class::_gp_confirm_call_status()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.gp.call_status      != 
        this->constants.CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            snprintf(X_dstr, sizeof(X_dstr), "!!! error in rsa306b_class");
            debug_record(true);
        #endif
    }
    this->_gp_copy_call_status();
}


////~~~~


/*
    private < 3 >
    uses API state to select an internal return value
*/
int rsa306b_class::_gp_confirm_return()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.gp.api_status == RSA_API::noError)
    {
        return this->constants.CALL_SUCCESS;
    }
    else
    {
        return this->constants.CALL_FAILURE;
    }
}


////~~~~


/*
    private < 4 >
    applies reccomended bit-check
    bits: 0, 1, 4, and 5 are checked
*/
void rsa306b_class::_gp_confirm_aquisition_code()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    /*
    this->_gp_copy_acquisition_code();
    if (this->_vars.device.is_connected == false)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "not connected { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }
    if ((this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_VALID_BITS_MASK) == 0)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "no errors in previous acquisition { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }

    // Bit 0: Overrange - Input to the ADC was outside of its operating range
    if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_ADC_OVERRANGE)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "ADC over overating range { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }
    // Bit 1: RefOscUnlocked - Loss of locked status on the reference oscillator
    if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_REF_OSC_UNLOCK)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "lost oscillator lock { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }
    // Bit 4: PowerFail - Power (5V and Usb) failure detected
    if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_LOW_SUPPLY_VOLTAGE)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "USB power failure detected { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }
    // Bit 5: Dropped frame - Loss of ADC data frame samples
    if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_ADC_DATA_LOST)
    {
        snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
            "ADC lost data frame samples { 0x%X }",
            this->_vars.gp.acquisition_code);
        this->_gp_copy_acquistion_message();
        #ifdef DEBUG_MAX
            printf("\n\tacquisition message:  %s\n",
                this->_vars.gp.acquisition_message);
        #endif
        return;
    }

    snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
        "!!! program failure { 0x%X } !!!",
        this->_vars.gp.acquisition_code);
    this->_gp_copy_acquistion_message();
    #ifdef DEBUG_MAX
        printf("\n\tacquisition message:  %s\n",
            this->_vars.gp.acquisition_message);
    #endif
    */
}

////////~~~~~~~~END>  rsa306b_gp_confirm.cpp
