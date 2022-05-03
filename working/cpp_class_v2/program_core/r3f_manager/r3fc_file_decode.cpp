/*
    basic member functions of "r3f_manager_class", 
    the file decoding capability

        public:
            < 1 >  file_decode()

        private:
            #  none
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    the input file is validated
    the output file is opened with force
    the size of the file is registered
    the start and stop byte indexes are validated
*/
void r3f_manager_class::file_decode
(                    
    const char* r3f_input_path_file_name,
    const char* decode_path_file_name, 
    long int decode_start_byte, 
    long int decode_stop_byte,
    bool print_while_decoding
) 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (decode_path_file_name == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate decoding output file\n");
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
    if (decode_start_byte < 0                    || 
        decode_start_byte > this->_bytes_in_file-2) 
    {
        decode_start_byte = 0;
    }
    if (decode_stop_byte < 0                  ||
        decode_stop_byte > this->_bytes_in_file) 
    {
        decode_stop_byte = this->_bytes_in_file;
    }
    if (decode_stop_byte <= decode_start_byte)
    {
        decode_start_byte = 0;
        decode_stop_byte = this->_bytes_in_file;
    }

    int8_t byte_getter;
    this->_fptr_decode = fopen(decode_path_file_name, "w");
    fseek(this->_fptr_read, 0L, SEEK_SET);
    if (print_while_decoding == true)
    {
        printf("\nmaking %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
            decode_path_file_name, decode_start_byte, decode_stop_byte-1);
    }
    fseek(this->_fptr_read, decode_start_byte, SEEK_CUR);
    for (long int ii = decode_start_byte; ii < decode_stop_byte; ii++)
    {
        fread(&byte_getter, sizeof(int8_t), 1, this->_fptr_read);
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
        fputs(this->_holder, this->_fptr_decode);
        if (print_while_decoding == true)
        {
            printf("%s", this->_holder);
        }
    }
    if (print_while_decoding == true)
    {
        printf("\n<<< end file decode >>>  check:  %s\n", decode_path_file_name);
    }
    fclose(this->_fptr_decode); this->_fptr_decode = NULL;
    fclose(this->_fptr_read); this->_fptr_read = NULL;
}


////////~~~~~~~~END>  r3fc_file_decode.cpp

        