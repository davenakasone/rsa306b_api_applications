/*
    class initializer and "general purpose" group initializer

    public :
        #  none
    
    private :
        < 1 >  _init_everything()
        < 2 >  _gp_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    initializes all class variables,
        using group initializers
    sets the public struct
*/
void rsa306b_class::_init_everything()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_gp_init();

    this->_device_init();

    this->_align_init();
}


////~~~~


/*
    < 2 > private
    initializes the "general purpose" variables
*/
void rsa306b_class::_gp_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    memset(this->_vars.gp.helper, '\0', BUF_E);
    strncpy(this->_vars.gp.helper, this->_vars.constants.INIT_STR, BUF_E-1);

    memset(this->_vars.gp.holder, '\0', BUF_F);
    strncpy(this->_vars.gp.holder, this->_vars.constants.INIT_STR, BUF_F-1);

    this->_vars.gp.api_status = RSA_API::noError;
    this->_vars.gp.call_status = this->_vars.constants.CALL_SUCCESS;

    this->_gp_copy_vars();
}


////////~~~~~~~~END>  rsa306b_gp_init.cpp
