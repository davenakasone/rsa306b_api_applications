/*
    primary getter +
    private member functions of the "general purpose" group
    used to copy private variable struct into the public variable struct

        public :
            < 1 >  get_everything()
        
        private :
            < 1 >  _gp_copy_vars()
            < 2 >  _gp_copy_vars_error_code()
            < 3 >  _gp_copy_vars_helper()
            < 4 >  _gp_copy_vars_holder()
            < 5 >  _gp_copy_vars_call_status()
            < 6 >  _gp_copy_vars_api_status()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    copies every variable of the private struct into the public struct
    the class attempts to update the public struct in real time
    this function can be called for insurace or convienence
    deep copy is performed by group, using group copier functions
*/
void rsa306b_class::get_everything()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  constructor\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_gp_copy_vars(); 
}

////~~~~


/*
    < 1 > private

    initiaties copying sequence for "gp" variables
*/
void rsa306b_class::_gp_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_gp_copy_vars_error_code();    
    this->_gp_copy_vars_helper();
    this->_gp_copy_vars_holder();
    this->_gp_copy_vars_call_status();
    this->_gp_copy_vars_api_status();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_gp_copy_vars_error_code()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.error_code, this->_vars.gp.error_code);
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_gp_copy_vars_helper()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.helper, this->_vars.gp.helper);
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_gp_copy_vars_holder()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.holder, this->_vars.gp.holder);
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_gp_copy_vars_call_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->vars.gp.call_status = this->_vars.gp.call_status;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_gp_copy_vars_api_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->vars.gp.api_status = this->_vars.gp.api_status;
}

////////~~~~~~~~END>  rsa306b_gp_copy.cpp
