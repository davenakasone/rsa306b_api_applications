/*
    common funtions of the 'siq_handler_class'

    public:
        < 1 >  siq_handler_class()
        < 2 >  ~siq_handler_class()
        < 3 >  unload_and_clear()
        < 4 >  get_file_byte_length()

    private:
        < 1 >  _verify_siq_extension()
        < 2 >  _prepare_siq_input()
        < 3 >  _conclude_siq_input()
        < 4 >  _prepare_any_output()
        < 5 >  _conclude_any_output()
*/

#include "siq_manager_class.h"

/*
    < 1 > public
    constructor
*/
siq_manager_class::siq_manager_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record();
#endif

    this->_init();
}


////~~~~


/*
    < 2 > public
    destructor
*/
siq_manager_class::~siq_manager_class()
{
#ifdef DEBUG_CLI
    if (X_dfp != NULL)
    {
        snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
            __LINE__, __FILE__, __func__);
        debug_record();
    }
#endif

    this->_init();

#ifdef DE_BUG
    debug_stop();
#endif
}


////~~~~


/*
    < 3 > public
    clear the instance
*/
void siq_manager_class::unload_and_clear()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif    

    this->_init();
}


////~~~~


/*
    < 4 > public
    finds the file size, any file, as long as file pointer is available
*/
unsigned long int  siq_manager_class::get_file_byte_length
(
    char* input_file
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif    

    if (input_file == NULL)
    {
        this->_set_error_code(empty_string);
        return INIT_INT;
    }
    if (this->_fptr_read != NULL)
    {
        this->_set_error_code(fptr_read_busy);
        return INIT_INT;
    }
    this->_fptr_read = fopen(input_file, "r");
    if (this->_fptr_read == NULL)
    {
        this->_set_error_code(input_file_not_found);
        return INIT_INT;
    }
    if (fseek(this->_fptr_read, 0L, SEEK_END) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
    }
    
    this->_bytes_in_file = ftell(this->_fptr_read);
    
    if (fclose(this->_fptr_read) != 0)
    {
        this->_set_error_code(fclose_returned_non_zero);
    }
    this->_fptr_read = NULL;
    this->_set_error_code(no_error);
    return this->_bytes_in_file;
}


////~~~~


/*
    < 1 > private
    confirms that a valid *.siq extension is provided
*/
void siq_manager_class::_verify_siq_extension
(
    const char* input_file
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (input_file == NULL)
    {
        this->_set_error_code(empty_string);
        return;
    }
    size_t string_length = strlen(input_file);
    if (string_length < 6)
    {
        this->_set_error_code(input_file_bad);
        return;
    }

    char compare_to[5]; memset(compare_to, '\0', 5);
    compare_to[0] = input_file[string_length-4];
    compare_to[1] = input_file[string_length-3];
    compare_to[2] = input_file[string_length-2];
    compare_to[3] = input_file[string_length-1];
    if (strcmp(compare_to, ".siq") != 0)
    {
        this->_set_error_code(invalid_siq_file);
        return;
    }
    this->_set_error_code(no_error);
}


////~~~~


/*
    < 2 > private
    verifys ".siq" extenstion
    gets bytes in file, ensuring enough bytes exist
    the file is opened for reading if successful
*/
void siq_manager_class::_prepare_siq_input
(
    char* input_file
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_verify_siq_extension(input_file);
    if (this->_ec != no_error)
    {
        return;
    }
    this->get_file_byte_length(input_file);
    if (this->_ec != no_error)
    {
        return;
    }
    if (this->_bytes_in_file < 1000)
    {
        this->_set_error_code(low_bytes_in_siq_file);
        return;
    }
    if (this->_fptr_read != NULL)
    {
        this->_set_error_code(fptr_read_busy);
        return;
    }
    this->_fptr_read = fopen(input_file, "r");
    if (this->_fptr_read == NULL)
    {
        this->_set_error_code(input_file_not_found);
        return;
    }
    this->_set_error_code(no_error);
}


////~~~~


/*
    < 3 > private
    closes the "*.siq" file when reading is complete
*/
void siq_manager_class::_conclude_siq_input()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_fptr_read == NULL)
    {
        this->_set_error_code(input_file_not_found);
        return;
    }
    if (fclose(this->_fptr_read) != 0)
    {
        this->_set_error_code(fclose_returned_non_zero);
        return;
    }
    this->_fptr_read = NULL;
    this->_set_error_code(no_error);
}


////~~~~


/*
    < 4 > private
    attempts to open and over-write given output file
*/
void siq_manager_class::_prepare_any_output
(
    char* output_file
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_fptr_write = fopen(output_file, "w");
    if (this->_fptr_write == NULL)
    {
        this->_set_error_code(out_file_not_open);
        return;
    }
    this->_set_error_code(no_error);
}



////~~~~


/*
    < 5 > private
    closes the "*.siq" file when reading is complete
*/
void siq_manager_class::_conclude_any_output()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_fptr_write == NULL)
    {
        this->_set_error_code(out_file_not_open);
        return;
    }
    if (fclose(this->_fptr_write) != 0)
    {
        this->_set_error_code(fclose_returned_non_zero);
        return;
    }
    this->_fptr_write = NULL;
    this->_set_error_code(no_error);
}


////////~~~~~~~~END>  siq_common.cpp
