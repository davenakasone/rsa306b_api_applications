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
    size_t s_len = wcslen(source);


}


////~~~~


////////~~~~~~~~END>  rsa306b_gp_utility.cpp
