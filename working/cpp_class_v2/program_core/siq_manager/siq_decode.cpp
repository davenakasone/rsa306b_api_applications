/*
    for loading *.siq file into class members

    public:
        < 1 >  decode_and_write()
        < 2 >  decode_and_print()

    private:
        #  none
*/

#include "siq_manager_class.h"


/*
    < 1 > public
*/
void siq_manager_class::decode_and_write
(
    char* input_file, 
    char* output_file, 
    unsigned long int byte_start, 
    unsigned long int byte_stop
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    this->_prepare_siq_input(input_file);
    if (this->_ec != no_error)
    {
        return;
    }
    this->_prepare_any_output(output_file);
    if (this->_ec != no_error)
    {
        return;
    }

    if (fseek(this->_fptr_read, 0L, SEEK_SET) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
        return;
    }

    if (byte_start < 0                    || 
        byte_start > this->_bytes_in_file-2) 
    {
        byte_start = 0;
    }
    if (byte_stop < 0                    ||
        byte_stop > this->_bytes_in_file-1) 
    {
        byte_stop = this->_bytes_in_file-1;
    }
    if (byte_stop <= byte_start)
    {
        byte_start = 0;
        byte_stop = this->_bytes_in_file-1;
    }

    int8_t byte_getter;
    snprintf(this->_holder, BUF_F-1, "\ndecoding %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
        input_file, 
        byte_start, 
        byte_stop);
    if (fputs(this->_holder, this->_fptr_write) < 0)
    {
        this->_set_error_code(fputs_failed_write);
    }
    if (fseek(this->_fptr_read, byte_start, SEEK_CUR) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
    }

    for (size_t ii = byte_start; ii <= byte_stop; ii++)
    {
        if (fread(&byte_getter, sizeof(int8_t), 1, this->_fptr_read) != 1)
        {
            this->_set_error_code(fread_failure);
        }
        this->_helper[0] = (char)byte_getter;
        switch (byte_getter)
        {
            case (0)    : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t\t\t\t[NULL]    %4d\n", ii, byte_getter);         break;
            case (10)   : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t\t\t\t[LF]      %4d\n", ii, byte_getter);         break;
            case (12)   : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t\t\t\t[FF]      %4d\n", ii, byte_getter);         break;
            case (13)   : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t\t\t\t[CR]      %4d\n", ii, byte_getter);         break;
            case (EOF)  : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t\t\t\t[EOF]     %4d\n", ii, byte_getter);         break;
            default     : snprintf(this->_holder, BUF_F-1, "<><><>%12ld)\t%c    %4d\n", ii, this->_helper[0], byte_getter); break;
        }
        if (fputs(this->_holder, this->_fptr_write) < 0)
        {
            this->_set_error_code(fputs_failed_write);
        }
    }
    snprintf(this->_holder, BUF_F-1, "\n<<< end file decode >>>\n");
    if (fputs(this->_holder, this->_fptr_write) < 0)
    {
        this->_set_error_code(fputs_failed_write);
    }
    this->_conclude_siq_input();
    this->_conclude_any_output();
}


////~~~~


/*
    < 2 > public
*/
void siq_manager_class::decode_and_print(char* input_file, unsigned long int byte_start, unsigned long int byte_stop)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_prepare_siq_input(input_file);
    if (this->_ec != no_error)
    {
        return;
    }

    if (fseek(this->_fptr_read, 0L, SEEK_SET) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
        return;
    }

    if (byte_start < 0                    || 
        byte_start > this->_bytes_in_file-2) 
    {
        byte_start = 0;
    }
    if (byte_stop < 0                    ||
        byte_stop > this->_bytes_in_file-1) 
    {
        byte_stop = this->_bytes_in_file-1;
    }
    if (byte_stop <= byte_start)
    {
        byte_start = 0;
        byte_stop = this->_bytes_in_file-1;
    }

    int8_t byte_getter;
    printf("\ndecoding %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
        input_file, 
        byte_start, 
        byte_stop);
    if (fseek(this->_fptr_read, byte_start, SEEK_CUR) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
    }

    for (size_t ii = byte_start; ii <= byte_stop; ii++)
    {
        if (fread(&byte_getter, sizeof(int8_t), 1, this->_fptr_read) != 1)
        {
            this->_set_error_code(fread_failure);
        }
        this->_helper[0] = (char)byte_getter;
        switch (byte_getter)
        {
            case (0)    : printf("<><><>%12ld)\t\t\t\t[NULL]    %4d\n", ii, byte_getter);         break;
            case (10)   : printf("<><><>%12ld)\t\t\t\t[LF]      %4d\n", ii, byte_getter);         break;
            case (12)   : printf("<><><>%12ld)\t\t\t\t[FF]      %4d\n", ii, byte_getter);         break;
            case (13)   : printf("<><><>%12ld)\t\t\t\t[CR]      %4d\n", ii, byte_getter);         break;
            case (EOF)  : printf("<><><>%12ld)\t\t\t\t[EOF]     %4d\n", ii, byte_getter);         break;
            default     : printf("<><><>%12ld)\t%c    %4d\n", ii, this->_helper[0], byte_getter); break;
        }
    }
    printf("\n<<< end file decode >>>\n");
    this->_conclude_siq_input();
}


////////~~~~~~~~END>  siq_decode.cpp
