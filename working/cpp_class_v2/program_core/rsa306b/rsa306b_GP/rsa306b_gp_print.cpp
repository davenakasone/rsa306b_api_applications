/*
    printing functions for the "general purpose" group

        public :
            < 1 >  print_everything()
            < 2 >  print_constants()
            < 3 >  print_gp()
        
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
void rsa306b_class::print_everything()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->print_constants();
    this->print_gp();
    this->print_align();
    this->print_audio();
    this->print_config();
    this->print_device();
    this->print_reftime();
    this->print_trig();

    // INSERT
} 


////~~~~


/*
    < 2 > public
    prints class constants to stdout
*/
void rsa306b_class::print_constants()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'constants' group >>>\n");
    printf("\tCALL_SUCCESS                          :  %d\n", this->_vars.constants.CALL_SUCCESS);
    printf("\tCALL_FAILURE                          :  %d\n", this->_vars.constants.CALL_FAILURE);
    printf("\tINIT_CHAR                             :  %c\n", this->_vars.constants.INIT_CHAR);
    printf("\tINIT_DOUBLE                           :  %lf\n", this->_vars.constants.INIT_DOUBLE);
    printf("\tINIT_INT                              :  %d\n", this->_vars.constants.INIT_INT);
    printf("\tINIT_UINT                             :  %u\n", this->_vars.constants.INIT_UINT);
    printf("\tINIT_STR                              :  %s\n", this->_vars.constants.INIT_STR);
    printf("\tEXTERNAL_FREQUENCY                    :  %lf  Hz\n", this->_vars.constants.EXTERNAL_FREQUENCY);
    printf("\tEXTERNAL_AMPLITUDE_dbm                :  %lf +/- dbm\n", this->_vars.constants.EXTERNAL_AMPLITUDE_dbm);
    printf("\tREFERENCE_LEVEL_MAX_dbm               :  %lf  dbm\n", this->_vars.constants.REFERENCE_LEVEL_MAX_dbm);
    printf("\tREFERENCE_LEVEL_MIN_dbm               :  %lf  dbm\n", this->_vars.constants.REFERENCE_LEVEL_MIN_dbm);
    printf("\tSPAN_MAX_Hz                           :  %lf  Hz\n", this->_vars.constants.SPAN_MAX_Hz);
    printf("\tSPAN_MIN_Hz                           :  %lf  Hz\n", this->_vars.constants.SPAN_MIN_Hz);
    printf("\tPOSITION_PERCENT_MAX                  :  %lf  Hz\n", this->_vars.constants.POSITION_PERCENT_MAX);
    printf("\tPOSITION_PERCENT_MIN                  :  %lf  Hz\n", this->_vars.constants.POSITION_PERCENT_MIN);
    printf("\tAUDIO_VOLUME_MAX                      :  %f\n", this->_vars.constants.AUDIO_VOLUME_MAX);
    printf("\tAUDIO_VOLUME_MIN                      :  %f\n", this->_vars.constants.AUDIO_VOLUME_MIN);
    printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz  :  %lf\n", this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
    printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz  :  %lf\n", this->_vars.constants.AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz);
}


////~~~~


/*
    < 3 > public
    prints "gp" group variables to stdout
*/
void rsa306b_class::print_gp()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'general purpose' group >>>\n");
    printf("\tcall status          :  %d\n", this->_vars.gp.call_status);
    if (this->_vars.device.is_connected == true)
    {
        this->_device_get_error_string();
        printf("\tAPI status           :  %d  (%s)\n", 
            (int)this->_vars.gp.api_status,
            this->_vars.device.error_string);
    }
    else
    {
        printf("\tAPI status           :  %d  (not connected) \n", (int)this->_vars.gp.api_status);
    }
    printf("\tacquistion  code     :  0x%X\n", this->_vars.gp.acquisition_code);
    printf("\tacquisition message  :  %s\n", this->_vars.gp.acquisition_message);
    printf("\thelper               :  %s\n", this->_vars.gp.helper);
    printf("\tholder               :  %s\n", this->_vars.gp.holder);
}


////////~~~~~~~~END>  rsa306b_print_constants.cpp
