/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_get_vars()
        < 2 >  _iqstream_get_bandwidth()
        < 3 >  _iqstream_get_acq_parameters()
        < 4 >  _iqstream_get_disk_fileinfo()
        < 5 >  _iqstream_get_is_enabled()
        < 6 >  _iqstream_get_pairs_max()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_iqstream_get_vars()
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
    
    this->_iqstream_get_vars();
    this->_iqstream_get_bandwidth();
    this->_iqstream_get_acq_parameters();
    this->_iqstream_get_disk_fileinfo();
    this->_iqstream_get_is_enabled();
    this->_iqstream_get_pairs_max();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_get_bandwidth()
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


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_iqstream_get_acq_parameters()
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


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_iqstream_get_disk_fileinfo()
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


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_iqstream_get_is_enabled()
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


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_iqstream_get_pairs_max()
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


////////~~~~~~~~END>  rsa306b_iqstream_get.cpp
