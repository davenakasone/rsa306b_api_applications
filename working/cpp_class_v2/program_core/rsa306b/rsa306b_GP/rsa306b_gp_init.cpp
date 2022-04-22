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

    this->get_everything();
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
    memset(this->_vars.gp.holder, '\0', BUF_F);
    memset(this->_vars.gp.error_code, '\0', BUF_D);
    strcpy(this->_vars.gp.helper, this->_vars.constants.INIT_STR);
    strcpy(this->_vars.gp.holder, this->_vars.constants.INIT_STR);
    strcpy(this->_vars.gp.error_code, this->_vars.constants.INIT_STR);
    this->_vars.gp.api_status = RSA_API::noError;
    this->_vars.gp.call_status = this->_vars.constants.CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_gp_init.cpp
