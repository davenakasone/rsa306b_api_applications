/*
    API group "DPX", the private copiers

    public :
        #  none
    
    private :
        < 1  >  _dpx_copy_vars()
        < 2  >  _dpx_copy_is_enabled()
        < 3  >  _dpx_copy_acq_status_messages()
        < 4  >  _dpx_copy_spectrum_bitmap_v()
        < 5  >  _dpx_copy_spectrum_traces_v()
        < 6  >  _dpx_copy_sogram_bitmap_v()
        < 7  >  _dpx_copy_sogram_bitmap_timestamp_v()
        < 8  >  _dpx_copy_sogram_bitmap_trigger_v()
        < 9  >  _dpx_copy_frame_buffer_type()
        < 10 >  _dpx_copy_frequency_span_hz()
        < 11 >  _dpx_copy_rbw_min_hz()
        < 12 >  _dpx_copy_rbw_max_hz()
        < 13 >  _dpx_copy_settings_type()
        < 15 >  _dpx_copy_line_data_v()
        < 16 >  _dpx_copy_line_data_elements()
        < 17 >  _dpx_copy_line_index()
        < 18 >  _dpx_copy_line_data_scaling_factor()
        < 19 >  _dpx_copy_trace_points()
        < 20 >  _dpx_copy_first_valid_point()
        < 21 >  _dpx_copy_line_count()
        < 22 >  _dpx_copy_line_timestamp()
        < 23 >  _dpx_copy_was_triggered()
        < 24 >  _dpx_copy_sogram_settings_type()
        < 25 >  _dpx_copy_frame_available()
        < 26 >  _dpx_copy_trace_points_per_pixel()
        < 27 >  _dpx_copy_trace_points_total()
        < 28 >  _dpx_copy_vertical_unit_select()
        < 29 >  _dpx_copy_y_top()
        < 30 >  _dpx_copy_y_bottom()
        < 31 >  _dpx_copy_infinite_persistence()
        < 32 >  _dpx_copy_persistence_time_seconds()
        < 33 >  _dpx_copy_show_only_trigger_frame()
        < 34 >  _dpx_copy_time_per_bitmap_line_seconds()
        < 35 >  _dpx_copy_time_resolution_seconds()
        < 36 >  _dpx_copy_power_min()
        < 37 >  _dpx_copy_power_max()
        < 38 >  _dpx_copy_spectrogram_trace_type_select()
        < 39 >  _dpx_copy_spectrum_traces()
        < 40 >  _dpx_copy_spectrum_trace_type_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_dpx_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 38;
    CODEZ caught_call[callz];

    caught_call[0]  = this->_dpx_copy_is_enabled();
    caught_call[1]  = this->_dpx_copy_acq_status_messages();
    caught_call[2]  = this->_dpx_copy_spectrum_bitmap_v();
    caught_call[3]  = this->_dpx_copy_spectrum_traces_v();
    caught_call[4]  = this->_dpx_copy_sogram_bitmap_v();
    caught_call[5]  = this->_dpx_copy_sogram_bitmap_timestamp_v();
    caught_call[6]  = this->_dpx_copy_sogram_bitmap_trigger_v();
    caught_call[7]  = this->_dpx_copy_frame_buffer_type();
    caught_call[8]  = this->_dpx_copy_frequency_span_hz();
    caught_call[9]  = this->_dpx_copy_rbw_min_hz();
    caught_call[10] = this->_dpx_copy_rbw_max_hz();
    caught_call[11] = this->_dpx_copy_settings_type();
    caught_call[12] = this->_dpx_copy_line_data_v();
    caught_call[13] = this->_dpx_copy_line_data_elements();
    caught_call[14] = this->_dpx_copy_line_index();
    caught_call[15] = this->_dpx_copy_line_data_scaling_factor();
    caught_call[16] = this->_dpx_copy_trace_points();
    caught_call[17] = this->_dpx_copy_first_valid_point();
    caught_call[18] = this->_dpx_copy_line_count();
    caught_call[19] = this->_dpx_copy_line_timestamp();
    caught_call[20] = this->_dpx_copy_was_triggered();
    caught_call[21] = this->_dpx_copy_sogram_settings_type();
    caught_call[22] = this->_dpx_copy_frame_available();
    caught_call[23] = this->_dpx_copy_trace_points_per_pixel();
    caught_call[24] = this->_dpx_copy_trace_points_total();
    caught_call[25] = this->_dpx_copy_vertical_unit_select();
    caught_call[26] = this->_dpx_copy_y_top();
    caught_call[27] = this->_dpx_copy_y_bottom();
    caught_call[28] = this->_dpx_copy_infinite_persistence();
    caught_call[29] = this->_dpx_copy_persistence_time_seconds();
    caught_call[30] = this->_dpx_copy_show_only_trigger_frame();
    caught_call[31] = this->_dpx_copy_time_per_bitmap_line_seconds();
    caught_call[32] = this->_dpx_copy_time_resolution_seconds();
    caught_call[33] = this->_dpx_copy_power_min();
    caught_call[34] = this->_dpx_copy_power_max();
    caught_call[35] = this->_dpx_copy_spectrogram_trace_type_select();
    caught_call[36] = this->_dpx_copy_spectrum_traces();
    caught_call[37] = this->_dpx_copy_spectrum_trace_type_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_dpx_copy_is_enabled()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_vars.dpx.is_enabled = this->_vars.dpx.is_enabled;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_dpx_copy_acq_status_messages()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    for (int ii = 0; ii < DPX_BITCHECKS; ii++)
    {
        strcpy(this->vars.dpx.acq_status_messages[ii], this->_vars.dpx.acq_status_messages[ii]);
    }
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_dpx_copy_spectrum_bitmap_v()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.dpx.spectrum_bitmap_v.clear();
    this->vars.dpx.spectrum_bitmap_v.resize(this->_vars.dpx.spectrum_bitmap_v.size());
    for (std::size_t ii = 0; ii < this->_vars.dpx.spectrum_bitmap_v.size(); ii++)
    {
        this->vars.dpx.spectrum_bitmap_v[ii].clear();
        this->vars.dpx.spectrum_bitmap_v[ii].resize(this->_vars.dpx.spectrum_bitmap_v[ii].size());
    }
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_dpx_copy_spectrum_traces_v()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.dpx.spectrum_traces_v.clear();
    
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_dpx_copy.cpp
















////~~~~


/*
    <  > private
*/
CODEZ rsa306b_class::
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    
    return cutil.report_status_code(CODEZ::_0_no_errors);
}