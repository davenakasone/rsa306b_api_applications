/*
    implementation of the essential components in the rsa306b class
    functions and members of "general purpose"

        public:
            < 1 >  rsa306b()
            < 2 >  ~rsa306b()
            < 3 >  get_api_return_status()
            < 4 >  get_api_return_status_string()
            < 5 >  get_gp_return_status()
            < 6 >  print_constants()
            < 7 >  print_variables()

        private:
            < 1 >  _api_error_check()
            < 2 >  _gp_error_check()
            < 3 >  _init_member_variables()
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    the constructor for the class
    there is no need for multiple constructors (for now)
    ensures all variables are initialized to known values
*/
rsa306b::rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  constructor\n",
        __LINE__, __FILE__, __func__);
#endif
    #ifdef DEBUG_MIN
        printf("\n\tinstance constructed\n");
    #endif
    this->_init_member_variables();
    this->_api_error_check();
    this->_gp_error_check();
}


////~~~~


/*
    public < 2 >
    the desctructor for the class
    stops a running device, if running
    disconnects a connected device, if connected
    deallocates dynamic member variables if necessary
*/
rsa306b::~rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  destructor\n",
        __LINE__, __FILE__, __func__);
#endif

    this->device_disconnect();
    #ifdef DEBUG_MIN
        printf("\n\tdestroyed\n");
    #endif
}


////~~~~


/*
    public < 3 >
    returns integer matching the error in the API enum
    user is responsible for matching the value
*/
RSA_API::ReturnStatus rsa306b::get_api_return_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    return this->_api_return_status;
}


////~~~~


/*
    public < 4 >
    updates string with API return status and error message
    caller must allocate input string, make at least 256 chars
*/
void rsa306b::get_api_return_status_string(char* carrier)
{
#ifdef DEBUG_CL
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (carrier == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the string before calling\n");
        #endif
        return;
    }

    const char* temp = NULL;
    temp = RSA_API::DEVICE_GetErrorString(this->_api_return_status);
    snprintf(carrier, BUF_D-1, 
        "error code:  %d  ,  error message:  %s", this->_api_return_status, temp);
    temp = NULL;
}


////~~~~


/*
    public < 5 >
    returns current state of gp return status indicator
*/
int rsa306b::get_gp_return_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
   return this->_gp_return_status;
}


////~~~~


/*
    public < 6 >
    call to print class constants 
    individual class constants and macros are publically availible 
    it is not possible for user to change "const <data_type>" members
*/
void rsa306b::print_constants()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    printf("\nclass macros >>>\n");
    #ifdef DEBUG_CLI
        printf("\tDEBUG_CLI               :  %d\n", DEBUG_CLI);
    #endif
    #ifdef DEBUG_MIN
        printf("\tDEBUG_MIN               :  %d\n", DEBUG_MIN);
    #endif
    #ifdef DEBUG_ERR
        printf("\tDEBUG_ERR               :  %d\n", DEBUG_ERR);
    #endif
    printf("\tBUF_A                 :  %d\n", BUF_A);
    printf("\tBUF_B                 :  %d\n", BUF_B);
    printf("\tBUF_C                 :  %d\n", BUF_C);
    printf("\tBUF_D                 :  %d\n", BUF_D);
    printf("\tBUF_E                 :  %d\n", BUF_E);
    printf("\tBUF_F                 :  %d\n", BUF_F);
    printf("\tSPECTRUM_DATA_LENGTH  :  %d\n", SPECTRUM_DATA_LENGTH);
    printf("\tAUDIO_DATA_LENGTH     :  %d\n", AUDIO_DATA_LENGTH);
    printf("\nclass constants >>>\n");
    printf("\tCALL_SUCCESS                          :  %d\n", this->CALL_SUCCESS);
    printf("\tCALL_FAILURE                          :  %d\n", this->CALL_FAILURE);
    printf("\tINIT_CHAR                             :  %c\n", this->INIT_CHAR);
    printf("\tINIT_DOUBLE                           :  %lf\n", this->INIT_DOUBLE);
    printf("\tINIT_INT                              :  %d\n", this->INIT_INT);
    printf("\tINIT_STR                              :  %s\n", this->INIT_STR);
    printf("\tEXTERNAL_FREQUENCY                    :  %lf  Hz\n", this->EXTERNAL_FREQUENCY);
    printf("\tEXTERNAL_AMPLITUDE_dbm                :  %lf +/- dbm\n", this->EXTERNAL_AMPLITUDE_dbm);
    printf("\tREFERENCE_LEVEL_MAX_dbm               :  %lf  dbm\n", this->REFERENCE_LEVEL_MAX_dbm);
    printf("\tREFERENCE_LEVEL_MIN_dbm               :  %lf  dbm\n", this->REFERENCE_LEVEL_MIN_dbm);
    printf("\tSPAN_MAX_Hz                           :  %lf  Hz\n", this->SPAN_MAX_Hz);
    printf("\tSPAN_MIN_Hz                           :  %lf  Hz\n", this->SPAN_MIN_Hz);
    printf("\tPOSITION_PERCENT_MAX                  :  %lf  Hz\n", this->POSITION_PERCENT_MAX);
    printf("\tPOSITION_PERCENT_MIN                  :  %lf  Hz\n", this->POSITION_PERCENT_MIN);
    printf("\tAUDIO_VOLUME_MAX                      :  %f\n", this->AUDIO_VOLUME_MAX);
    printf("\tAUDIO_VOLUME_MIN                      :  %f\n", this->AUDIO_VOLUME_MIN);
    printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz  :  %lf\n", this->AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz);
    printf("\tAUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz  :  %lf\n", this->AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz);
}


