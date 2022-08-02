/*
    common public funtions of the 'siq_handler_class'

    public:
        < 1 >  siq_handler_class()
        < 2 >  ~siq_handler_class()
    
    private:
        #  none
*/

#include "siq_manager_class.h"

/*
    < 1 >
    constructor
*/
siq_manager_class::siq_manager_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
}


////~~~~


/*
    < 2 >
    destructor
*/
siq_manager_class::~siq_manager_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif    
}


////////~~~~~~~~END>  siq_public.cpp
