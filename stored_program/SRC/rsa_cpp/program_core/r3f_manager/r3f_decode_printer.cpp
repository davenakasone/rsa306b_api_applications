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
CODEZ r3f_manager_class::decode_print
(
    const char* r3f_file, 
    const long int start_byte, 
    const long int stop_byte
)
{
    return this->cutil.h_decode_print(r3f_file, start_byte, stop_byte);
}


////~~~~


/*
    < 2 >
    for viewing all present files in stdout
*/
CODEZ r3f_manager_class::batch_decode_print
(
    const char* r3f_directory, 
    const long int start_byte, 
    const long int stop_byte,
    std::vector<std::string>& filez
)
{
    filez.clear();

    // load r3f files in the directory
    if (this->cutil.h_batch_match_extension(r3f_directory, "r3f", filez, true) != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    if (filez.size() < static_cast<std::size_t>(1))
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    char temp[BUF_E];
    for (std::size_t ii = 0; ii < filez.size(); ii++)
    {
        printf("\nfile %lu of %lu\n", ii+1, filez.size());
        (void)strcpy(temp, filez[ii].c_str());
        if (this->decode_print(temp, start_byte, stop_byte) != CODEZ::_0_no_errors)
        {
            return this->cutil.get_status_code();
        }
        if (ii < filez.size()-1)
        {
            printf("\n\tany key for next file:  ");
            std::cin >> this->cutil.helper;
        }
    }
    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_decode_printer.cpp
