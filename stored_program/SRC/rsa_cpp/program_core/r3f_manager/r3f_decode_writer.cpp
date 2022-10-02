/*
    basic member functions of "r3f_manager_class", 
    file decoding capability for printing

        public:
            < 1 >  decode_print()
            < 2 >  batch_decode_print()

        private:
            #  none
*/

#include "r3f_manager_class.h"


/*
    < 1 >
    for viewing a single file in stdout
*/
CODEZ r3f_manager_class::decode_write
(
    const char* r3f_file, 
    const char* decode_file,
    const long int start_byte, 
    const long int stop_byte
)
{
    return this->cutil.h_decode_write(r3f_file, decode_file, start_byte, stop_byte);
}


////~~~~


/*
    < 2 >
    for viewing all present files in stdout
*/
CODEZ r3f_manager_class::batch_decode_write
(
    const char* r3f_directory, 
    const char* decode_directory,
    const long int start_byte, 
    const long int stop_byte,
    std::vector<std::string>& in_filez,
    std::vector<std::string>& out_filez
)
{
    // load r3f files in the directory
    std::vector<std::string> originalz;
    std::vector<std::string> modifiedz;
    originalz.clear();
    modifiedz.clear();
    in_filez.clear();
    out_filez.clear();

    // get original r3f files, directory is included
    if (this->cutil.h_batch_match_extension(r3f_directory, "r3f", originalz, true) != CODEZ::_0_no_errors) 
    {
        return this->cutil.get_status_code();
    }
    if 
    (
        this->cutil.h_batch_redir_insert_ext_change(r3f_directory, "r3f", decode_directory, "_DECODED_", "txt", modifiedz) != 
        CODEZ::_0_no_errors
    )
    {
        return this->cutil.get_status_code();
    }
    if 
    (
        (originalz.size() < static_cast<std::size_t>(1)) ||
        (modifiedz.size() < static_cast<std::size_t>(1))
    )
    {
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    
    char temp_in[BUF_E];
    char temp_out[BUF_E];
    for (std::size_t ii = 0; ii < originalz.size(); ii++)
    {
        (void)strcpy(temp_in, originalz[ii].c_str());
        (void)strcpy(temp_out, modifiedz[ii].c_str());
        
        if (this->decode_write(temp_in, temp_out, start_byte, stop_byte) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
        in_filez.push_back(temp_in);
        out_filez.push_back(temp_out);
    }
    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_decode_writer.cpp
