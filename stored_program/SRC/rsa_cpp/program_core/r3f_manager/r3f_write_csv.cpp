/*
    "r3f_manager_class", CSV writing

        public:
            #  none

        private:
            < 1 >  _write_csv_adc()
            < 2 >  _write_csv_equalization()
*/

#include "r3f_manager_class.h"


/*
    < 1 > private
        if user selected "write_adc == true"
        when load_file() or batch_process_files() was called,
        then this function helps made the output file of ADC values over time
*/
CODEZ r3f_manager_class::_write_csv_adc()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }

    std::size_t v_size = this->_vars.v_adc.size();
    if (v_size < static_cast<std::size_t>(1))
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)sprintf(this->_helper, "%s,%s\n",
                  IFSTREAM_FIELD_ADC_1_OF_2,
                  IFSTREAM_FIELD_ADC_2_OF_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.9lf,%d\n",
                       static_cast<double>(idx) / this->_vars.fpga_sample_counter_ticks_per_second,
                       this->_vars.v_adc[idx]);
        (void)fputs(this->_helper, this->_fp_write);
    }

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}

////~~~~

/*
    < 2 > private
        if user selected "write_equalization == true"
        when load_file() or batch_process_files() was called,
        then this function helps made the output file for equalization values
*/
CODEZ r3f_manager_class::_write_csv_equalization()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }

    std::size_t v_size = this->_vars.v_eqaul[0].size();
    if (v_size < static_cast<std::size_t>(1))
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)sprintf(this->_helper, "%s, %s, %s\n",
                  IFSTREAM_FIELD_EQL_1_OF_3,
                  IFSTREAM_FIELD_EQL_2_OF_3,
                  IFSTREAM_FIELD_EQL_3_OF_3);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.9f,%0.9f,%0.9f\n",
                       this->_vars.v_eqaul[R3F_EQL_IDX_FREQ][idx],
                       this->_vars.v_eqaul[R3F_EQL_IDX_SCAL][idx],
                       this->_vars.v_eqaul[R3F_EQL_IDX_PHAS][idx]);
        (void)fputs(this->_helper, this->_fp_write);
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_write_csv.cpp
