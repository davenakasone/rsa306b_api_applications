/*
    unit test # 1, class [common_utility]

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
        bool  h_matched_extension (const char* file_path_name, const char* extension);
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


constexpr int bangz_ut1 = 3;
static void ut1_callcheck();
static void ut1_exe();
static void ut1_decode();
static void ut1_timer();
static void ut1_wchar();
static void ut1_acq();


void unit_test_1()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [common_utility]'\n", __func__);
#endif                   
//~

    ut1_callcheck();
    ut1_exe();
    ut1_decode();
    ut1_timer();
    ut1_wchar();
    ut1_acq();

//~
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
//~

    (void)printf("\tstatus code number:  %d\n", X_util.get_status_code_number());
    (void)printf("\tstatus code enum  :  %d\n", X_util.get_status_code());
    (void)printf("\tstatus code string:  %s\n", X_util.get_status_code_string());

    CODEZ test[bangz_ut1] = {CODEZ::_10_fclose_failed, CODEZ::_15_ftell_failed, CODEZ::_2_error_in_logic};
    (void)printf("\n\tcodez batch result =  %d\n\n", X_util.codez_checker(test, bangz_ut1));

    for (int ii = 0; ii < bangz_ut1; ii++)
    {
        X_util.report_status_code(test[ii]);
        (void)printf("\t[%2d of %2d] status code number:  %d\n", ii+1, bangz_ut1, X_util.get_status_code_number());
        (void)printf("\t[%2d of %2d] status code enum  :  %d\n", ii+1, bangz_ut1, X_util.get_status_code());
        (void)printf("\t[%2d of %2d] status code string:  %s\n", ii+1, bangz_ut1, X_util.get_status_code_string());
    }

    printf("\navailable 'CODEZ':\n");
    for (int ii = 0; ii < ROWS_CODEZ; ii++)
    {
        printf("\t%s\n", X_util.codez_messages(static_cast<CODEZ>(ii)));
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut1_exe()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  methods that execute common library functions\n", __func__);
#endif                   
//~

    char src[BUF_A] = "source cstring";
    char dest[BUF_A] = "destination cstring";
    printf("\nsource     :  %s\n", src);
    printf("destination:  %s\n", dest);
    (void)X_util.exe_strcpy(dest, src);
    printf("\nsource     :  %s\n", src);
    printf("destination:  %s\n", dest);

    FILE* fp = NULL;
    (void)sprintf(X_util.helper, "%sut1.txt", DATA_DIRECTORY_PROCESSED);
    fp = fopen(X_util.helper, "w");
    if (fp == NULL) {return;}
    (void)fputs("dummy data", fp);
    (void)fclose(fp);
    fp = NULL;
#ifdef WAIT_ENTER_CLEAR
    printf("\nsee if file was made\n'%s'\n\tit will be deleted soon, press any key to execute:",
        X_util.helper);
    std::cin >> X_util.holder;
#endif
    X_util.exe_remove(X_util.helper);

//~
#ifdef WAIT_ENTER_CLEAR
flush_io();
#endif
}


////~~~~


static void ut1_decode()
{
    #ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  methods that decode and manage files\n", __func__);
#endif                   
//~

    long bytez = 0;
    FILE* fp = NULL;
    char ext[BUF_A] = "txt";
    (void)sprintf(X_util.helper, "%sut1decode.%s", DATA_DIRECTORY_RAW, ext);
    fp = fopen(X_util.helper, "w");
    if (fp == NULL) {return;}
    (void)fputs("dummy data", fp);
    (void)fclose(fp);
    fp = NULL;
    printf("\nmade:  '%s'\n", X_util.helper);
    printf("\n\textension == '%s' ?  %d {0=false, 1=true}\n",
        ext,
        X_util.h_matched_extension(X_util.helper, ext));
    (void)X_util.h_find_bytes_in_file(X_util.helper, bytez);
    printf("\n\tbytes in file:  %ld\n", bytez);

    sprintf(X_util.holder, "%sut1decoded.txt", DATA_DIRECTORY_PROCESSED);
    X_util.h_decode_print(X_util.helper, 0, 0);
    X_util.h_decode_write(X_util.helper, X_util.holder, 0, 0);
    printf("\nsee files:\n");
#ifdef WAIT_ENTER_CLEAR
    printf("%s\n%s\n\tany key to delete:", X_util.helper, X_util.holder);
    char discard[BUF_C];
    std::cin >> discard;
#endif
    X_util.exe_remove(X_util.helper);
    X_util.exe_remove(X_util.holder);

//~
#ifdef WAIT_ENTER_CLEAR
flush_io();
#endif
}


////~~~~


static void ut1_timer()
{
    #ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  timers (wall and CPU)\n", __func__);
#endif                   
//~

    X_util.timer_split_start();
    printf("\n\t\tsleep(1)  ...split started\n");
    sleep(1);

    X_util.timer_split_stop();
    X_util.timer_print_both(1,1);
    printf("[cpu/wall]  running:  %lf  |  %lf  ,  %lf  |  %lf\n",
        X_util.timer_get_running_cpu(),
        X_util.timer_get_running_wall(),
        X_util.timer_get_split_cpu(),
        X_util.timer_get_split_wall());
    printf("\n\t\tsleep(2)  ...split continues\n");
    sleep(2);

    X_util.timer_split_stop();
    X_util.timer_print_both(1,1);
    printf("[cpu/wall]  running:  %lf  |  %lf  ,  %lf  |  %lf\n",
        X_util.timer_get_running_cpu(),
        X_util.timer_get_running_wall(),
        X_util.timer_get_split_cpu(),
        X_util.timer_get_split_wall());
    X_util.timer_split_start();
    printf("\n\t\tsleep(4)  ...split interval resets\n");
    sleep(4);

    X_util.timer_split_stop();
    X_util.timer_print_both(1,1);
    printf("[cpu/wall]  running:  %lf  |  %lf  ,  %lf  |  %lf\n",
        X_util.timer_get_running_cpu(),
        X_util.timer_get_running_wall(),
        X_util.timer_get_split_cpu(),
        X_util.timer_get_split_wall());

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut1_wchar()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  wchar_t* --> char*\n", __func__);
#endif                   
//~

    char c_str[BUF_A] = "cstring";
    wchar_t wc_str[BUF_A] = L"w_cstring";
    std::cout << "c-string :  " << c_str << std::endl;
    std::cout << "wc-string:  " << wc_str << std::endl;

    X_util.wchar_2_char_std(c_str, wc_str);
    std::cout << "\nc-string :  " << c_str << std::endl;
    std::cout << "wc-string:  " << wc_str << std::endl;
//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut1_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  acquisition status helpers\n", __func__);
#endif                   
//~

    printf("\n\tIQBLK bitchecks:  %d...all will fail\n\n", IQBLK_BITCHECKS);
    if 
    (
        X_util.iqblk_acq_status(X_rsa.vars.iqblk.valid_bitmask, X_rsa.vars.iqblk.valid_bitmask, X_rsa.vars.iqblk.acq_status_messages) !=
        CODEZ::_0_no_errors
    ) 
    {
        for (int ii = 0; ii < IQBLK_BITCHECKS; ii++)
        {
            if (strcmp(BITCHECK_SUCCESS_MESSAGE, X_rsa.vars.iqblk.acq_status_messages[ii]) != 0)
            {
                printf("%s\n", X_rsa.vars.iqblk.acq_status_messages[ii]);
            }
        }
    }

    printf("\n\tIQSTREAM bitchecks:  %d...all will fail\n\n", IQSTREAM_BITCHECKS);
    if 
    (
        X_util.iqstream_acq_status(X_rsa.vars.iqstream.valid_bitmask, X_rsa.vars.iqstream.valid_bitmask, X_rsa.vars.iqstream.acq_status_messages) !=
        CODEZ::_0_no_errors
    ) 
    {
        for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
        {
            if (strcmp(BITCHECK_SUCCESS_MESSAGE, X_rsa.vars.iqstream.acq_status_messages[ii]) != 0)
            {
                printf("%s\n", X_rsa.vars.iqstream.acq_status_messages[ii]);
            }
        }
    }

    printf("\n\tIFSTREAM bitchecks:  %d...all will fail\n\n", IFSTREAM_BITCHECKS);
    if 
    (
        X_util.ifstream_acq_status(X_rsa.vars.ifstream.valid_bitmask, X_rsa.vars.ifstream.valid_bitmask, X_rsa.vars.ifstream.acq_status_messages) !=
        CODEZ::_0_no_errors
    ) 
    {
        for (int ii = 0; ii < IFSTREAM_BITCHECKS; ii++)
        {
            if (strcmp(BITCHECK_SUCCESS_MESSAGE, X_rsa.vars.ifstream.acq_status_messages[ii]) != 0)
            {
                printf("%s\n", X_rsa.vars.ifstream.acq_status_messages[ii]);
            }
        }
    }

    printf("\n\tSPECTRUM bitchecks:  %d...all will fail\n\n", SPECTRUM_BITCHECKS);
    if 
    (
        X_util.spectrum_acq_status(X_rsa.vars.spectrum.valid_bitmask, X_rsa.vars.spectrum.valid_bitmask, X_rsa.vars.spectrum.acq_status_messages) !=
        CODEZ::_0_no_errors
    ) 
    {
        for (int ii = 0; ii < SPECTRUM_BITCHECKS; ii++)
        {
            if (strcmp(BITCHECK_SUCCESS_MESSAGE, X_rsa.vars.spectrum.acq_status_messages[ii]) != 0)
            {
                printf("%s\n", X_rsa.vars.spectrum.acq_status_messages[ii]);
            }
        }
    }
    
    printf("\n\nchecking IFSTREAM :  %d  {0 == good bitcheck}\n",
        X_util.ifstream_acq_status(BITCHECK_SUCCESS, X_rsa.vars.ifstream.valid_bitmask, NULL));
    printf("checking IQBLK    :  %d  {0 == good bitcheck}\n",
        X_util.iqblk_acq_status(BITCHECK_SUCCESS, X_rsa.vars.iqblk.valid_bitmask, NULL));
    printf("checking IQSTREAM :  %d  {0 == good bitcheck}\n",
        X_util.iqstream_acq_status(BITCHECK_SUCCESS, X_rsa.vars.iqstream.valid_bitmask, NULL));
    printf("checking SPECTRUM :  %d  {0 == good bitcheck}\n",
        X_util.spectrum_acq_status(BITCHECK_SUCCESS, X_rsa.vars.spectrum.valid_bitmask, NULL));
    

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_1.cpp
