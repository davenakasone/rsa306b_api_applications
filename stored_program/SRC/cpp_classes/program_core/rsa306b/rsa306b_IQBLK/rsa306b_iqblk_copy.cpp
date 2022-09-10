/*
    API group "IQBLK"

    public :
        #  none
    
    private :
        < 1 >   _iqblk_copy_vars()
        < 2 >   _iqblk_copy_getter()
        < 3 >   _iqblk_copy_actual_buffer_samples()
        //< 4 >   _iqblk_copy_sample_pairs_requested()
        < 5 >   _iqblk_copy_cplx32_v()
        < 6 >   _iqblk_copy_acq_info_type()
        < 7 >   _iqblk_copy_bitcheck()
        < 8 >   _iqblk_copy_sample_rate()
        < 9 >   _iqblk_copy_bandwidth_hz()
        < 10 >  _iqblk_copy_max_bandwidth_hz()
        < 11 >  _iqblk_copy_min_bandwidth_hz()
        < 12 >  _iqblk_copy_record_length()
        < 13 >  _iqblk_copy_max_record_length()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_iqblk_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_iqblk_copy_getter();
    this->_iqblk_copy_actual_buffer_samples();
    //this->_iqblk_copy_sample_pairs_requested();
    this->_iqblk_copy_cplx32_v();
    this->_iqblk_copy_acq_info_type();
    this->_iqblk_copy_bitcheck();
    this->_iqblk_copy_sample_rate();
    this->_iqblk_copy_bandwidth_hz();
    this->_iqblk_copy_max_bandwidth_hz();
    this->_iqblk_copy_min_bandwidth_hz();
    this->_iqblk_copy_record_length();
    this->_iqblk_copy_max_record_length();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqblk_copy_getter()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.getter = this->_vars.iqblk.getter;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_iqblk_copy_actual_buffer_samples()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.actual_buffer_samples = this->_vars.iqblk.actual_buffer_samples;
}


////~~~~


/*
    < 4 > private

void rsa306b_class::_iqblk_copy_sample_pairs_requested()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.sample_pairs_requested = this->_vars.iqblk.sample_pairs_requested;
}
*/

////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_iqblk_copy_cplx32_v()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.cplx32_v.resize(
        this->_vars.iqblk.cplx32_v.size());
    for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)
    {
        this->vars.iqblk.cplx32_v[ii].i = this->_vars.iqblk.cplx32_v[ii].i;
        this->vars.iqblk.cplx32_v[ii].q = this->_vars.iqblk.cplx32_v[ii].q;
    }
}



////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_iqblk_copy_acq_info_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.acq_info_type.acqStatus          = this->_vars.iqblk.acq_info_type.acqStatus;
    this->vars.iqblk.acq_info_type.sample0Timestamp   = this->_vars.iqblk.acq_info_type.sample0Timestamp;
    this->vars.iqblk.acq_info_type.triggerSampleIndex = this->_vars.iqblk.acq_info_type.triggerSampleIndex;
    this->vars.iqblk.acq_info_type.triggerTimestamp   = this->_vars.iqblk.acq_info_type.triggerTimestamp;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_iqblk_copy_bitcheck()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    strcpy(this->vars.iqblk.bitcheck, this->_vars.iqblk.bitcheck);
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_iqblk_copy_sample_rate()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.sample_rate = this->_vars.iqblk.sample_rate;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_iqblk_copy_bandwidth_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.bandwidth_hz = this->_vars.iqblk.bandwidth_hz;
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_iqblk_copy_max_bandwidth_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.max_bandwidth_hz = this->_vars.iqblk.max_bandwidth_hz;
}


////~~~~


/*
    < 11 > private
*/
void rsa306b_class::_iqblk_copy_min_bandwidth_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.min_bandwidth_hz = this->_vars.iqblk.min_bandwidth_hz;
}


////~~~~


/*
    < 12 > private
*/
void rsa306b_class::_iqblk_copy_record_length()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.record_length = this->_vars.iqblk.record_length;
}


////~~~~


/*
    < 13 > private
*/
void rsa306b_class::_iqblk_copy_max_record_length()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqblk.max_record_length = this->_vars.iqblk.max_record_length;
}

////////~~~~~~~~END>  rsa306b_iqblk_copy.cpp
