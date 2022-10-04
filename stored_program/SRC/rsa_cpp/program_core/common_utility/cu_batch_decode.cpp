/*
    class common_utility, batch decoders

        public:
            < 1 >  batch_decode_print()
            < 2 >  batch_decode_write()

        private:
            #  none
*/

#include "common_utility.h"


/*
    < 1 >
    finds all files with specified extension in directory of interest
    each file is decoded to stdout
    specified byte range is obeyed if possible, but subject to change
    all files found and printed are recorded into "found_files_v"
    best for "*.siq" and "*.r3f" files
*/
CODEZ common_utility::batch_decode_print
(
    const char* raw_directory,
    const char* raw_extension, 
    const long int start_byte, 
    const long int stop_byte, 
    std::vector<std::string>& raw_files_v
)
{
    raw_files_v.clear();

    // see if raw files with specified extension are in the directory
    if
    (
        this->find_files_with_extension
        (
            raw_directory, 
            raw_extension, 
            raw_files_v, 
            true
            ) != CODEZ::_0_no_errors
    )
    {
        return this->get_status_code();
    }
    if (raw_files_v.size() < static_cast<std::size_t>(1))
    {
        return this->report_status_code(CODEZ::_19_result_not_found);
    }

    char temp_raw[BUF_E];
    for (std::size_t ii = 0; ii < raw_files_v.size(); ii++)
    {
        printf("\nfile %lu of %lu\n", ii+1, raw_files_v.size());
        (void)strncpy(temp_raw, raw_files_v[ii].c_str(), sizeof(temp_raw));
        if 
        (
            this->decode_print
            (
                temp_raw, 
                start_byte, 
                stop_byte
            ) != CODEZ::_0_no_errors
        )
        {
            return this->get_status_code();
        }

        if (ii < raw_files_v.size()-1)
        {
            printf("\n\tany key for next file:  ");
            std::cin >> this->_worker;
        }
    }
    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 2 >
    finds all files with specified extension in directory of interest
    each file is decoded and output is written to selected directory with specified extension
    output file names are exactly the same as the raw file that was decoded
    specified byte range is obeyed if possible, but subject to change
    all found input file-path-names are populated into "raw_files_v"
    all produced output file-path-names are populated into "decoded_files_v"
    best for "*.siq" and "*.r3f" files
*/
CODEZ common_utility::batch_decode_write
(
    const char* raw_directory,
    const char* raw_extension, 
    const char* decoded_directory,
    const char* decoded_insert,
    const char* decoded_extenstion,
    const long int start_byte, 
    const long int stop_byte, 
    std::vector<std::string>& raw_files_v, 
    std::vector<std::string>& decoded_files_v
)
{
    raw_files_v.clear();
    decoded_files_v.clear();

    // get raw files, directory is included
    if 
    (
        this->find_files_with_extension    // with full file-path-name
        (
            raw_directory, 
            raw_extension, 
            raw_files_v, 
            true
            ) != CODEZ::_0_no_errors
    ) 
    {
        return this->get_status_code();    // no files were found
    }
    if (raw_files_v.size() < static_cast<std::size_t>(1))
    {
        return this->report_status_code(CODEZ::_19_result_not_found);    // no raw files were found
    }
    
    // prepare the decoded files
    if 
    (
        this->h_batch_redir_insert_ext_change
        (
            raw_directory, 
            raw_extension, 
            decoded_directory, 
            decoded_insert, 
            decoded_extenstion, 
            decoded_files_v
        ) != CODEZ::_0_no_errors
    )
    {
        return this->get_status_code();
    }
    if (raw_files_v.size() != decoded_files_v.size())
    {
        return this->report_status_code(CODEZ::_9_function_call_failed);    // mismatch
    }
    
    char temp_raw[BUF_E];
    char temp_decoded[BUF_E];
    for (std::size_t ii = 0; ii < raw_files_v.size(); ii++)
    {
        (void)strcpy(temp_raw, raw_files_v[ii].c_str());
        (void)strcpy(temp_decoded, decoded_files_v[ii].c_str());
        
        if 
        (
            this->decode_write
            (
                temp_raw, 
                temp_decoded, 
                start_byte, 
                stop_byte
            ) != CODEZ::_0_no_errors)
        {
            return this->get_status_code();
        }
    }
    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_batch_decode.cpp
