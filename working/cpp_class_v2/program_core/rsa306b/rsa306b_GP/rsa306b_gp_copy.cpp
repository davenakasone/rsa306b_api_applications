/*
    primary getter +
    private member functions of the "general purpose" group
    used to copy private variable struct into the public variable struct

        public :
            < 1 >  get_everything()
        
        private :
            < 1 >  _gp_copy_vars()
            < 2 >  _gp_copy_helper()
            < 3 >  _gp_copy_holder()
            < 4 >  _gp_copy_call_status()
            < 5 >  _gp_copy_api_status()
            < 6 >  _gp_copy_was_good_acquisition()
            < 7 >  _gp_copy_acquistion_message()
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

    this->_align_get_vars();
    this->_audio_get_vars();
    this->_config_get_vars();
    this->_device_get_vars();
    this->_ifstream_get_vars();
    this->_reftime_get_vars();
    this->_spectrum_get_vars();
    this->_trig_get_vars();

    // INSERT
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
  
    this->_gp_copy_helper();
    this->_gp_copy_holder();
    this->_gp_copy_call_status();
    this->_gp_copy_api_status();
    this->_gp_copy_acquisition_code();
    this->_gp_copy_acquistion_message();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_gp_copy_helper()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.helper, this->_vars.gp.helper);
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_gp_copy_holder()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.holder, this->_vars.gp.holder);
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_gp_copy_call_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->vars.gp.call_status = this->_vars.gp.call_status;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_gp_copy_api_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->vars.gp.api_status = this->_vars.gp.api_status;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_gp_copy_acquisition_code()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->vars.gp.acquisition_code = this->_vars.gp.acquisition_code;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_gp_copy_acquistion_message()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    strcpy(this->vars.gp.acquisition_message, this->_vars.gp.acquisition_message);
}


////////~~~~~~~~END>  rsa306b_gp_copy.cpp
