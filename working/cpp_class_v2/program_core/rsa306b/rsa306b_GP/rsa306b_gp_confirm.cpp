/*
    "general purpose" group, confirmation functions

    public :
        #  none
    
    private :
        < 1 >  _gp_confirm_api_status()
        < 2 >  _gp_confirm_error_code()
        < 3 >  _gp_confirm_call_status()
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
#ifdef DEBUG_ERR
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #if defined (DEBUG_ERR) || (DEBUG_MIN)
            this->_gp_confirm_error_code();
            printf("\n\t###   !!!   API ERROR   !!!   ###   %s\n", 
                this->_vars.gp.error_code);
        #endif
    }
}


////~~~~


/*
    private < 2 >
    updates "_vars.gp.error_code" with API message as a string
    the API looks up the message base on the return status
*/
void rsa306b_class::_gp_confirm_error_code()
{
#ifdef DEBUG_CL
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    const char* temp = NULL;
    temp = RSA_API::DEVICE_GetErrorString(this->_vars.gp.api_status);
    snprintf(this->_vars.gp.error_code, BUF_D-1, 
        "error code:  %d  ,  error message:  %s", 
        this->_vars.gp.api_status, temp);
    temp = NULL;
}


////~~~~


/*
    private < 3 >
    called to indicate error conditions 
    good practice to get the return value, then call
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b_class::_gp_confirm_call_status()
{
#ifdef DEBUG_ERR
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.gp.call_status      != 
        this->_vars.constants.CALL_SUCCESS)
    {
        #if defined (DEBUG_ERR) || (DEBUG_MIN)
            printf("\n\t###   !!! ERROR  IN THE OBJECT !!!   ###\n");
        #endif
    }
}


////////~~~~~~~~END>  rsa306b_gp_confirm.cpp
