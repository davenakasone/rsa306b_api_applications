/*
    API group "IFSTREAM", user funcitons

    public :
        < 1 >  ifstream_set_vars
        < 2 >  ifstream_record_file()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::ifstream_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_ifstream_set_vars();
}


////~~~~


/*
    < 2 > public
    produces "*.r3f" file
    user already set correct settings (or is using default)
*/
void rsa306b_class::ifstream_record_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    /*
    bool writing = true;
	RSA_API::CONFIG_SetCenterFreq(this->vars.config.center_frequency_hz);
	RSA_API::CONFIG_SetReferenceLevel(this->vars.config.reference_level_dbm);
	RSA_API::IFSTREAM_SetDiskFilePath(this->vars.ifstream.file_path);
	RSA_API::IFSTREAM_SetDiskFilenameBase(this->vars.ifstream.file_name_base);
	RSA_API::IFSTREAM_SetDiskFilenameSuffix(this->vars.ifstream.file_name_suffix);
	RSA_API::IFSTREAM_SetDiskFileLength(this->vars.ifstream.file_length_ms);
	//RSA_API::IFSTREAM_SetDiskFileMode(RSA_API::StreamingModeFramed);
    RSA_API::IFSTREAM_SetOutputConfiguration(this->vars.ifstream.output_configuration_select);
	RSA_API::IFSTREAM_SetDiskFileCount(this->vars.ifstream.file_count);

	RSA_API::DEVICE_Run();
	RSA_API::IFSTREAM_SetEnable(true);
	while (writing == true)
	{
		//sleep(g_waitTime/1000);
		RSA_API::IFSTREAM_GetActiveStatus(&writing);
	}
	RSA_API::DEVICE_Stop();
    */
    //
    this->_vars.ifstream.is_active = true;
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();

    while(this->_vars.ifstream.is_active == true)
    {
        this->_ifstream_get_is_active();
    }

    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->device_stop();

    #ifdef DEBUG_MIN
        printf("\n\trecording complete, check:  %s%s*\n", 
            this->_vars.ifstream.file_path, 
            this->_vars.ifstream.file_name_base);
    #endif
    //
}


////////~~~~~~~~END>  rsa306b_ifstream_user1.cpp


/*
    bool writing = true;
	RSA_API::CONFIG_SetCenterFreq(g_cf);
	RSA_API::CONFIG_SetReferenceLevel(g_refLevel);
	RSA_API::IFSTREAM_SetDiskFilePath(g_fileDir);
	RSA_API::IFSTREAM_SetDiskFilenameBase(g_fileName);
	RSA_API::IFSTREAM_SetDiskFilenameSuffix(-2);
	RSA_API::IFSTREAM_SetDiskFileLength(g_durationMsec);
	RSA_API::IFSTREAM_SetDiskFileMode(RSA_API::StreamingModeFramed);
	RSA_API::IFSTREAM_SetDiskFileCount(1);

	RSA_API::DEVICE_Run();
	RSA_API::IFSTREAM_SetEnable(true);
	while (writing == true)
	{
		sleep(g_waitTime/1000);
		RSA_API::IFSTREAM_GetActiveStatus(&writing);
	}
	RSA_API::DEVICE_Stop();

	std::cout << "\nIF stream aquried,  a big output file was made ,  any key to continue:  ";
	std::cin >> holder;
	RSA_API::DEVICE_Disconnect();
*/