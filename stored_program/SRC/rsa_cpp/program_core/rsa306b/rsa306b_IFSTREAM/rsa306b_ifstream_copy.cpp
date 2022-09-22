/*
    API group "IFSTREAM", copiers

    public :
        #  none
    
    private :
        < 1 >   _ifstream_copy_vars()
        < 2 >   _ifstream_copy_file_name_suffix()
        < 3 >   _ifstream_copy_file_path()
        < 4 >   _ifstream_copy_file_name_base()
        < 5 >   _ifstream_copy_file_length_max_ms()
        < 6 >   _ifstream_copy_file_count()         
        < 7 >   _ifstream_copy_output_destination_select()
        < 8 >   _ifstream_copy_is_active()  
        < 9 >   _ifstream_copy_if_data_length()
        < 10 >  _ifstream_copy_data_info_type()          
        < 11 >  _ifstream_copy_adc_data_v()       
        < 12 >  _ifstream_copy_adc_tiggers_v()   
        < 13 >  _ifstream_copy_frame_bytes()
        < 14 >  _ifstream_copy_number_of_frames()
        < 15 >  _ifstream_copy_framed_adc_data_v()
        < 16 >  _ifstream_copy_points_in_equalization_buffer()
        < 17 >  _ifstream_copy_eq_frequency_v()
        < 18 >  _ifstream_copy_eq_amplitude_v()
        < 19 >  _ifstream_copy_eq_phase_v()
        < 20 >  _ifstream_copy_scale_factor()
        < 21 >  _ifstream_copy_scale_frequency()
        < 22 >  _ifstream_copy_if_bandwidth_hz()
        < 23 >  _ifstream_copy_samples_per_second()
        < 24 >  _ifstream_copy_if_center_frequency()
        < 25 >  _ifstream_copy_buffer_size_bytes()
        < 26 >  _ifstream_copy_buffer_samples()
        < 27 >  _ifstream_copy_acq_status_message()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_ifstream_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 26;
    CODEZ caught_call[callz];

    caught_call[0]   = this->_ifstream_copy_file_name_suffix();
    caught_call[1]   = this->_ifstream_copy_file_path();
    caught_call[2]   = this->_ifstream_copy_file_name_base();
    caught_call[3]   = this->_ifstream_copy_file_length_max_ms();
    caught_call[4]   = this->_ifstream_copy_file_count();
    caught_call[5]   = this->_ifstream_copy_output_destination_select();
    caught_call[6]   = this->_ifstream_copy_is_active();
    caught_call[7]   = this->_ifstream_copy_if_data_length();
    caught_call[8]   = this->_ifstream_copy_data_info_type();         
    caught_call[9]   = this->_ifstream_copy_adc_data_v();  
    caught_call[10]  = this->_ifstream_copy_adc_tiggers_v();
    caught_call[11]  = this->_ifstream_copy_frame_bytes();
    caught_call[12]  = this->_ifstream_copy_number_of_frames();
    caught_call[13]  = this->_ifstream_copy_framed_adc_data_v();
    caught_call[14]  = this->_ifstream_copy_points_in_equalization_buffer();
    caught_call[15]  = this->_ifstream_copy_eq_frequency_v();
    caught_call[16]  = this->_ifstream_copy_eq_amplitude_v();
    caught_call[17]  = this->_ifstream_copy_eq_phase_v();
    caught_call[18]  = this->_ifstream_copy_scale_factor();
    caught_call[19]  = this->_ifstream_copy_scale_frequency();
    caught_call[20]  = this->_ifstream_copy_if_bandwidth_hz();
    caught_call[21]  = this->_ifstream_copy_samples_per_second();
    caught_call[22]  = this->_ifstream_copy_if_center_frequency();
    caught_call[23]  = this->_ifstream_copy_buffer_size_bytes();
    caught_call[24]  = this->_ifstream_copy_buffer_samples();
    caught_call[25]  = this->_ifstream_copy_acq_status_message();
    
    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_ifstream_copy_file_name_suffix()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.file_name_suffix = this->_vars.ifstream.file_name_suffix;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_ifstream_copy_file_path()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)strcpy(this->vars.ifstream.file_path, this->_vars.ifstream.file_path);
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_ifstream_copy_file_name_base()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    strcpy(this->vars.ifstream.file_name_base, this->_vars.ifstream.file_name_base);
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_ifstream_copy_file_length_max_ms()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.file_length_max_ms = this->_vars.ifstream.file_length_max_ms;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_ifstream_copy_file_count()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.file_count = this->_vars.ifstream.file_count;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_ifstream_copy_output_destination_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.output_destination_select = this->_vars.ifstream.output_destination_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_ifstream_copy_is_active()  
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.is_active = this->_vars.ifstream.is_active;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_ifstream_copy_if_data_length()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.if_data_length = this->_vars.ifstream.if_data_length;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 10 > private
*/
CODEZ rsa306b_class::_ifstream_copy_data_info_type()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.data_info_type.acqStatus = this->_vars.ifstream.data_info_type.acqStatus;
    this->vars.ifstream.data_info_type.timestamp = this->_vars.ifstream.data_info_type.timestamp;
    this->vars.ifstream.data_info_type.triggerCount = this->_vars.ifstream.data_info_type.triggerCount;
    //this->_vars.ifstream.data_info_type.triggerIndices = this->_vars.ifstream.data_info_type.triggerIndices;

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 11 > private
*/
CODEZ rsa306b_class::_ifstream_copy_adc_data_v()  
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.adc_data_v.resize(this->_vars.ifstream.adc_data_v.size());
    this->vars.ifstream.adc_data_v = this->vars.ifstream.adc_data_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}



