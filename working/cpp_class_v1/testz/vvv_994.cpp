/*
    using "cpp_IF_steam_v1/"
    it is not necessary to stream to a file
    you can process all the data with IFSTREAM_GetIFData()
        raw singed 16-bit IF sample data is continually produced at 112 Msps
        client must call IFSTREAM_GetIFData() at a rate before the storage buffer overflows
        the RSA storage buffer can only hold about 2.4 seconds of IF data (260 x 10^6 samples)
        just put it in the IFSTRMDATAINFO struct, then process it
    
    the examples use "IFSTREAM_SetDiskFileMode()"
    new API says to use "IFSTREAM_SetOutputConfiguration" instead

    the steamed file is nice to have as a record
    opening it and processing it might be best done with a python script
    streamed IF files in "*.r3f" format are good because they are a raw record of the ADC
    steamed IF files in "*.r3f" format are bad because a 1 TB harddrive will be full in less than 1 hour

    this unit test will produce 5x "*.r3f" files
    file lengths of 1ms : 5ms are recorded
    use the "python_helpers" script to attempt a read after recording
    call "make clean" before pushing to github if files are > 30 MB
*/

#include "unit_tests.h"

#define FILES_MADE 5


void vvv_994()
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


/////////~~~~~~~~END>  vvv_994.cpp
