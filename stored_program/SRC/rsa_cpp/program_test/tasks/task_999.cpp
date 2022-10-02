/*
    temporary test bench
        don't keep anything permenant here

    bool  h_matched_extension    (const char* file_path_name, const char* extension);
    h_batch_match_extension(const char* directory, const char* extension, std::vector<std::string>& filez, bool include_directory);
    h_change_extension     (char* file_path_name, const char* new_extension);
    h_batch_change_redirect(const char* in_directory, const char* in_extension, const char* out_directory, const char* out_extension, std::vector<std::string>& new_filez);
    h_insert_and_change_extension(char* file_path_name, const char* to_insert, const char* new_extension);
    h_switch_directory(char* file_to_change, const char* new_directory);
    h_batch_redir_insert_ext_change(const char* in_directory, const char* in_extension, const char* out_directory, const char* inserts, const char* out_extension, std::vector<std::string>& new_filez);
    h_decode_print(const char* file_path_name, const long int start_byte, const long int stop_byte);
    h_decode_write(const char* raw_file, const char* output_file, const long int start_byte, const long int stop_byte);
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_999()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  a unit test template\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    FILE* fp = NULL;
    char extn1[BUF_A] = "abc";
    char extn2[BUF_A] = "txt";

    for (int ii = 0; ii < 17; ii++)
    {
        sprintf(X_util.helper, "%stest_%d.%s", DATA_DIRECTORY_RAW, ii, extn1);
        fp = fopen(X_util.helper, "w");
        fputs(X_util.helper, fp);
        fclose(fp);
        fp = NULL;
    }

    // X_util.h_batch_change_redirect(DATA_DIRECTORY_RAW, extn1, DATA_DIRECTORY_PROCESSED, extn2, X_util.filez_out);
    // for (std::size_t ii = 0; ii < X_util.filez_out.size(); ii++)
    // {
    //     printf("%s\n", X_util.filez_out[ii].c_str());
    // }

    X_util.h_batch_redir_insert_ext_change(DATA_DIRECTORY_RAW, extn1, DATA_DIRECTORY_PROCESSED, "_penis_", extn2, X_util.filez_out);
    for (std::size_t ii = 0; ii < X_util.filez_out.size(); ii++)
    {
        printf("%s\n", X_util.filez_out[ii].c_str());
    }


//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


/////////~~~~~~~~END>  task_999.cpp
