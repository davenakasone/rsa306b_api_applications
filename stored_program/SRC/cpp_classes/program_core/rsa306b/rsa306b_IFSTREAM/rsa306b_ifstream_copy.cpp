/*
    API group "IFSTREAM", copiers

    public :
        #  none
    
    private :
        < 1 >   _ifstream_copy_vars()
        < 2 >   _ifstream_copy_file_name_suffix()
        < 3 >   _ifstream_copy_file_path()
        < 4 >   _ifstream_copy_file_name_base()
        < 5 >   _ifstream_copy_file_length_ms()
        < 6 >   _ifstream_copy_file_count()
        < 7 >   _ifstream_copy_output_configuration_select()
        < 8 >   _ifstream_copy_is_enabled_adc()
        < 9 >   _ifstream_copy_is_active()
        < 10 >  _ifstream_copy_if_data()
        < 11 >  _ifstream_copy_if_data_length()
        < 12 >  _ifstream_copy_data_info_type()
        < 13 >  _ifstream_copy_adc_data_v()
        < 14 >  _ifstream_copy_if_frames()
        < 15 >  _ifstream_copy_frame_bytes()
        < 16 >  _ifstream_copy_number_of_frames()
        < 17 >  _ifstream_copy_framed_adc_data_v()
        < 18 >  _ifstream_copy_eq_parameters()
        < 19 >  _ifstream_copy_points_in_equalization_buffer()
        < 20 >  _ifstream_copy_eq_frequency_v()
        < 21 >  _ifstream_copy_eq_amplitude_v()
        < 22 >  _ifstream_copy_eq_phase_v()
        < 23 >  _ifstream_copy_scaling_parameters()
        < 24 >  _ifstream_copy_scale_factor()
        < 25 >  _ifstream_copy_scale_frequency()
        < 26 >  _ifstream_copy_acq_parameters()
        < 27 >  _ifstream_copy_if_bandwidth_hz()
        < 28 >  _ifstream_copy_samples_per_second()
        < 29 >  _ifstream_copy_if_center_frequency()
        < 30 >  _ifstream_copy_buffer_size()
        < 31 >  _ifstream_copy_buffer_size_bytes()
        < 32 >  _ifstream_copy_number_of_samples()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_copy_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_file_name_suffix();
    this->_ifstream_copy_file_path();
    this->_ifstream_copy_file_name_base();
    this->_ifstream_copy_file_length_ms();
    this->_ifstream_copy_file_count();
    this->_ifstream_copy_output_configuration_select();
    this->_ifstream_copy_is_enabled_adc();
    this->_ifstream_copy_is_active();
    this->_ifstream_copy_if_data();
    this->_ifstream_copy_if_frames();
    this->_ifstream_copy_eq_parameters();
    this->_ifstream_copy_scaling_parameters();
    this->_ifstream_copy_acq_parameters();
    this->_ifstream_copy_buffer_size();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_ifstream_copy_file_name_suffix()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.file_name_suffix = this->_vars.ifstream.file_name_suffix;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_ifstream_copy_file_path()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    strcpy(this->vars.ifstream.file_path, this->_vars.ifstream.file_path);
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_ifstream_copy_file_name_base()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    strcpy(this->vars.ifstream.file_name_base, this->_vars.ifstream.file_name_base);
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_ifstream_copy_file_length_ms()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.file_length_ms = this->_vars.ifstream.file_length_ms;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_ifstream_copy_file_count()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.file_count = this->_vars.ifstream.file_count;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_ifstream_copy_output_configuration_select()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.output_configuration_select = this->_vars.ifstream.output_configuration_select;
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_ifstream_copy_is_enabled_adc()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.is_enabled_adc = this->_vars.ifstream.is_enabled_adc;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_ifstream_copy_is_active()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.is_active = this->_vars.ifstream.is_active;
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_ifstream_copy_if_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_if_data_length();
    this->_ifstream_copy_data_info_type();
    this->_ifstream_copy_adc_data_v();
}


////~~~~


/*
    < 11 > private
*/
void rsa306b_class::_ifstream_copy_if_data_length()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.if_data_length = this->_vars.ifstream.if_data_length;
}


////~~~~


/*
    < 12 > private
*/
void rsa306b_class::_ifstream_copy_data_info_type()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.data_info_type.acqStatus      = this->_vars.ifstream.data_info_type.acqStatus;
    this->vars.ifstream.data_info_type.timestamp      = this->_vars.ifstream.data_info_type.timestamp;
    this->vars.ifstream.data_info_type.triggerCount   = this->_vars.ifstream.data_info_type.triggerCount;
    this->vars.ifstream.data_info_type.triggerIndices = this->_vars.ifstream.data_info_type.triggerIndices;
}


////~~~~


/*
    < 13 > private
*/
void rsa306b_class::_ifstream_copy_adc_data_v()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
    
    this->vars.ifstream.adc_data_v.resize(
        this->_vars.ifstream.adc_data_v.size());
    this->vars.ifstream.adc_data_v = this->_vars.ifstream.adc_data_v;
}


