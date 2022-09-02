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
        printf("whar_t* as source, char* as destination:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);

        wcscpy(w_str, L"стринг*");
        printf("\nthe whar_t* and char*:\n");
        std::wcout << "the w-string:  " << w_str << std::endl;
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("whar_t* as source, char* as destination:\n");
        std::wcout << "the w-string:  " << w_str << std::endl;
        printf("the c-string:  %s\n", c_str);

        std::wcscpy(w_str, L"");
        printf("\nthe whar_t* and char*:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("whar_t* as source, char* as destination:\n");
        printf("the w-string:  %ls\n", w_str);
        printf("the c-string:  %s\n", c_str);

        wchar_t w_strr[BUF_A] = {300, 350, 412, 65, 0};
        std::wcscpy(w_str, w_strr);
        printf("\nthe whar_t* and char*:\n");
        std::wcout << "the w-string:  " << w_str << std::endl;
        printf("the c-string:  %s\n", c_str);
        rsa.gp_wchar_2_char(w_str, c_str);
        printf("whar_t* as source, char* as destination:\n");
        std::wcout << "the w-string:  " << w_str << std::endl;
        printf("the c-string:  %s\n", c_str);
    }
    printf("\n%s()  ,  test complete\n", __func__);
}


/////////~~~~~~~~END>  task_991.cpp
