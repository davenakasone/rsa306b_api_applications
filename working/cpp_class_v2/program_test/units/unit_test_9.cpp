/*
    unit test # 9, API group "IFSTREAM"

    this section is used to write .r3f files
    more capabilities should be added to handle real-time ADC processing

    goals:
        - getters, setters, copiers working correctly
        - a valid "*.r3f" file can be written
*/

#include "../testz.h"

//#define UT9_a 1    // basic test
//#define UT9_b 2      // make an output file
#define UT9_c 3      // make several output files and process them to raw ADC


void unit_test_9 (void)
{
    printf("\n%s()  ,  API group 'IFSTREAM'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        r3f_manager_class r3f;
        rsa.device_connect();

        #ifdef UT9_a
            rsa.print_ifstream();

            rsa.vars.ifstream.file_count = 3;
            rsa.vars.ifstream.file_length_ms = 3000;
            strcpy(rsa.vars.ifstream.file_name_base, "toppy");
            rsa.vars.ifstream.file_name_suffix = 9;
            strcpy(rsa.vars.ifstream.file_path, "sloppy");
            rsa.vars.ifstream.is_enabled_adc = true;
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_MIDAS_DET;
            rsa.ifstream_set_vars();
            
            rsa.print_ifstream();
        #endif
        #ifdef UT9_b
            rsa.vars.config.reference_level_dbm = -45;
            rsa.vars.config.center_frequency_hz = 150e6;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.ifstream.file_count = 1;
            rsa.vars.ifstream.file_length_ms = 30;
            //strcpy(rsa.vars.ifstream.file_name_base, "tryR3F");
            rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_TIMESTAMP;
            //strcpy(rsa.vars.ifstream.file_path, "./program_test/data/outputs_r3f/");
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            rsa.ifstream_set_vars();

            rsa.ifstream_record_file(); // using default settings
            rsa.print_ifstream();
        #endif
        #ifdef UT9_c
            rsa.vars.config.reference_level_dbm = -45;
            rsa.vars.config.center_frequency_hz = 150e6;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.vars.ifstream.file_length_ms = 10;
            rsa.vars.ifstream.file_name_suffix = RSA_API::IFSSDFN_SUFFIX_TIMESTAMP;
            rsa.vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
            rsa.ifstream_set_vars();
            rsa.print_ifstream();

            int repz = 5;
            for (int ii = 0; ii < repz; ii++)
            {
                rsa.ifstream_record_file();
            }
            r3f.prepare_plot_from_adc(rsa.vars.ifstream.file_path, rsa.vars.constants.IFSTREAM_CSV_PATH);
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_9.cpp
