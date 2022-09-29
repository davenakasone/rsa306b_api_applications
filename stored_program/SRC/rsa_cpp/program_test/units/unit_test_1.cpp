/*
    unit test # 1, "class common_utility"

    this class is composed into the 3 core classes of the program
    a global stand-alone instance is also available
    it is very important that it operates correctly

    goals:
        
        // call-check management
        const char* get_status_code_string();
        int         get_status_code_number();
        CODEZ       get_status_code       ();                                                  
        CODEZ       report_status_code    (CODEZ current_code);                                
        CODEZ       codez_checker         (const CODEZ* codez_list, const int codez_count);    
        const char* codez_messages        (CODEZ lookup);                                     

        // execute a specific function + verify
        CODEZ exe_strcpy (char* destination, const char* source); 
        CODEZ exe_remove (const char* file_to_delete);

        // help for a common task
        CODEZ h_find_bytes_in_file(const char* file_path_name, long& result);
        CODEZ h_match_extension   (const char* file_path_name, const char* extension);
        CODEZ h_decode_print      (const char* file_path_name, long int start_byte, long int stop_byte);
        CODEZ h_decode_write      (const char* raw_file, const char* output_file, long int& start_byte, long int& stop_byte);
        
        // timer, both CPU and wall-clock
        CODEZ  timer_split_start      ();                                          
        CODEZ  timer_split_stop       ();                                         
        CODEZ  timer_print_split      (int new_lines_begin, int new_lines_end);    
        CODEZ  timer_print_running    (int new_lines_begin, int new_lines_end);    
        CODEZ  timer_print_both       (int new_lines_begin, int new_lines_end);    
        double timer_get_split_cpu   ();                                           
        double timer_get_split_wall  ();                                           
        double timer_get_running_cpu ();                                           
        double timer_get_running_wall();                                           

        // string tools
        CODEZ wchar_2_char_std(char* destination, const wchar_t* source);                            
        CODEZ wchar_2_char(const wchar_t* source, char* destination);                                
        CODEZ make_date_timestamp(const time_t* seconds, const uint64_t nanos, char* dts_string); 

        // acqstatus bitchecking, the API has 6 bitcheck points in 5 API groups
        CODEZ ifstream_acq_status(const uint32_t acq_status, const uint32_t valid_bitmask, char results[IFSTREAM_BITCHECKS][BUF_D]);
        //CODEZ dpx_acq_status     (const uint32_t acq_status, const uint32_t valid_bitmask, char results[DPX_BITCHECKS][BUF_D]     );
        CODEZ iqblk_acq_status   (const uint32_t acq_status, const uint32_t valid_bitmask, char results[IQBLK_BITCHECKS][BUF_D]   );
        CODEZ iqstream_acq_status(const uint32_t acq_status, const uint32_t valid_bitmask, char results[IQSTREAM_BITCHECKS][BUF_D]);
        CODEZ spectrum_acq_status(const uint16_t acq_status, const uint16_t valid_bitmask, char results[SPECTRUM_BITCHECKS][BUF_D]);
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int ut1_repz = 3;
static void ut1_callcheck();


void unit_test_1 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class 'common_utility'\n", __func__);
#endif                   
////~~~~

    ut1_callcheck();

////~~~~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut1_callcheck()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  call-check management\n", __func__);
#endif                   
////~~~~

    (void)printf("\tstatus code number:  %d\n", X_util.get_status_code_number());
    (void)printf("\tstatus code enum  :  %d\n", X_util.get_status_code());
    (void)printf("\tstatus code string:  %s\n", X_util.get_status_code_string());

    CODEZ test[ut1_repz] = {CODEZ::_10_fclose_failed, CODEZ::_15_ftell_failed, CODEZ::_2_error_in_logic};
    (void)printf("\n\tcodez batch result =  %d\n\n", X_util.codez_checker(test, ut1_repz));

    for (int ii = 0; ii < ut1_repz; ii++)
    {
        X_util.report_status_code(test[ii]);
        (void)printf("\t[%2d of %2d] status code number:  %d\n", ii, ii, X_util.get_status_code_number());
        (void)printf("\t[%2d of %2d] status code enum  :  %d\n", ii, ii, X_util.get_status_code());
        (void)printf("\t[%2d of %2d] status code string:  %s\n", ii, ii, X_util.get_status_code_string());
    }

    printf("\navailable 'CODEZ':\n");
    for (int ii = 0; ii < ROWS_CODEZ; ii++)
    {
        printf("\t%s\n", X_util.codez_messages(static_cast<CODEZ>(ii)));
    }

////~~~~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif


////////~~~~~~~~END>  unit_test_1.cpp
