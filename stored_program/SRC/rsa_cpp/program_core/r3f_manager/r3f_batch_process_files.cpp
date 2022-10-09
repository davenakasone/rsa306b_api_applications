/*
    "r3f_manager_class", batch processing

        public:
            < 1 >  batch_load_file()

        private:
            #  none
*/

#include "r3f_manager_class.h"

/*
    < 1 > public
        finds "*.r3f" files in specified directory, produces output selected
        not good for loading an indivdual file, only last file will be loaded into the members
        very good for processing every "*.r3f" file in a directory

        * processed files take default values, see "constant_expression.h"
*/
CODEZ r3f_manager_class:: batch_process_files
(
    const char* r3f_input_directory,
    const char* output_directory,
    std::vector<std::string>& input_files_v, 
    std::vector<std::string>& output_files_v,
    bool write_parsed,
    bool write_equalization,
    bool write_adc
)
{
    // these data structures help manage the files while processing
    std::vector<std::string> parsedz;
    std::vector<std::string> equalz;
    std::vector<std::string> adcz;
    parsedz.clear();
    equalz.clear();
    adcz.clear();

    input_files_v.clear();  // the user's input file vector is reset
    output_files_v.clear(); // the user's output file vector is reset

    // see if there any "*.r3f" files in the specified directory
    if 
    (
        this->cutil.find_files_with_extension
        (
            r3f_input_directory, 
            R3F_RAW_EXT, 
            input_files_v, 
            true
        ) != CODEZ::_0_no_errors
    )
    {
        return this->cutil.get_status_code();
    }
    if ((input_files_v.size() < static_cast<std::size_t>(1)))
    {
        return this->cutil.report_status_code(CODEZ::_19_result_not_found);    // no "*.r3f" files were found
    }

    // if parsed output is needed, then prepare the output files
    if (write_parsed == true)
    {
        if 
        (
            this->cutil.batch_switch_directory_insert_and_change_extension
            (
                r3f_input_directory,
                R3F_RAW_EXT,
                output_directory,
                TAG_PARSED,
                EXT_PARSED,
                parsedz
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.get_status_code();
        }
    }

    // if equalization output is needed, then prepare the output files
    if (write_equalization == true)
    {
        if 
        (
            this->cutil.batch_switch_directory_insert_and_change_extension
            (
                r3f_input_directory,
                R3F_RAW_EXT,
                output_directory,
                IFSTREAM_TAG_EQL,
                DATA_DEFAULT_EXT,
                equalz) != CODEZ::_0_no_errors
            )
        {
            return this->cutil.get_status_code();
        }
    }

    // if ADC output is needed, prepare the output files
    if (write_adc == true)
    {
        if 
        (
            this->cutil.batch_switch_directory_insert_and_change_extension
            (
                r3f_input_directory,
                R3F_RAW_EXT,
                output_directory,
                IFSTREAM_TAG_ADC,
                DATA_DEFAULT_EXT,
                adcz
            ) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
    }

    // check the results
    if 
    (
        ((write_parsed       == true) && (parsedz.size() != input_files_v.size())) ||
        ((write_equalization == true) && (equalz.size()  != input_files_v.size())) ||
        ((write_adc          == true) && (adcz.size()    != input_files_v.size()))
    )
    {
        return this->cutil.report_status_code(CODEZ::_2_error_in_logic);
    }

    char temp_r3f[BUF_E];
    char temp_parsed[BUF_E];
    char temp_eql[BUF_E];
    char temp_adc[BUF_E];
    (void)memset(temp_r3f, '\0', sizeof(temp_r3f));
    (void)memset(temp_parsed, '\0', sizeof(temp_parsed));
    (void)memset(temp_eql, '\0', sizeof(temp_eql));
    (void)memset(temp_adc, '\0', sizeof(temp_adc));

    for (std::size_t ii = 0; ii < input_files_v.size(); ii++)
    {
        (void)strncpy(temp_r3f, input_files_v[ii].c_str(), sizeof(temp_r3f));
        if (write_parsed == true)
        {
            (void)strncpy(temp_parsed, parsedz[ii].c_str(), sizeof(temp_parsed));
        }
        if (write_equalization == true)
        {
            (void)strncpy(temp_eql, equalz[ii].c_str(), sizeof(temp_eql));
        }
        if (write_adc == true)
        {
            (void)strncpy(temp_adc, adcz[ii].c_str(), sizeof(temp_adc));
        }

        // each "*.r3f" file is loaded, output is produced according to bools
        if 
        (
            this->load_file
            (
                temp_r3f,
                temp_parsed,
                temp_eql,
                temp_adc,
                write_parsed,
                write_equalization,
                write_adc
            ) != CODEZ::_0_no_errors
        )
        {
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }

        // provide user with input files processed and outputs that were produced
        if (write_parsed == true)
        {
            output_files_v.push_back(temp_parsed);
        }
        if (write_equalization == true)
        {
            output_files_v.push_back(temp_eql);
        }
        if (write_adc == true)
        {
            output_files_v.push_back(temp_adc);
        }
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_batch_process_files.cpp
