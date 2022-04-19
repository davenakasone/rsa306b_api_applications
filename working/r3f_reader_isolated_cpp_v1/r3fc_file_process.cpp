/*
    basic member functions of "r3f_manager_class",
    the file processing capability

        public:
            < 1 >  file_process()

        private:
            < 1 >  _process_header()
            < 2 >  _process_data()
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    the input file is validated
    the output file is opened with force
    the size of the file is registered
    processing occurs for every byte in the file
*/
void r3f_manager_class::file_process
(
    const char* r3f_input_path_file_name,
    const char* r3f_output_path_file_name,
    bool print_while_processing
) 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (r3f_output_path_file_name == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the output file\n");
        #endif
        return;
    }
    this->_return_status = this->_verify_r3f_extension(r3f_input_path_file_name);
    if (this->_return_status != _CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tbad input specification\n");
        #endif
        return;
    }
    this->_return_status = this->_find_input_file_size();
    if (this->_return_status != _CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tbad file size\n");
        #endif
        return;
    }
    
    this->_fptr_write = fopen(r3f_output_path_file_name, "w");
    fseek(this->_fptr_read, 0L, SEEK_SET);
    if (print_while_processing == true)
    {
        printf("\nmaking %s  ,  total bytes:  %ld\n<<< begin file processing >>>\n\n",
            r3f_output_path_file_name, this->_bytes_in_file);
    }

    this->_process_header();
    this->_process_data();    

    if (print_while_processing == true)
    {
        printf("\n<<< end file processing >>>  check:  %s\n", r3f_output_path_file_name);
    }
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    fclose(this->_fptr_read); this->_fptr_read = NULL;
}



////~~~~


/*
    private < 1 >
    the header information is needed first
    this 16 kB block determines how to get the rest of the data
*/
void r3f_manager_class::_process_header()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    sprintf(_holder, "UN\n");
    fputs(_holder, _fptr_write);
}


////~~~~


/*
    private < 2 >
    use the header information to get the data
*/
void r3f_manager_class::_process_data()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    sprintf(_holder, "LV\n");
    fputs(_holder, _fptr_write);
}


////////~~~~~~~~END>  r3fc_file_process.cpp

        