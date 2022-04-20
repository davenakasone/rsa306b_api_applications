/*
    using "cpp_IF_steam_v1/"
    make a file to plot data
*/

#include "unit_tests.h"

#define FILES_MADE 11


void vvv_993()
{
    printf("\n%s()  , checking ...\n\n", __func__);
    bool is_writing = true;
    char output_dir[BUF_A] = "./testz/test_outputs_r3f/";
    char file_name[BUF_A];
    double cf = 100e6;
    double rl = -30;
    rsa306b rsa;           

    rsa.device_connect(); 
    rsa.config_update_cf_rl(cf, rl);
    RSA_API::IFSTREAM_SetDiskFileCount(1);
    RSA_API::IFSTREAM_SetDiskFilenameSuffix(-2);
    RSA_API::IFSTREAM_SetDiskFilePath(output_dir);
    RSA_API::IFSTREAM_SetDiskFileMode(RSA_API::StreamingModeFramed);

    for (int ii = 0; ii < FILES_MADE; ii++)
    {
        snprintf(file_name, BUF_A-1, "duration_%dms", ii+1);
        RSA_API::IFSTREAM_SetDiskFilenameBase(file_name);
        RSA_API::IFSTREAM_SetDiskFileLength(ii+1);

        rsa.device_run();
	    RSA_API::IFSTREAM_SetEnable(true);
        while (is_writing == true)
        {
            //sleep(g_waitTime/1000);
            RSA_API::IFSTREAM_GetActiveStatus(&is_writing);
        }
        RSA_API::IFSTREAM_SetEnable(false);
        rsa.device_stop();
        is_writing = true;
        printf("\tfile made,  '%s%s'\n", output_dir, file_name);
    }
	
    printf("\nfiles aquired, look in '%s' for %d '*.r3f' files\n",
        output_dir, FILES_MADE);
    printf("\n%s()  ,  test complete\n", __func__); 
}


/////////~~~~~~~~END>  vvv_993.cpp
