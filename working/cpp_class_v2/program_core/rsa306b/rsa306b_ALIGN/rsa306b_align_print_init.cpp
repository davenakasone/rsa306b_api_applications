/*
    API group "ALIGN"

    public :
        < 1 >   print_align()
    
    private :
        < 1 >  _align_init()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints the "ALIGN" variables to stdout, 
        using the private struct
*/
void rsa306b_class::print_align()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'ALIGN' group:\n");
    printf("\talignment is needed :  %d\n", this->_vars.align.is_needed);
    printf("\tdevice is warmed-up :  %d\n", this->_vars.align.is_warmed);
}


////~~~~


/*
    < 1 > private
    initializes variables in the "ALIGN" group
*/
void rsa306b_class::_align_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_vars.align.is_needed = true;
    this->_vars.align.is_warmed = true;   

    this->_align_copy_vars(); 
}


////////~~~~~~~~END>  rsa306b_align_print_init.cpp
