/*
    "general purpose" group, confirmation functions

    public :
        #  none
    
    private :
        < 1 >  _gp_confirm_api_status()
        < 2 >  _gp_confirm_call_status()
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
            this->_device_get_error_string();
            printf("\n\t###   !!!   API ERROR   !!!   ###   %s\n", 
                this->_vars.device.error_string);
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
    this->_gp_copy_call_status();
}


////////~~~~~~~~END>  rsa306b_gp_confirm.cpp
