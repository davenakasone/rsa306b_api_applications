/*
    common_utility, class 

    public :
        < 1 >  h_find_bytes_in_file()
        < 2 >  h_match_extension()
        < 3 >  h_decode_write()

    private :
        #  none
*/

#include "common_utility.h"

static void get_byte(const int8_t byte, char* bstr, long int& idx);    // for local assistance


/*
    < 1 > public
    FILE* must be closed and on NULL
*/
CODEZ common_utility::h_find_bytes_in_file
(
    const char* file_path_name, 
    long& result
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    FILE* fp = NULL;
    if (this->exe_fopen(file_path_name, "r", fp) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fseek(fp, 0L, SEEK_END) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }

    if (this->exe_ftell(fp, result) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    
    if (this->exe_fseek(fp, 0L, SEEK_SET) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fclose(fp) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    fp = NULL;

    return report_status_code(CODEZ::_0_no_errors);    // "result" is updated
}


////~~~~


/*
    < 2 > public
    "r3f" "siq" "csv" ...
*/
CODEZ common_utility::h_match_extension
(
    const char* file_path_name, 
    const char* extension
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if (file_path_name == NULL ||
        extension == NULL       )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_7_parameter_not_allocated));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }

    size_t file_chars = strlen(file_path_name);
    memset(this->_worker, '\0', sizeof(_worker));
    size_t counter = file_chars-1;
    char compare_to[10];
    memset(compare_to, '\0', 10);
    while (counter >= 0                 &&
           file_path_name[counter] != '.')
    {
        if (counter < file_chars-10)
        {
            return this->report_status_code(CODEZ::_19_result_not_found);
        }
        this->_worker[file_chars-1-counter] = file_path_name[counter];
        counter--;
    }
    file_chars = strlen(this->_worker);
    if (file_chars < 1 || file_chars > 10)
    {
        return this->report_status_code(CODEZ::_19_result_not_found);
    }
    counter = 0;
    while (counter < file_chars)
    {
        compare_to[counter] = this->_worker[file_chars-1-counter];
        counter++;
    }
    if (strcmp(compare_to, extension) != 0)
    {
        return this->report_status_code(CODEZ::_19_result_not_found);
    }
    return report_status_code(CODEZ::_0_no_errors);    // the exentension matched
}


////~~~~


/*
    < 3 > public
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
    if (this->exe_fopen(file_path_name, "r", fp) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
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

    if (this->exe_fseek(fp, 0L, SEEK_SET) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fseek(fp, start_byte, SEEK_CUR) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    printf("\nmaking %s  ,  bytes[ %ld : %ld ]\n<<<begin file decode >>>\n\n",
            file_path_name, start_byte, stop_byte);

    for (long int ii = start_byte; ii <= stop_byte; ii++)
    {
        if (fread(&bget, sizeof(int8_t), 1, fp) != 1)
        {
            return this->exe_fclose(fp);
        }
        get_byte(bget, this->_worker, ii);
        (void)printf("%s", this->_worker);
    }
    if (this->exe_fclose(fp) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }

    (void)printf("\n<<< end file decode >>>\n");
    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > public
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
    if (this->exe_fopen(raw_file, "r", fp_r) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fopen(output_file, "w", fp_w) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
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
    if (this->exe_fseek(fp_r, 0L, SEEK_SET) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fseek(fp_r, start_byte, SEEK_CUR) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
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
            return this->exe_fclose(fp_r);
        }
        get_byte(bget, this->_worker, ii);
        (void)fputs(this->_worker, fp_w);
    }
    (void)sprintf(this->_worker, "\n<<< end file decode >>>\n");
    (void)fputs(this->_worker, fp_w);

    if (this->exe_fclose(fp_r) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->exe_fclose(fp_w) != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
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


////////~~~~~~~~END>  cu_help_1.cpp
