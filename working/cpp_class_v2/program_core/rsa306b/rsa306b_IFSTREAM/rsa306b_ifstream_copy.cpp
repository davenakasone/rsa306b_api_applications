/*
    API group "IFSTREAM", copiers

    public :
        #  none
    
    private :
        < 1 >  _ifstream_copy_vars()
        < 2 >  _ifstream_copy_file_name_suffix()
        < 3 >  _ifstream_copy_file_path()
        < 4 >  _ifstream_copy_file_name_base()
        < 5 >  _ifstream_copy_file_length_ms()
        < 6 >  _ifstream_copy_file_count()
        < 7 >  _ifstream_copy_output_configuration_select()
        < 8 >  _ifstream_copy_is_enabled_adc()
        < 9 >  _ifstream_copy_is_active()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_ifstream_copy_file_name_suffix();
    this->_ifstream_copy_file_path();
    this->_ifstream_copy_file_name_base();
    this->_ifstream_copy_file_length_ms();
    this->_ifstream_copy_file_count();
    this->_ifstream_copy_output_configuration_select();
    this->_ifstream_copy_is_enabled_adc();
    this->_ifstream_copy_is_active();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_ifstream_copy_file_name_suffix()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.file_name_suffix = this->_vars.ifstream.file_name_suffix;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_ifstream_copy_file_path()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    strcpy(this->vars.ifstream.file_path, this->_vars.ifstream.file_path);
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_ifstream_copy_file_name_base()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    strcpy(this->vars.ifstream.file_name_base, this->_vars.ifstream.file_name_base);
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_ifstream_copy_file_length_ms()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.file_length_ms = this->_vars.ifstream.file_length_ms;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_ifstream_copy_file_count()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.file_count = this->_vars.ifstream.file_count;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_ifstream_copy_output_configuration_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.output_configuration_select = this->_vars.ifstream.output_configuration_select;
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_ifstream_copy_is_enabled_adc()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.is_enabled_adc = this->_vars.ifstream.is_enabled_adc;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_ifstream_copy_is_active()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.ifstream.is_active = this->_vars.ifstream.is_active;
}


////////~~~~~~~~END>  rsa306b_ifstream_copy.cpp
