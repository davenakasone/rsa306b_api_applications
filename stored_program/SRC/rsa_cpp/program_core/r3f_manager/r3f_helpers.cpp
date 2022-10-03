/*
    basic member functions of "r3f_manager_class", 
    file decoding capability for printing

        public:
            < 1 >  batch_load_file()

        private:
            < 1 >  _write_csv_adc()
            < 2 >  _write_csv_equalization()
*/

#include "r3f_manager_class.h"


/*
    < 1 > public
        for viewing a single file in stdout
*/
CODEZ r3f_manager_class::batch_process_files
(
    const char* r3f_input_directory,
    const char* output_directory,
    std::vector<std::string>& in_filez, 
    std::vector<std::string>& out_filez,
    bool write_parsed,
    bool write_equalization,
    bool write_adc
)
{
    // load r3f files in the directory
    std::vector<std::string> originalz;
    std::vector<std::string> parsedz;
    std::vector<std::string> equalz;
    std::vector<std::string> adcz;
    originalz.clear();
    parsedz.clear();
    equalz.clear();
    adcz.clear();
    in_filez.clear();
    out_filez.clear();

    if (this->cutil.h_batch_match_extension(r3f_input_directory, R3F_EXT, originalz, true) != CODEZ::_0_no_errors) 
    {
        return this->cutil.get_status_code();
    }
    if (write_parsed == true)
    {
        if 
        (
            this->cutil.h_batch_redir_insert_ext_change
            (
                r3f_input_directory, 
                R3F_EXT, 
                output_directory, 
                R3F_TAG_PAR,
                R3F_EXT_PAR,
                parsedz
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.get_status_code();
        }
    }
    if (write_equalization == true)
    {
        if 
        (
            this->cutil.h_batch_redir_insert_ext_change
            (
                r3f_input_directory, 
                R3F_EXT, 
                output_directory, 
                R3F_TAG_EQL,
                R3F_EXT_EQL,
                equalz
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.get_status_code();
        }
    }
    if (write_adc == true)
    {
        if 
        (
            this->cutil.h_batch_redir_insert_ext_change
            (
                r3f_input_directory, 
                R3F_EXT, 
                output_directory, 
                R3F_TAG_ADC,
                R3F_EXT_ADC,
                adcz
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.get_status_code();
        }
    }
    if ((originalz.size() < static_cast<std::size_t>(1)))
    {
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }

    char temp_r3f[BUF_E];       
    char temp_parsed[BUF_E];    
    char temp_eql[BUF_E];
    char temp_adc[BUF_E];
    (void)memset(temp_r3f   , '\0', sizeof(temp_r3f)   );
    (void)memset(temp_parsed, '\0', sizeof(temp_parsed));
    (void)memset(temp_eql   , '\0', sizeof(temp_eql)   );
    (void)memset(temp_adc   , '\0', sizeof(temp_adc)   );

    for (std::size_t ii = 0; ii < originalz.size(); ii++)
    {
        (void)strcpy(temp_r3f, originalz[ii].c_str());
        if (write_parsed == true)
        {
            (void)strcpy(temp_parsed, parsedz[ii].c_str());
        }
        if (write_equalization == true)
        {
            (void)strcpy(temp_eql, equalz[ii].c_str());
        }
        if (write_adc == true)
        {
            (void)strcpy(temp_adc, adcz[ii].c_str());
        }

        if 
        (
            this->load_file
            (
                temp_r3f, 
                temp_parsed, 
                temp_adc, 
                temp_eql,
                write_parsed,
                write_equalization,
                write_adc
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }

        in_filez.push_back(temp_r3f);
        if(write_parsed == true)
        {
            out_filez.push_back(temp_parsed);
        }
        if (write_equalization == true)
        {
            out_filez.push_back(temp_eql);
        }
        if (write_adc == true)
        {
            out_filez.push_back(temp_adc);
        }
    }


    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 1 > private
        for viewing all present files in stdout
*/
CODEZ r3f_manager_class::_write_csv_adc()
{
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
        IFSTREAM_FIELD_1,
        IFSTREAM_FIELD_2);
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
        for viewing all present files in stdout
*/
CODEZ r3f_manager_class::_write_csv_equalization()
{
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
        R3F_FIELD_3,
        R3F_FIELD_4,
        R3F_FIELD_5);
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


////////~~~~~~~~END>  r3f_helpers.cpp