////~~~~


/*
    public < 7 >
    prints device member variables
    organized by API function group
*/
void rsa306b::print_variables()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  destructor\n",
        __LINE__, __FILE__, __func__);
#endif
    
    this->audio_print_all();
    this->align_print_all();
    this->config_print_all();
    this->device_print_all();
    this->reftime_print_all();
    this->spectrum_print_all();
    this->trig_print_all();
}


////~~~~


/*
    private < 1 >
    matches current state of the ReturnStatus variable to the enum
    indicates if an error has occured, otherwise does nothing
    good practice to call after each API function is used, unless speed is needed
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b::_api_error_check()
{
#ifdef DEBUG_ERR
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_api_return_status != RSA_API::noError)
    {
        #if defined (DEBUG_ERR) || (DEBUG_MIN)
            this->get_api_return_status_string(this->_helper_string);
            printf("\n\t###   !!!   API ERROR   !!!   ###   %s\n", 
                this->_helper_string);
        #endif
    }
}


////~~~~


/*
    private < 2 >
    called to indicate error conditions 
        after calling non-API 'general purpouse' functions
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b::_gp_error_check()
{
#ifdef DEBUG_ERR
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #if defined (DEBUG_ERR) || (DEBUG_MIN)
            printf("\n\t###   !!! ERROR  IN THE OBJECT !!!   ###\n");
        #endif
    }
}


////~~~~


/*
    private < 3 >
    call any time member variables should be reset to known values
    deallocates dynamically member variables if needed, and places on NULL
    initialization values are in "rsa306b_class.h"
    this is the only function that changes values without using setters 
    this function should only be called by the constructor
*/
void rsa306b::_init_member_variables()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    // general purpose
    memset(this->_helper_string, '\0', BUF_E);
    memset(this->_holder_string, '\0', BUF_F);
    this->_api_return_status = RSA_API::noError;
    this->_gp_return_status = this->CALL_SUCCESS;

    // ALIGN
    this->_align_need_alignment = false;
    this->_align_is_warmed = false;

    // AUDIO
    this->_audio_type.center_frequency_offset_hz = this->INIT_DOUBLE;
    this->_audio_type.demodulation_mode_select = RSA_API::ADM_AM_8KHZ;
    this->_audio_type.is_demodulating = false;
    this->_audio_type.is_mute = true;
    this->_audio_type.volume = this->INIT_FLOAT;
    this->_audio_type.data_length_received = 0;
    for (int ii = 0; ii < AUDIO_DATA_LENGTH; ii++)
    {
        this->aduio_data[ii] = 0;
    }

    // CONFIG
    this->_config_center_frequency_hz = this->INIT_DOUBLE;
    this->_config_center_frequency_max_hz = -6.2e9;
    this->_config_center_frequency_min_hz = -9e3;
    this->_config_reference_level_dbm = this->INIT_DOUBLE;
    this->_config_external_reference_frequency_hz = this->INIT_DOUBLE;
    this->_config_frequency_reference_source_select = RSA_API::FRS_INTERNAL;

    // DEVICE
    this->_device_is_connected = false;
    this->_device_is_over_temperature = false;
    this->_device_is_running = false;
    this->_device_id = this->INIT_INT;
    strcpy(this->_device_info_type.apiVersion, this->INIT_STR);
    strcpy(this->_device_info_type.fpgaVersion, this->INIT_STR);
    strcpy(this->_device_info_type.fwVersion, this->INIT_STR);
    strcpy(this->_device_info_type.hwVersion, this->INIT_STR);
    strcpy(this->_device_info_type.nomenclature, this->INIT_STR);
    strcpy(this->_device_info_type.serialNum, this->INIT_STR);

    // REFTIME
    memset(this->_reftime_date_timestamp, '\0', BUF_C);
    this->_reftime_running = this->INIT_DOUBLE;
    this->_reftime_split = this->INIT_DOUBLE;
    this->_reftime_split_lead = this->INIT_DOUBLE;
    this->_reftime_split_trail = this->INIT_DOUBLE;
    this->_reftime_source_select = RSA_API::RTSRC_NONE;
    this->_reftime_timestamp_rate = this->INIT_INT;
    this->_reftime_begin_type.seconds = this->INIT_INT;
    this->_reftime_begin_type.nanos = this->INIT_INT;
    this->_reftime_begin_type.stamp = this->INIT_INT;
    this->_reftime_current_type.seconds = this->INIT_INT;
    this->_reftime_current_type.nanos = this->INIT_INT;
    this->_reftime_current_type.stamp = this->INIT_INT;

    // SPECTRUM
    this->_spectrum_valid_trace_points = this->INIT_INT;
    this->_spectrum_good_aquisition = false;
    this->_spectrum_measurement_enabled = false;
    for (int ii = 0; ii < SPECTRUM_DATA_LENGTH; ii++)
    {
        this->_spectrum_frequency_array[ii] = this->INIT_DOUBLE;
        this->_spectrum_trace_data[0][ii] = this->INIT_FLOAT;
        this->_spectrum_trace_data[1][ii] = this->INIT_FLOAT;
        this->_spectrum_trace_data[2][ii] = this->INIT_FLOAT;
    }
    this->_spectrum_3_traces_type.trace_enabled[0] = false;
    this->_spectrum_3_traces_type.trace_enabled[1] = false;
    this->_spectrum_3_traces_type.trace_enabled[2] = false;
    this->_spectrum_3_traces_type.detector_select[0] = RSA_API::SpectrumDetector_Sample;
    this->_spectrum_3_traces_type.detector_select[1] = RSA_API::SpectrumDetector_Sample;
    this->_spectrum_3_traces_type.detector_select[2] = RSA_API::SpectrumDetector_Sample;
    this->_spectrum_3_traces_type.trace_select[0] = RSA_API::SpectrumTrace1;
    this->_spectrum_3_traces_type.trace_select[1] = RSA_API::SpectrumTrace2;
    this->_spectrum_3_traces_type.trace_select[2] = RSA_API::SpectrumTrace3;
    this->_spectrum_limits_type.maxRBW = this->INIT_DOUBLE;    
    this->_spectrum_limits_type.maxSpan = this->INIT_DOUBLE;
    this->_spectrum_limits_type.maxTraceLength = INIT_INT;
    this->_spectrum_limits_type.maxVBW = this->INIT_DOUBLE;
    this->_spectrum_limits_type.minRBW = this->INIT_DOUBLE;
    this->_spectrum_limits_type.minSpan = this->INIT_DOUBLE;
    this->_spectrum_limits_type.minTraceLength = this->INIT_INT;
    this->_spectrum_limits_type.minVBW = this->INIT_DOUBLE;
    this->_spectrum_settings_type.actualFreqStepSize = this->INIT_DOUBLE;
    this->_spectrum_settings_type.actualNumIQSamples = this->INIT_INT;
    this->_spectrum_settings_type.actualRBW = this->INIT_DOUBLE;
    this->_spectrum_settings_type.actualStartFreq = this->INIT_DOUBLE;
    this->_spectrum_settings_type.actualStopFreq = this->INIT_DOUBLE;
    this->_spectrum_settings_type.actualVBW = this->INIT_DOUBLE;
    this->_spectrum_settings_type.enableVBW = false;
    this->_spectrum_settings_type.rbw = this->INIT_DOUBLE;
    this->_spectrum_settings_type.span = this->INIT_DOUBLE;
    this->_spectrum_settings_type.traceLength = this->INIT_INT;
    this->_spectrum_settings_type.vbw = this->INIT_DOUBLE;
    this->_spectrum_settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_Watt;
    this->_spectrum_settings_type.window = RSA_API::SpectrumWindow_Mil6dB;
    this->_spectrum_trace_info_type.acqDataStatus = RSA_API::AcqDataStatus_ADC_DATA_LOST;
    this->_spectrum_trace_info_type.timestamp = this->INIT_INT;  

    // TRIG
    this->_trig_type.if_power_level = this->INIT_DOUBLE;
    this->_trig_type.position_percent = this->INIT_DOUBLE;
    this->_trig_type.mode_select = RSA_API::triggered;
    this->_trig_type.source_select = RSA_API::TriggerSourceExternal;
    this->_trig_type.transition_select = RSA_API::TriggerTransitionHL;  

    #ifdef DEBUG_MIN
        printf("\n\tclass members initialized\n");
    #endif
}
       

////////~~~~~~~~END>  rsa306b_class__gp.cpp
