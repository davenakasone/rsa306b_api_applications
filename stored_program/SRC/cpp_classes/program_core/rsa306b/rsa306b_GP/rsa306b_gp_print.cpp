/*
    printing functions for the "general purpose" group

        public :
            < 1 >  print_everything()
            < 2 >  print_constants()
        
        private :
            #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints class variables and constatns to stdout
    variables are displayed in current state
    uses the private struct
*/
CODEZ rsa306b_class::print_everything()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->print_constants();
    this->print_align();
    this->print_audio();
    this->print_config();
    this->print_device();
    this->print_ifstream();
    this->print_iqblk();
    this->print_iqstream();
    this->print_reftime();
    this->print_spectrum();
    this->print_trig();

    // INSERT
} 


////~~~~


/*
    < 2 > public
    prints class constants to stdout
*/
CODEZ rsa306b_class::print_constants()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'constants' group >>>\n");
    // (void)printf("\tCALL_SUCCESS                          :  %d\n", this->constants.CALL_SUCCESS);
    // (void)printf("\tCALL_FAILURE                          :  %d\n", this->constants.CALL_FAILURE);
    // (void)printf("\tINIT_CHAR                             :  %c\n", this->constants.INIT_CHAR);
    // (void)printf("\tINIT_DOUBLE                           :  %lf\n", this->constants.INIT_DOUBLE);
    // (void)printf("\tINIT_INT                              :  %d\n", this->constants.INIT_INT);
    // (void)printf("\tINIT_UINT                             :  %u\n", this->constants.INIT_UINT);
    // (void)printf("\tINIT_STR                              :  %s\n", this->constants.INIT_STR);
    (void)printf("\tEXTERNAL_FREQUENCY                    :  %lf  Hz\n", this->constants.EXTERNAL_FREQUENCY);
    (void)printf("\tEXTERNAL_AMPLITUDE_dbm                :  %lf +/- dbm\n", this->constants.EXTERNAL_AMPLITUDE_DBM);
    (void)printf("\tREFERENCE_LEVEL_MAX_dbm               :  %lf  dbm\n", this->constants.REFERENCE_LEVEL_MAX_DBM);
    (void)printf("\tREFERENCE_LEVEL_MIN_dbm               :  %lf  dbm\n", this->constants.REFERENCE_LEVEL_MIN_DBM);
    (void)printf("\tSPAN_MAX_Hz                           :  %lf  Hz\n", this->constants.SPAN_MAX_HZ);
    (void)printf("\tSPAN_MIN_Hz                           :  %lf  Hz\n", this->constants.SPAN_MIN_HZ);
    (void)printf("\tPOSITION_PERCENT_MAX                  :  %lf  Hz\n", this->constants.POSITION_PERCENT_MAX);
    (void)printf("\tPOSITION_PERCENT_MIN                  :  %lf  Hz\n", this->constants.POSITION_PERCENT_MIN);
    (void)printf("\tAUDIO_VOLUME_MAX                      :  %f\n", this->constants.AUDIO_VOLUME_MAX);
    (void)printf("\tAUDIO_VOLUME_MIN                      :  %f\n", this->constants.AUDIO_VOLUME_MIN);
    (void)printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz  :  %lf\n", this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
    (void)printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz  :  %lf\n", this->constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz);
    //(void)printf("\tSPECTRUM_CSV_PATH                     :  %s\n", this->constants.SPECTRUM_CSV_PATH);
    (void)printf("\tIFSTREAM_SUFFIX                       :  %d\n", this->constants.IFSTREAM_SUFFIX);
    //(void)printf("\tIFSTREAM_FILE_PATH                    :  %s\n", this->constants.IFSTREAM_FILE_PATH);
    (void)printf("\tIFSTREAM_FILE_NAME_BASE               :  %s\n", this->constants.IFSTREAM_FILE_NAME_BASE);
    (void)printf("\tIFSTREAM_MAX_MS                       :  %d\n", this->constants.IFSTREAM_MAX_MS);
    (void)printf("\tIFSTREAM_DEFAULT_MS                   :  %d\n", this->constants.IFSTREAM_DEFAULT_MS);
    (void)printf("\tIFSTREAM_DEFAULT_FILE_COUNT           :  %d\n", this->constants.IFSTREAM_DEFAULT_FILE_COUNT);
    //(void)printf("\tIFSTREAM_CSV_PATH                     :  %s\n", this->constants.IFSTREAM_CSV_PATH);
}


////////~~~~~~~~END>  rsa306b_print_constants.cpp
