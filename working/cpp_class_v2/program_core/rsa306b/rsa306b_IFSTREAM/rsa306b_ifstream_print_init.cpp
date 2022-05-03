/*
    API group "IFSTREAM"

    public :
        < 1 >  print_ifstream()
    
    private :
        < 1 >  _ifstream_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::print_ifstream()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'IFSTREAM' group >>>\n");
    printf("\tfile name suffix      :  %d  ", this->_vars.ifstream.file_name_suffix);
    switch (this->_vars.ifstream.file_name_suffix)
    {
        case (RSA_API::IFSSDFN_SUFFIX_NONE)          : printf("{none}\n");                break;
        case (RSA_API::IFSSDFN_SUFFIX_TIMESTAMP)     : printf("{timestamp included}\n");  break;
        case (RSA_API::IFSSDFN_SUFFIX_INCRINDEX_MIN) : printf("{minimal, auto-index}\n"); break;
        default                                      : printf("{! UNKNOWN !}\n");         break;
    }
    printf("\tfile path             :  %s\n", this->_vars.ifstream.file_path);
    printf("\tfile base name        :  %s\n", this->_vars.ifstream.file_name_base);
    printf("\tfile length (ms)      :  %d\n", this->_vars.ifstream.file_length_ms);
    printf("\tfile count            :  %d\n", this->_vars.ifstream.file_count);
    printf("\toutput configuration  :  %d  ", this->_vars.ifstream.output_configuration_select);
    switch (this->_vars.ifstream.output_configuration_select)
    {
        case (RSA_API::IFSOD_CLIENT)         : printf("{output direct to client, no file written}\n");                   break;
        case (RSA_API::IFSOD_FILE_R3F)       : printf("{R3F file output}\n");                                            break;
        case (RSA_API::IFSOD_FILE_R3HA_DET)  : printf("{R3H+R3A file output}\n");                                        break;
        case (RSA_API::IFSOD_FILE_MIDAS)     : printf("{Midas CDIF file output, combined header+data file}\n");          break;
        case (RSA_API::IFSOD_FILE_MIDAS_DET) : printf("{Midas CDIF+DET file output, separate header and data files}\n"); break;
        default                              : printf("{! UNKNOWN !}\n");                                                break;
    }
    printf("\tis enabled ADC        :  %d\n", this->_vars.ifstream.is_enabled_adc);
	printf("\tis active streaming   :  %d\n", this->_vars.ifstream.is_active);		 
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_vars.ifstream.file_name_suffix = this->_vars.constants.IFSTREAM_SUFFIX;
    strcpy(this->_vars.ifstream.file_path, this->_vars.constants.IFSTREAM_FILE_PATH);
    strcpy(this->_vars.ifstream.file_name_base, this->_vars.constants.IFSTREAM_FILE_NAME_BASE);
    this->_vars.ifstream.file_length_ms = this->_vars.constants.IFSTREAM_DEFAULT_MS;
    this->_vars.ifstream.file_count = this->_vars.constants.IFSTREAM_DEFAULT_FILE_COUNT;
    this->_vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    this->_vars.ifstream.is_enabled_adc = false;
    this->_vars.ifstream.is_active = false;

    this->_ifstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_ifstream_print_init.cpp
