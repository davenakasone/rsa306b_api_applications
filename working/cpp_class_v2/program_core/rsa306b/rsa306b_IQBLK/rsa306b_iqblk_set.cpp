/*
    API group "xxx"

    public :
        < 1 >  iqblk_set_vars()
    
    private :
        < 1 >  _iqblk_set_vars()
        < 2 >  _iqblk_set_getter()
        < 3 >  _iqblk_set_bandwidth_hz()
        < 4 >  _iqblk_set_record_length()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::iqblk_set_vars()
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
    this->_iqblk_set_vars();
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqblk_set_vars()
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
    this->_iqblk_set_getter();
    this->_iqblk_set_bandwidth_hz();
    this->_iqblk_set_record_length();
}


////~~~~


/*
    < 2 > private
    does not require API
*/
void rsa306b_class::_iqblk_set_getter()
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
    if (this->vars.iqblk.getter == this->_vars.iqblk.getter)
    {
        #ifdef DEBUG_MAX
            printf("\n\tgetter already set\n");
        #endif
        return;
    }

    if (this->vars.iqblk.getter != IQBLK_GET_IQ_DATA               &&
        this->vars.iqblk.getter != IQBLK_GET_IQ_DATA_CPLX          &&
        this->vars.iqblk.getter != IQBLK_GET_IQ_DATA_DEINETERLEAVED )
    {
        #ifdef DEBUG_MAX
            printf("\n\tinvalid selection, using default from const class\n");
        #endif
        this->_vars.iqblk.getter = this->_vars.constants.IQBLK_GETTER_DEFAULT;
        this->_iqblk_copy_getter();
        return;
    }
    this->_vars.iqblk.getter = this->vars.iqblk.getter;
}


////~~~~


/*
    < 3 > private
    should be set first
*/
void rsa306b_class::_iqblk_set_bandwidth_hz()
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
    if (this->vars.iqblk.bandwidth_hz == this->_vars.iqblk.bandwidth_hz)
    {
        #ifdef DEBUG_MAX
            printf("\n\tbandwidth already set\n");
        #endif
        return;
    }

    if (this->vars.iqblk.bandwidth_hz < this->_vars.iqblk.min_bandwidth_hz ||
        this->vars.iqblk.bandwidth_hz > this->_vars.iqblk.max_bandwidth_hz  )
    {
        this->vars.iqblk.bandwidth_hz = this->_vars.iqblk.max_bandwidth_hz / 2;
        #ifdef DEBUG_MAX
            printf("\n\tinvalid IQ bandwidth, using:  %lf Hz\n", 
                this->vars.iqblk.bandwidth_hz);
        #endif
    }
    this->_vars.iqblk.bandwidth_hz = this->vars.iqblk.bandwidth_hz;
    this->_vars.gp.api_status =
        RSA_API::IQBLK_SetIQBandwidth(
            this->_vars.iqblk.bandwidth_hz);
    this->_gp_confirm_api_status();
    this->_iqblk_get_bandwidth_hz();
    this->_iqblk_get_min_bandwidth_hz();
    this->_iqblk_get_max_bandwidth_hz();
}


////~~~~


/*
    < 4 > private
    should be called after setting bandwidth
*/
void rsa306b_class::_iqblk_set_record_length()
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
    if (this->vars.iqblk.record_length == this->_vars.iqblk.record_length)
    {
        #ifdef DEBUG_MAX
            printf("\n\trecord length already set\n");
        #endif
        return;
    }

    this->_iqblk_get_max_record_length();
    if (this->vars.iqblk.record_length < this->_vars.constants.IQBLK_MIN_PAIRS ||
        this->vars.iqblk.record_length > this->_vars.iqblk.max_record_length    )
    {
        this->vars.iqblk.record_length = this->_vars.iqblk.max_record_length / 2;
        #ifdef DEBUG_MIN
            printf("\n\tinvalid IQ record length, using:  %d samples/pairs\n", 
                this->vars.iqblk.record_length);
        #endif
    }
    this->_vars.iqblk.record_length = this->vars.iqblk.record_length;
    this->_vars.gp.api_status =
        RSA_API::IQBLK_SetIQRecordLength(
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();
    this->_iqblk_get_record_length();
    this->_iqblk_get_max_record_length();

    this->_vars.iqblk.cplx32_v.resize(
        (size_t)this->_vars.iqblk.record_length);
    for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)
    {
        this->_vars.iqblk.cplx32_v[ii].i = this->_vars.constants.INIT_FLOAT;
        this->_vars.iqblk.cplx32_v[ii].q = this->_vars.constants.INIT_FLOAT;
    }
    this->_iqblk_copy_cplx32_v();
}


////////~~~~~~~~END>  rsa306b_iqblk_set.cpp
