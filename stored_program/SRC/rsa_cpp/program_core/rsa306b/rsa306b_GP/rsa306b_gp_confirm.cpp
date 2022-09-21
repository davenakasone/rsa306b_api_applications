/*
    "general purpose" group, confirmation functions

    public :
        < 1 >  get_api_status_number()
        < 2 >  get_api_status_string()
        < 3 >  get_api_status()  
        < 4 >  set_api_status()    
                
    
    private :
        < 1 >  _report_api_status()
        < 2 >  _confirm_api_status()
*/

#include "../rsa306b_class.h"



/*
    public < 1 >
*/
int rsa306b_class::get_api_status_number()
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return static_cast<int>(this->_api_status);
}


////~~~~


/*
    public < 2 >
*/
char* rsa306b_class::get_api_status_string()
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_device_get_api_status_message();
    return this->vars.device.api_status_message;
}


////~~~~


/*
    public < 3 >
*/
RSA_API::ReturnStatus rsa306b_class::get_api_status()
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_api_status;
}


////~~~~


/*
    public < 4 >
    call check the API status code after some delay, or in a loop
    good for getting a return status and updating it at leaset 2 execution tasks into the future
    also helps user manage the API status when working with the class and API directly
*/
CODEZ rsa306b_class::set_api_status
(
    RSA_API::ReturnStatus result
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_api_status = result;
    return this->_report_api_status();
}


////~~~~


/*
    < 1 > private
    matches current state of the ReturnStatus variable to the enum
    indicates if an error has occured, otherwise does nothing
    good practice to call after each API function is used, unless speed is needed
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
CODEZ rsa306b_class::_report_api_status()
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_api_status != RSA_API::noError)
    {
        this->_device_get_api_status_message();
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), "API ERROR  %4d  !!!  %s", 
                static_cast<int>(this->_api_status),
                this->_vars.device.api_status_message);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_1_rsa_api_error);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}












/*
    private < 4 >
    applies reccomended bit-check
    bits: 0, 1, 4, and 5 are checked
*/
// CODEZ rsa306b_class::_gp_confirm_aquisition_code()
// {
// #ifdef DEBUG_CALL_CHECKS
//     snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     this->_gp_copy_acquisition_code();
//     if (this->_vars.device.is_connected == false)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "not connected { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }
//     if ((this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_VALID_BITS_MASK) == 0)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "no errors in previous acquisition { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }

//     // Bit 0: Overrange - Input to the ADC was outside of its operating range
//     if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_ADC_OVERRANGE)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "ADC over overating range { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }
//     // Bit 1: RefOscUnlocked - Loss of locked status on the reference oscillator
//     if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_REF_OSC_UNLOCK)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "lost oscillator lock { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }
//     // Bit 4: PowerFail - Power (5V and Usb) failure detected
//     if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_LOW_SUPPLY_VOLTAGE)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "USB power failure detected { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }
//     // Bit 5: Dropped frame - Loss of ADC data frame samples
//     if (this->_vars.gp.acquisition_code & RSA_API::AcqDataStatus_ADC_DATA_LOST)
//     {
//         snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//             "ADC lost data frame samples { 0x%X }",
//             this->_vars.gp.acquisition_code);
//         this->_gp_copy_acquistion_message();
//         #ifdef DEBUG_MAX
//             printf("\n\tacquisition message:  %s\n",
//                 this->_vars.gp.acquisition_message);
//         #endif
//         return;
//     }

//     snprintf(this->_vars.gp.acquisition_message, BUF_B-1, 
//         "!!! program failure { 0x%X } !!!",
//         this->_vars.gp.acquisition_code);
//     this->_gp_copy_acquistion_message();
//     #ifdef DEBUG_MAX
//         printf("\n\tacquisition message:  %s\n",
//             this->_vars.gp.acquisition_message);
//     #endif
// }

////////~~~~~~~~END>  rsa306b_gp_confirm.cpp
