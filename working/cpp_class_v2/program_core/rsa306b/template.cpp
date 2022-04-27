/*
    API group "xxx"

    public :
        < 1 >  xxx()
    
    private :
        < 1 >  _xxx()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::
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
}


////////~~~~~~~~END>  rsa306b_x.cpp
