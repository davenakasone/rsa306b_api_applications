/*
    "siq_manager_class", batch processing

        public:
            < 1 >  batch_load_file()

        private:
            #  none
*/

#include "siq_manager_class.h"

/*
    < 1 > public
        finds "*.siq" files in specified directory, produces output selected
        not good for loading an indivdual file, only last file will be loaded into the members
        very good for processing every "*.siq" file in a directory

        * processed files take default values, see "constant_expression.h"
*/
CODEZ siq_manager_class::batch_process_files
(
    const char* siq_input_directory,
    const char* output_directory,
    std::vector<std::string>& input_files_v, 
    std::vector<std::string>& output_files_v,
    bool write_parsed,
    bool write_iq
)
{
    std::vector<std::string> parsedz;
    std::vector<std::string> iqz;
    parsedz.clear();
    iqz.clear();

    input_files_v.clear();     // the user's input file vector is reset
    output_files_v.clear();    // the user's output file vector is reset

    // see if there any "*.r3f" files in the specified directory
    if 
    (
        this->cutil.find_files_with_extension
        (
            siq_input_directory, 
            SIQ_RAW_EXT, 
            input_files_v, 
            true
        ) != CODEZ::_0_no_errors
    )
    {
        return this->cutil.get_status_code();
    }
    if ((input_files_v.size() < static_cast<std::size_t>(1)))
    {
        return this->cutil.report_status_code(CODEZ::_19_result_not_found);    // no "*.siq" files were found
    }

    // if parsed output is needed, then prepare the output files
    if (write_parsed == true)
    {
        if 
        (
            this->cutil.h_batch_redir_insert_ext_change
            (
                siq_input_directory,
                SIQ_RAW_EXT,
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

    // if IQ output is needed, then prepare the output files
    if (write_iq == true)
    {
        if 
        (
            this->cutil.h_batch_redir_insert_ext_change
            (
                siq_input_directory,
                SIQ_RAW_EXT,
                output_directory,
                SIQ_TAG_IQ,
                DATA_DEFAULT_EXT,
                iqz
            ) != CODEZ::_0_no_errors
            )
        {
            return this->cutil.get_status_code();
        }
    }

    // check the results
    if 
    (
        ((write_parsed == true) && (parsedz.size() != input_files_v.size())) ||
        ((write_iq     == true) && (iqz.size()     != input_files_v.size()))
    )
    {
        return this->cutil.report_status_code(CODEZ::_2_error_in_logic);
    }

    char temp_siq[BUF_E];
    char temp_parsed[BUF_E];
    char temp_iq[BUF_E];
    (void)memset(temp_siq, '\0', sizeof(temp_siq));
    (void)memset(temp_parsed, '\0', sizeof(temp_parsed));
    (void)memset(temp_iq, '\0', sizeof(temp_iq));

    for (std::size_t ii = 0; ii < input_files_v.size(); ii++)
    {
        (void)strncpy(temp_siq, input_files_v[ii].c_str(), sizeof(temp_siq));
        if (write_parsed == true)
        {
            (void)strncpy(temp_parsed, parsedz[ii].c_str(), sizeof(temp_parsed));
        }
        if (write_iq == true)
        {
            (void)strncpy(temp_iq, iqz[ii].c_str(), sizeof(temp_iq));
        }

        // each "*.siq" file is loaded, output is produced according to bools
        if 
        (
            this->load_file
            (
                temp_siq,
                temp_parsed,
                temp_iq,
                write_parsed,
                write_iq
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
        if (write_iq == true)
        {
            output_files_v.push_back(temp_iq);
        }
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  siq_batch_process_files.cpp
