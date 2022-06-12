/*
    ensure the whchar_2_char general purpose utility is working
*/

#include "../testz.h"


void task_991()
{
    printf("\n%s()  ,  validate the whchar_t to char utility\n", __func__);
    {
        rsa306b_class rsa;

        wchar_t w_str[BUF_A] = L"wide str 2 c str";
        char c_str[BUF_A] = "any ascii str";

        printf("\nthe whar_t* and char* as initialized:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("\nwhar_t* as source, char* as destination:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);

        wcscpy(w_str, L"another wchar_t*");
        printf("\nthe whar_t* and char*:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("\nwhar_t* as source, char* as destination:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);

        wcscpy(w_str, L"");
        printf("\nthe whar_t* and char*:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("\nwhar_t* as source, char* as destination:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);
    }
    printf("\n%s()  ,  test complete\n", __func__);
}


/////////~~~~~~~~END>  task_991.cpp