////~~~~


/*
    < 14 > private
*/
void rsa306b_class::_ifstream_copy_if_frames()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_frame_bytes();
    this->_ifstream_copy_number_of_frames();
    this->_ifstream_copy_framed_adc_data_v();
}


////~~~~


/*
    < 15 > private
*/
void rsa306b_class::_ifstream_copy_frame_bytes()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.frame_bytes = this->_vars.ifstream.frame_bytes;
}


////~~~~


/*
    < 16 > private
*/
void rsa306b_class::_ifstream_copy_number_of_frames()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.number_of_frames = this->_vars.ifstream.number_of_frames;
}


////~~~~


/*
    < 17 > private
*/
void rsa306b_class::_ifstream_copy_framed_adc_data_v()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.framed_adc_data_v.resize(
        this->_vars.ifstream.framed_adc_data_v.size());
    for (long unsigned int ii = 0; ii < this->_vars.ifstream.framed_adc_data_v.size(); ii++)
    {
        this->vars.ifstream.framed_adc_data_v[ii].resize(
            this->_vars.ifstream.framed_adc_data_v[ii].size());
        this->vars.ifstream.framed_adc_data_v[ii] = this->_vars.ifstream.framed_adc_data_v[ii];
    }
}


////~~~~


/*
    < 18 > private
*/
void rsa306b_class::_ifstream_copy_eq_parameters()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_points_in_equalization_buffer();
    this->_ifstream_copy_eq_frequency_v();
    this->_ifstream_copy_eq_amplitude_v();
    this->_ifstream_copy_eq_phase_v();
}


////~~~~


/*
    < 19 > private
*/
void rsa306b_class::_ifstream_copy_points_in_equalization_buffer()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.points_in_equalization_buffer = this->_vars.ifstream.points_in_equalization_buffer;
}


////~~~~


/*
    < 20 > private
*/
void rsa306b_class::_ifstream_copy_eq_frequency_v()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.eq_frequency_v.resize(
        this->_vars.ifstream.eq_frequency_v.size());
    this->vars.ifstream.eq_frequency_v = this->_vars.ifstream.eq_frequency_v;
}


////~~~~


/*
    < 21 > private
*/
void rsa306b_class::_ifstream_copy_eq_amplitude_v()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.eq_amplitude_v.resize(
        this->_vars.ifstream.eq_amplitude_v.size());
    this->vars.ifstream.eq_amplitude_v = this->_vars.ifstream.eq_amplitude_v;
}


////~~~~


/*
    < 22 > private
*/
void rsa306b_class::_ifstream_copy_eq_phase_v()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.eq_phase_v.resize(
        this->_vars.ifstream.eq_phase_v.size());
    this->vars.ifstream.eq_phase_v = this->_vars.ifstream.eq_phase_v;
}


////~~~~


/*
    < 23 > private
*/
void rsa306b_class::_ifstream_copy_scaling_parameters()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_scale_factor();
    this->_ifstream_copy_scale_frequency();
}


////~~~~


/*
    < 24 > private
*/
void rsa306b_class::_ifstream_copy_scale_factor()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.scale_factor = this->_vars.ifstream.scale_factor;
}


////~~~~


/*
    < 25 > private
*/
void rsa306b_class::_ifstream_copy_scale_frequency()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.scale_frequency = this->_vars.ifstream.scale_frequency;
}


////~~~~


/*
    < 26 > private
*/
void rsa306b_class::_ifstream_copy_acq_parameters()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_if_bandwidth_hz();
    this->_ifstream_copy_samples_per_second();
    this->_ifstream_copy_if_center_frequency();
}


////~~~~


/*
    < 27 > private
*/
void rsa306b_class::_ifstream_copy_if_bandwidth_hz()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.if_bandwidth_hz = this->_vars.ifstream.if_bandwidth_hz;
}


////~~~~


/*
    < 28 > private
*/
void rsa306b_class::_ifstream_copy_samples_per_second()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.samples_per_second = this->_vars.ifstream.samples_per_second;
}


////~~~~


/*
    < 29 > private
*/
void rsa306b_class::_ifstream_copy_if_center_frequency()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.if_center_frequency = this->_vars.ifstream.if_center_frequency;
}


////~~~~


/*
    < 30 > private
*/
void rsa306b_class::_ifstream_copy_buffer_size()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_ifstream_copy_buffer_size_bytes();
    this->_ifstream_copy_number_of_samples();
}


////~~~~


/*
    < 31 > private
*/
void rsa306b_class::_ifstream_copy_buffer_size_bytes()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.buffer_size_bytes = this->_vars.ifstream.buffer_size_bytes;
}


////~~~~


/*
    < 32 > private
*/
void rsa306b_class::_ifstream_copy_number_of_samples()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.ifstream.number_of_samples = this->_vars.ifstream.number_of_samples;
}


////////~~~~~~~~END>  rsa306b_ifstream_copy.cpp
 