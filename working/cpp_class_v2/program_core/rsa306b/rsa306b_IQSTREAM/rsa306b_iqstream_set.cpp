/*
    API group "xxx"

    public :
        < 1 >  iqstream_set_vars()
    
    private :
        < 1 >  _iqstream_set_vars()
        < 2 >  _iqstream_set_acq_bandwidth()
        < 3 >  _iqstream_set_disk_file_length()
        < 4 >  _iqstream_set_disk_filename_base()
        < 5 >  _iqstream_set_filename_suffix()
        < 6 >  _iqstream_set_iq_data_buffer_size()
        < 7 >  _iqstream_set_output_configuration()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::iqstream_set_vars()
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
    this->_iqstream_set_vars();
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqstream_set_vars()
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
    this->device_stop();

    this->_iqstream_set_acq_bandwidth();
    this->_iqstream_set_disk_file_length();
    this->_iqstream_set_disk_filename_base();
    this->_iqstream_set_filename_suffix();
    this->_iqstream_set_iq_data_buffer_size();
    this->_iqstream_set_output_configuration();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_set_acq_bandwidth()
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
    if (this->_vars.iqstream.bandwidth == this->vars.iqstream.bandwidth)
    {
        #ifdef DEBUG_MAX
            printf("\n\tbandwidth already set, requested { %lf }  ,  active { %lf }\n",
                this->vars.iqstream.bandwidth,
                this->_vars.iqstream.bandwidth);
        #endif
        return;
    }
    this->_iqstream_get_max_acq_bandwidth();
    this->_iqstream_get_min_acq_bandwidth();
    if (this->vars.iqstream.bandwidth < this->_vars.iqstream.bandwidth_min ||
        this->vars.iqstream.bandwidth > this->_vars.iqstream.bandwidth_max  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tbandwidth requested { %0.6lf }  out of range [ %lf : %lf ]\n",
                this->vars.iqstream.bandwidth,
                this->_vars.iqstream.bandwidth_min,
                this->_vars.iqstream.bandwidth_max);
        #endif
        return;    // old bandwidth remains
    }
    this->_vars.gp.api_status =
        RSA_API::IQSTREAM_SetAcqBandwidth(
            this->vars.iqstream.bandwidth);
    this->_gp_confirm_api_status();
    this->_iqstream_get_acq_parameters();    // sample rate depends on this, see p78
}


////~~~~


/*
    < 3 > private
    no API use to get after set
    the record time determines the size
*/
void rsa306b_class::_iqstream_set_disk_file_length()
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
    if (this->_vars.iqstream.record_time_ms == this->vars.iqstream.record_time_ms)
    {
        #ifdef DEBUG_MAX
            printf("\n\trecord time already set, requested { %d }ms  ,  active { %d }ms\n",
                this->vars.iqstream.record_time_ms,
                this->_vars.iqstream.record_time_ms);
        #endif
        return;
    }
    if (this->vars.iqstream.record_time_ms < this->constants.IQSTREAM_MSEC_MIN ||
        this->vars.iqstream.record_time_ms > this->constants.IQSTREAM_MSEC_MAX  )
    {
        #ifdef DEBUG_MIN
            printf("\n\trecord time ms, requested{ %d }  out of range [ %d : %d ]\n",
                this->vars.iqstream.record_time_ms,
                this->constants.IQSTREAM_MSEC_MIN,
                this->constants.IQSTREAM_MSEC_MAX);
        #endif
        return;    // old recording time remains
    }
    this->_vars.iqstream.record_time_ms = this->vars.iqstream.record_time_ms;
    this->_vars.gp.api_status =
        RSA_API::IQSTREAM_SetDiskFileLength
        (
            this->_vars.iqstream.record_time_ms
        );
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 4 > private
    no API use to get after set
*/
void rsa306b_class::_iqstream_set_disk_filename_base()
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
    if (this->vars.iqstream.filename_base == NULL)
    {
        #ifdef DEBUG_MAX
            printf("\n\trequested filename base not allocated\n");
        #endif
        return;    // no set occurs
    }
    if (strcmp(this->vars.iqstream.filename_base, this->_vars.iqstream.filename_base) == 0)
    {
        #ifdef DEBUG_MIN
            printf("\n\trequested filename base unchanged\n");
        #endif
        return;    // no set occurs
    }
    strcpy(this->_vars.iqstream.filename_base, this->vars.iqstream.filename_base);
    this->_vars.gp.api_status =
        RSA_API::IQSTREAM_SetDiskFilenameBase
        (
            this->_vars.iqstream.filename_base
        );
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 5 > private
    no API use to get after set
*/
void rsa306b_class::_iqstream_set_filename_suffix()
{
#ifdef DEBUG_CLI
    printf
        ("\n<%d> %s/%s()\n",
            __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (this->vars.iqstream.suffix_control < 
        (int)RSA_API::IQSSDFN_SUFFIX_NONE  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tsuffix not in range,  requested { %d }  ,  required { %d, %d, or >= %d}\n",
                static_cast<int>(this->vars.iqstream.suffix_control),
                (int)RSA_API::IQSSDFN_SUFFIX_NONE,
                (int)RSA_API::IQSSDFN_SUFFIX_TIMESTAMP,
                static_cast<int>(RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN));
        #endif
        return;    // no set occurs

    }
    if (this->vars.iqstream.suffix_control == this->_vars.iqstream.suffix_control)
    {
        #ifdef DEBUG_MAX
            printf("\n\tsuffix already set,  requested { %d }  ,  using { %d }\n",
                this->vars.iqstream.suffix_control,
                this->_vars.iqstream.suffix_control);
        #endif
        return;    // no set occurs
    }
    this->_vars.iqstream.suffix_control = this->vars.iqstream.suffix_control;
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_SetDiskFilenameSuffix
        (
            this->_vars.iqstream.suffix_control
        );
    this->_gp_confirm_api_status();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_iqstream_set_iq_data_buffer_size()
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
    < 7 > private
*/
void rsa306b_class::_iqstream_set_output_configuration()
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


////////~~~~~~~~END>  rsa306b_iqstream_set.cpp