////~~~~


/*
    < 12 > private
*/
CODEZ rsa306b_class::_ifstream_copy_adc_tiggers_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.adc_triggers_v.resize(this->_vars.ifstream.adc_triggers_v.size());
    this->vars.ifstream.adc_triggers_v = this->_vars.ifstream.adc_triggers_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 13 > private
*/
CODEZ rsa306b_class::_ifstream_copy_frame_bytes()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.frame_bytes = this->_vars.ifstream.frame_bytes;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 14 > private
*/
CODEZ rsa306b_class::_ifstream_copy_number_of_frames()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.number_of_frames = this->_vars.ifstream.number_of_frames;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 15 > private
*/
CODEZ rsa306b_class::_ifstream_copy_framed_adc_data_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.framed_adc_data_v.resize(this->vars.ifstream.framed_adc_data_v.size());
    for (std::size_t ii = 0; ii < this->vars.ifstream.framed_adc_data_v.size(); ii++)
    {
        this->vars.ifstream.framed_adc_data_v[ii].resize(this->_vars.ifstream.framed_adc_data_v[ii].size());
        this->vars.ifstream.framed_adc_data_v[ii] = this->_vars.ifstream.framed_adc_data_v[ii];
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 16 > private
*/
CODEZ rsa306b_class::_ifstream_copy_points_in_equalization_buffer()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.points_in_equalization_buffer = this->_vars.ifstream.points_in_equalization_buffer;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 17 > private
*/
CODEZ rsa306b_class::_ifstream_copy_eq_frequency_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.eq_frequency_v.resize(this->_vars.ifstream.eq_frequency_v.size());
    this->vars.ifstream.eq_frequency_v = this->_vars.ifstream.eq_frequency_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 18 > private
*/
CODEZ rsa306b_class::_ifstream_copy_eq_amplitude_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.eq_amplitude_v.resize(this->_vars.ifstream.eq_amplitude_v.size());
    this->vars.ifstream.eq_amplitude_v = this->_vars.ifstream.eq_amplitude_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 19 > private
*/
CODEZ rsa306b_class::_ifstream_copy_eq_phase_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.eq_phase_v.resize(this->_vars.ifstream.eq_phase_v.size());
    this->vars.ifstream.eq_phase_v = this->_vars.ifstream.eq_phase_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 20 > private
*/
CODEZ rsa306b_class::_ifstream_copy_scale_factor()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.scale_factor = this->_vars.ifstream.scale_factor;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 21 > private
*/
CODEZ rsa306b_class::_ifstream_copy_scale_frequency()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.scale_frequency = this->_vars.ifstream.scale_frequency;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 22 > private
*/
CODEZ rsa306b_class::_ifstream_copy_if_bandwidth_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.if_bandwidth_hz = this->_vars.ifstream.if_bandwidth_hz;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 23 > private
*/
CODEZ rsa306b_class::_ifstream_copy_samples_per_second()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.samples_per_second = this->_vars.ifstream.samples_per_second;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 24 > private
*/
CODEZ rsa306b_class::_ifstream_copy_if_center_frequency()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.if_center_frequency = this->_vars.ifstream.if_center_frequency;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 25 > private
*/
CODEZ rsa306b_class::_ifstream_copy_buffer_size_bytes()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.buffer_size_bytes = this->_vars.ifstream.buffer_size_bytes;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 26 > private
*/
CODEZ rsa306b_class::_ifstream_copy_buffer_samples()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.ifstream.buffer_samples = this->_vars.ifstream.buffer_samples;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 27> private
*/
CODEZ rsa306b_class::_ifstream_copy_acq_status_message()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    for (int ii = 0; ii < IFSTREAM_BITCHECKS; ii++)
    {
        strcpy(this->vars.ifstream.acq_status_messages[ii], this->_vars.ifstream.acq_status_messages[ii]);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_copy.cpp