/*
    common_utility, class 

    public :
        < 1 >  h_decode_print()
        < 2 >  h_decode_write()

    private :
        #  none
*/

#include "common_utility.h"


static void get_byte(const int8_t byte, char* bstr, long int& idx);    // for local assistance


/*
    < 1 > public
    "r3f" or "siq" 
*/
CODEZ common_utility::h_decode_print
(
    const char* file_path_name, 
    long int start_byte, 
    long int stop_byte
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    FILE* fp = NULL;
    long bytes_in_file = 0;
    int8_t bget = 0;

    if (this->h_find_bytes_in_file(file_path_name, bytes_in_file) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }

    fp = fopen(file_path_name, "r");                               
    if (fp == NULL)
    {
        return this->report_status_code(CODEZ::_13_fopen_failed);
    }

    if (start_byte < 0             || 
        start_byte > bytes_in_file-2) 
    {
        start_byte = 0;
    }
    if (stop_byte < 0           ||
        stop_byte > bytes_in_file) 
    {
        stop_byte = bytes_in_file;
    }
    if (stop_byte <= start_byte)
    {
        start_byte = 0;
        stop_byte = bytes_in_file;
    }

    if (fseek(fp, 0L, SEEK_SET) != 0)                                 
    {
        if (fclose(fp) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp = NULL;
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }
    if (fseek(fp, start_byte, SEEK_CUR) != 0)                               
    {
        if (fclose(fp) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp = NULL;
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }

    printf("\nmaking %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
            file_path_name, start_byte, stop_byte);

    for (long int ii = start_byte; ii <= stop_byte; ii++)
    {
        if (fread(&bget, sizeof(int8_t), 1, fp) != 1)
        {
            if (fclose(fp) != 0)                                         
            {
                return this->report_status_code(CODEZ::_10_fclose_failed);
            }
            fp = NULL;
            return this->report_status_code(CODEZ::_20_fread_failed);
        }
        get_byte(bget, this->_worker, ii);
        (void)printf("%s", this->_worker);
    }
    if (fclose(fp) != 0)                                         
    {
        return this->report_status_code(CODEZ::_10_fclose_failed);
    }
    fp = NULL;

    (void)printf("\n<<< end file decode >>>\n");
    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > public
    "r3f" or "siq" 
*/
CODEZ common_utility::h_decode_write
(
    const char* raw_file, 
    const char* output_file, 
    long int& start_byte, 
    long int& stop_byte
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    FILE* fp_w = NULL;
    FILE* fp_r = NULL;
    long bytes_in_file = 0;
    int8_t bget = 0;

    if (this->h_find_bytes_in_file(raw_file, bytes_in_file) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    fp_r = fopen(raw_file, "r");                               
    if (fp_r == NULL)
    {
        return this->report_status_code(CODEZ::_13_fopen_failed);
    }
    fp_w = fopen(output_file, "w");                               
    if (fp_w == NULL)
    {
        return this->report_status_code(CODEZ::_13_fopen_failed);
    }

    if (start_byte < 0L            || 
        start_byte > bytes_in_file-2) 
    {
        start_byte = 0L;
    }
    if (stop_byte < 0L          ||
        stop_byte > bytes_in_file) 
    {
        stop_byte = bytes_in_file;
    }
    if (stop_byte <= start_byte)
    {
        start_byte = 0L;
        stop_byte = bytes_in_file;
    }

    if (fseek(fp_r, 0L, SEEK_SET) != 0)                                 
    {
        if (fclose(fp_r) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_r = NULL;
        if (fclose(fp_w) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_w = NULL;
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }
    if (fseek(fp_r, start_byte, SEEK_CUR) != 0)                               
    {
        if (fclose(fp_r) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_r = NULL;
        if (fclose(fp_w) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_w = NULL;
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }

    (void)sprintf(this->_worker, "\nmaking %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
            raw_file, 
            start_byte, 
            stop_byte);
    (void)fputs(this->_worker, fp_w);
    for (long int ii = start_byte; ii <= stop_byte; ii++)
    {
        if (fread(&bget, sizeof(int8_t), 1, fp_r) != 1)
        {
            if (fclose(fp_r) != 0)                                         
            {
                return this->report_status_code(CODEZ::_10_fclose_failed);
            }
            fp_r = NULL;
            if (fclose(fp_w) != 0)                                         
            {
                return this->report_status_code(CODEZ::_10_fclose_failed);
            }
            fp_w = NULL;
            return this->report_status_code(CODEZ::_20_fread_failed);
        }
        get_byte(bget, this->_worker, ii);
        if (fputs(this->_worker, fp_w) < 0)
        {
            if (fclose(fp_r) != 0)                                         
            {
                return this->report_status_code(CODEZ::_10_fclose_failed);
            }
            fp_r = NULL;
            if (fclose(fp_w) != 0)                                         
            {
                return this->report_status_code(CODEZ::_10_fclose_failed);
            }
            fp_w = NULL;
            return this->report_status_code(CODEZ::_31_fputs_failed);
        }
    }
    (void)sprintf(this->_worker, "\n<<< end file decode >>>\n");
    if (fputs(this->_worker, fp_w) < 0)
    {
        if (fclose(fp_r) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_r = NULL;
        if (fclose(fp_w) != 0)                                         
        {
            return this->report_status_code(CODEZ::_10_fclose_failed);
        }
        fp_w = NULL;
        return this->report_status_code(CODEZ::_31_fputs_failed);
    }

    if (fclose(fp_r) != 0)                                         
    {
        return this->report_status_code(CODEZ::_10_fclose_failed);
    }
    fp_r = NULL;
    if (fclose(fp_w) != 0)                                         
    {
        return this->report_status_code(CODEZ::_10_fclose_failed);
    }
    fp_w = NULL;
    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


static void get_byte(const int8_t byte, char* bstr, long int& idx)
{
    switch (byte)
    {
        case (0)    : (void)sprintf(bstr, "<><><>%12ld)\t\t\t\t[NULL]    %4d\n", idx, byte)               ; break;
        case (10)   : (void)sprintf(bstr, "<><><>%12ld)\t\t\t\t[LF]      %4d\n", idx, byte)               ; break;
        case (12)   : (void)sprintf(bstr, "<><><>%12ld)\t\t\t\t[FF]      %4d\n", idx, byte)               ; break;
        case (13)   : (void)sprintf(bstr, "<><><>%12ld)\t\t\t\t[CR]      %4d\n", idx, byte)               ; break;
        case (EOF)  : (void)sprintf(bstr, "<><><>%12ld)\t\t\t\t[EOF]     %4d\n", idx, byte)               ; break;
        default     : (void)sprintf(bstr, "<><><>%12ld)\t%c    %4d\n", idx, static_cast<char>(byte), byte); break;
    }
}


////////~~~~~~~~END>  cu_help_decode.cpp
