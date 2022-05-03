/*
    API group "IFSTREAM", getters

    public :
        #  none
    
    private :
        < 1 >  _ifstreamm_get_vars()
        < 2 >  _ifstream_get_is_active()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_get_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

    this->_ifstream_get_is_active();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_ifstream_get_is_active()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetActiveStatus(
            &this->_vars.ifstream.is_active);
    this->_ifstream_copy_is_active();
}


////////~~~~~~~~END>  rsa306b_ifstream_get.cpp
