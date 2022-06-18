/*
    API group "general purpose"

    public :
        < 1 >  gp_wchar_2_char()
    
    private :
        #  none
        
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    the caller should ensure the destiation c-string 
    is allocated to the proper length before calling
*/
void rsa306b_class::gp_wchar_2_char
(
    wchar_t* source, 
    char* destination
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (source == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tthe w_string is empty\n");
        #endif
        return;
    }
    if (destination == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tthe c_string is empty\n");
        #endif
        return;
    }
    int w_len = (int)wcslen(source);
    int idx = 0;
    if (source[idx] == '\0' ||
        w_len == 0           )
    {
        #ifdef DEBUG_MAX
            printf("\n\tno string to convert\n");
        #endif
        memset(destination, '\0', 2);    // ensure NULL termination
        return;
    }

    while (idx < w_len)
    {
        if (source[idx] <= 127 &&
            source[idx] >= 0   )    // ASCII range is 0:127
        {
            destination[idx] = source[idx];
        }
        else
        {
            #ifdef DEBUG_MIN
                printf("\n\t wchar_t* to char* not possible\n");
            #endif
            return;
        }
        idx++;
    }
    destination[idx] = '\0';    // ensure NULL termination
}


////~~~~


////////~~~~~~~~END>  rsa306b_gp_utility.cpp
