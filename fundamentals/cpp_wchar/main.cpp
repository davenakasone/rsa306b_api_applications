/*
    handle the wchar_t
*/

#include <iostream>
#include <cwchar>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <wchar.h> old


int main()
{
    wchar_t w = L'A';
    std::cout << "\nthe integer of the wchar_t :  " << w << std::endl;
    std::wcout << "the value of the wchar_t  :  " << w << std::endl;
    printf("printf() wchar_t:  %c\n", w);
    printf("bytes of wchar_t:  %lu\n", sizeof(w));

    wchar_t w_str[10] = L"abcde";
    char c_str[10] = "tuvwxyz";
    size_t s_len = wcslen(w_str);
    printf("\nthe wchar_t string length:  %lu\n", s_len);

    int idx = 0;
    memset(c_str, '\0', 10);
    while (idx < s_len)
    {
        if (w_str[idx] < 255)
        {
            c_str[idx] = w_str[idx];
        }
        else
        {
            printf("conversion not possilbe\n");
            return EXIT_FAILURE;
        }
        idx++;
    }
    printf("copied to narrow char*:  \"%s\"\n", c_str);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}