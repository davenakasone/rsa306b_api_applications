/*
    unit test # 1, class [common_utility]

    this class is composed into the 3 core classes of the program
    a global stand-alone instance is also available
    it is very important that it operates correctly

    goals:

        common_utility ()    
        ~common_utility()  
        clear          ()
        
        get_status_code_string() 
        get_status_code_number()                                              
        get_status_code       ()
        report_status_code    ()
        codez_checker         ()
        codez_messages        ()

        wchar_2_char()  

        exe_strcpy()
        exe_remove()

        find_bytes_in_file               ()
        extension_matched                ()
        tag_matched                      ()
        extension_and_tag_matched        ()
        find_files_with_extension        ()
        find_files_with_tag              ()
        find_files_with_extension_and_tag()

        delete_files_in_directory                         ()
        change_extension                                  ()
        switch_directory                                  ()
        insert_and_change_extension                       ()
        batch_switch_directory_and_change_extension       ()
        batch_switch_directory_insert_and_change_extension()
        
        decode_print      ()
        batch_decode_print()
        decode_write      ()
        batch_decode_write()
        
        timer_split_start     ()
        timer_split_stop      ()
        timer_print_split     ()
        timer_print_running   ()
        timer_print_both      ()
        timer_get_split_cpu   ()
        timer_get_split_wall  ()
        timer_get_running_cpu ()
        timer_get_running_wall()
        make_date_timestamp   ()

// acqstatus bitchecking, the API has 6 bitcheck points in 5 API groups
        ifstream_acq_status()
        //dpx_acq_status   ()
        iqblk_acq_status   ()
        iqstream_acq_status()
        spectrum_acq_status()
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
static void ut1_file_info();
static void ut1_mod_file();


void unit_test_1()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [common_utility]'\n", __func__);
#endif                   
//~
    X_util.clear_data();

    ut1_callcheck();
    ut1_exe();
    ut1_decode();
    ut1_timer();
    ut1_wchar();
    ut1_acq();
    ut1_file_info();
    ut1_mod_file();
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
    // get_status_code_string() 
    // get_status_code_number()                                              
    // get_status_code       ()
    // report_status_code    ()
    // codez_checker         ()
    // codez_messages        ()

    (void)printf("\tstatus code number:  %d\n", X_util.get_status_code_number());
    (void)printf("\tstatus code enum  :  %d\n", X_util.get_status_code());
    (void)printf("\tstatus code string:  %s\n", X_util.get_status_code_string());

    CODEZ test[bangz_ut1] = {CODEZ::_10_fclose_failed, CODEZ::_15_ftell_failed, CODEZ::_2_error_in_logic};  //
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
    // exe_strcpy()
    // exe_remove()

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

    (void)sprintf(X_util.helper, "%smydir/", DATA_DIRECTORY_PROCESSED);
    (void)X_util.exe_mkdir(X_util.helper);
    (void)sprintf(X_util.holder, "%stemp.txt", X_util.helper);
    fp = fopen(X_util.holder, "w");
    if (fp == NULL) {return;}
    fputs("data", fp);
    (void)fclose(fp);
    fp = NULL;
#ifdef WAIT_ENTER_CLEAR
    printf("\nsee if directory was made\n'%s'\n\tit will be deleted soon, press any key to execute:",
        X_util.helper);
    std::cin >> X_util.holder;
#endif
    (void)X_util.exe_rmdir(X_util.helper);

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
    // decode_print      ()
    // batch_decode_print()
    // decode_write      ()
    // batch_decode_write()

    long bytez = 0;
    FILE* fp = NULL;
    char ext[BUF_A] = "txt";

    (void)sprintf(X_util.helper, "%sut1encoded.%s", DATA_DIRECTORY_RAW, ext);
    fp = fopen(X_util.helper, "w");
    if (fp == NULL) {return;}
    (void)fputs("dummy data", fp);
    (void)fclose(fp);
    fp = NULL;
    printf("\nmade:  '%s'\n", X_util.helper);
    printf("\n\textension == '%s' ?  %d {0=false, 1=true}\n",
        ext,
        X_util.extension_matched(X_util.helper, ext));
    (void)X_util.find_bytes_in_file(X_util.helper, bytez);
    printf("\n\tbytes in file:  %ld\n", bytez);

    sprintf(X_util.holder, "%sut1decoded.txt", DATA_DIRECTORY_PROCESSED);
    X_util.decode_print(X_util.helper, 0, 0);
    X_util.decode_write(X_util.helper, X_util.holder, 0, 0);
    printf("\nsee files:\n");

#ifdef WAIT_ENTER_CLEAR
    printf("%s\n%s\n\tany key to delete:", X_util.helper, X_util.holder);
    char discard[BUF_C];
    std::cin >> discard;
#endif
    X_util.exe_remove(X_util.helper);
    X_util.exe_remove(X_util.holder);

    for (int ii = 0; ii < bangz_ut1; ii++)
    {
        (void)sprintf(X_util.helper, "%sraw%d.%s", DATA_DIRECTORY_RAW, ii, EXT_DECODED);
        fp = fopen(X_util.helper, "w");
        if (fp == NULL) {return;}
        (void)sprintf(X_util.holder, "dummy data %d of %d\n", ii+1, bangz_ut1);
        (void)fputs(X_util.holder, fp);
        (void)fclose(fp);
        fp=NULL;
    }
    X_util.batch_decode_print(DATA_DIRECTORY_RAW, EXT_DECODED, 0, 0, X_util.filez_in);
    for (std::size_t ii = 0UL; ii < X_util.filez_in.size(); ii++)
    {
        printf("%s\n", X_util.filez_in[ii].c_str());
    }
    X_util.batch_decode_write
    (
        DATA_DIRECTORY_RAW, 
        EXT_DECODED, 
        DATA_DIRECTORY_PROCESSED, 
        TAG_DECODED, 
        EXT_PARSED,
        0, 
        0, 
        X_util.filez_in, 
        X_util.filez_out
    );
    for (std::size_t ii = 0UL; ii < X_util.filez_in.size(); ii++)
    {
        printf("%s\n", X_util.filez_in[ii].c_str());
    }
    for (std::size_t ii = 0UL; ii < X_util.filez_out.size(); ii++)
    {
        printf("%s\n", X_util.filez_out[ii].c_str());
    }
#ifdef WAIT_ENTER_CLEAR
    printf("\n\tany key to delete files: ");
    std::cin >> discard;
#endif
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

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
    // timer_split_start     ()
    // timer_split_stop      ()
    // timer_print_split     ()
    // timer_print_running   ()
    // timer_print_both      ()
    // timer_get_split_cpu   ()
    // timer_get_split_wall  ()
    // timer_get_running_cpu ()
    // timer_get_running_wall()
    // make_date_timestamp   ()

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
    
    X_util.make_date_timestamp(0,0, X_util.helper);
    printf("\n%s\n", X_util.helper);
    X_util.make_date_timestamp(&X_rsa.vars.reftime.start.seconds, 111, X_util.helper);
    printf("\n%s\n", X_util.helper);

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
    // wchar_2_char()  

    printf("\n");
    char std_c_str[BUF_A] = "cstring std";
    wchar_t std_wc_str[BUF_A] = L"w_cstring std";
    std::cout << "c-string :  " << std_c_str << std::endl;
    std::cout << "wc-string:  " << std_wc_str << std::endl;
    X_util.wchar_2_char(std_c_str, std_wc_str, true);
    std::cout << "c-string :  " << std_c_str << std::endl;
    std::cout << "wc-string:  " << std_wc_str << std::endl;

    printf("\n");
    char unq_c_str[BUF_A] = "cstring unq";
    wchar_t unq_wc_str[BUF_A] = L"w_cstring unq";
    std::cout << "c-string :  " << unq_c_str << std::endl;
    std::cout << "wc-string:  " << unq_wc_str << std::endl;
    X_util.wchar_2_char(unq_c_str, unq_wc_str, false);
    std::cout << "c-string :  " << unq_c_str << std::endl;
    std::cout << "wc-string:  " << unq_wc_str << std::endl;

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
    // ifstream_acq_status()
    // //dpx_acq_status   ()
    // iqblk_acq_status   ()
    // iqstream_acq_status()
    // spectrum_acq_status()

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


////~~~~


static void ut1_file_info()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  file info functions\n", __func__);
#endif                   
//~
    // extension_matched                ()
    // tag_matched                      ()
    // extension_and_tag_matched        ()
    // find_files_with_extension        ()
    // find_files_with_tag              ()
    // find_files_with_extension_and_tag()
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

    FILE* fp = NULL;
    for (int ii = 0; ii < bangz_ut1; ii++)
    {
        if (ii%2==1)
        {
            (void)sprintf(X_util.helper, "%sut1_%d_.%s", DATA_DIRECTORY_PROCESSED, ii, EXT_PARSED);
        }
        else
        {
            (void)sprintf(X_util.helper, "%sut1_%d_%s.%s", DATA_DIRECTORY_PROCESSED, ii, TAG_PARSED, EXT_PARSED);
        }
        fp = fopen(X_util.helper, "w");
        fputs("trash", fp);
        fclose(fp);
        fp = NULL;
        printf("%s\n", X_util.helper);
    }
    std::vector<std::string> temp;
    X_util.find_files_with_extension(DATA_DIRECTORY_PROCESSED, EXT_PARSED, X_util.filez_in, true);
    X_util.find_files_with_tag(DATA_DIRECTORY_PROCESSED, TAG_PARSED, X_util.filez_out, true);
    X_util.find_files_with_extension_and_tag(DATA_DIRECTORY_PROCESSED, EXT_PARSED, TAG_PARSED, temp, true);
    printf("\nmatched extension:\n");
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("%s\n", X_util.filez_in[ii].c_str());
    }
    printf("\nmatched tag:\n");
    for (std::size_t ii = 0; ii < X_util.filez_out.size(); ii++)
    {
        printf("%s\n", X_util.filez_out[ii].c_str());
    }
    printf("\nmatched extension + tag:\n");
    for (std::size_t ii = 0; ii < temp.size(); ii++)
    {
        printf("%s\n", temp[ii].c_str());
    }
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut1_mod_file()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  file modification\n", __func__);
#endif                   
//~
    // change_extension                                  ()
    // switch_directory                                  ()
    // insert_and_change_extension                       ()
    // batch_switch_directory_and_change_extension       ()
    // batch_switch_directory_insert_and_change_extension()
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

    FILE* fp = NULL;
    sprintf(X_util.helper, "%sraw123.%s", DATA_DIRECTORY_RAW, R3F_RAW_EXT);
    fp = fopen(X_util.helper, "w");
    fclose(fp);
    fp = NULL;
    printf("\noriginal:\n\t%s\n", X_util.helper);
    X_util.change_extension(X_util.helper, DATA_DEFAULT_EXT);
    printf("\nextension changed:\n\t%s\n", X_util.helper);
    X_util.switch_directory(X_util.helper, DATA_DIRECTORY_PROCESSED);
    printf("\nswitched directory:\n\t%s\n", X_util.helper);
    X_util.insert_and_change_extension(X_util.helper, SIQ_TAG_IQ, EXT_PARSED);
    printf("\ninserted and changed extension:\n\t%s\n", X_util.helper);

    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

    printf("\noriginal files made:\n");
    for (int ii = 0; ii < bangz_ut1; ii++)
    {
        sprintf(X_util.helper, "%sraw123_%d_%s.%s", DATA_DIRECTORY_RAW, ii, TAG_DECODED, EXT_DECODED);
        fp = fopen(X_util.helper, "w");
        fclose(fp); fp= NULL;
        printf("%s\n", X_util.helper);
    }
    X_util.batch_switch_directory_and_change_extension
    (
        DATA_DIRECTORY_RAW, 
        EXT_DECODED, 
        DATA_DIRECTORY_PROCESSED, 
        DATA_DEFAULT_EXT, 
        X_util.filez_in
    );
    X_util.batch_switch_directory_insert_and_change_extension
    (
        DATA_DIRECTORY_RAW, 
        EXT_DECODED, 
        DATA_DIRECTORY_PROCESSED, 
        IFSTREAM_TAG_EQL,
        SIQ_RAW_EXT, 
        X_util.filez_out
    );
    printf("\nswitched directory and changed extension:\n");
    for (std::size_t ii = 0; ii < X_util.filez_in.size(); ii++)
    {
        printf("%s\n", X_util.filez_in[ii].c_str());
    }
    printf("\n+ inserted:\n");
    for (std::size_t ii = 0; ii < X_util.filez_out.size(); ii++)
    {
        printf("%s\n", X_util.filez_out[ii].c_str());
    }
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_1.cpp
