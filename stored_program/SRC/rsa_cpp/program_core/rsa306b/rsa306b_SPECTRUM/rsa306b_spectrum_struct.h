/*
    variables needed for the API group "SPECTRUM" 
        SPECTRUM_AquireTrace()
        SPECTRUM_GetEnable()         , SPECTRUM_SetEnable()
        SPECTRUM_GetLimits()
        SPECTRUM_GetSettings()       , SPECTRUM_SetSettings()
        SPECTRUM_GetTrace()
        SPECTRUM_GetTraceInfo()
        SPECTRUM_GetTraceType()      , SPECTRUM_SetTraceType()
        SPECTRUM_SetDefault()        
        SPECTRUM_WaitForTraceReady()

    active :
        bool                            is_enabled_measurement
        RSA_API::Spectrum_Limits        limits_type
        RSA_API::Spectrum_Settings      settings_type
        RSA_API::SpectrumTraces         trace_select[TRACES_306B]
        int                             trace_points_acquired[TRACES_306B]
        std::vector<float>              trace_power_v
        RSA_API::Spectrum_TraceInfo     trace_info_type[TRACES_306B]
        char                            acq_status_messages[SPECTRUM_BITCHECKS][BUF_D]
        bool                            is_enabled_trace[TRACES_306B]
        RSA_API::SpectrumDetectors      detector_select[TRACES_306B]
        std::vector<double>             frequency_v
        std::size_t                     peak_index[TRACES_306B]

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/

#ifndef H_rsa306b_spectrum_struct
#define H_rsa306b_spectrum_struct


#include "../../control/resourcez.h"


struct rsa306b_spectrum_struct
{


// limiting constants
    const int LOOP_LIMIT_MS = 100;    // maximum time, in milli-seconds, to loiter in a loop and wait for data acquisition


/*
    SPECTRUM_AquireTrace()
        parameters must be set to valid states before calling
        initiates the trace acquisition
*/


/*
    SPECTRUM_GetEnable(), SPECTRUM_SetEnable()
        get/set enable status of the spectrum
        "true" means spectrum measurement is enabled
        "false" means spectrum measurement is disabled
            is_enabled_measurement ;  if the device is enabled for measurement
*/
    bool       is_enabled_measurement;
    const bool _IS_ENABLED_MEASUREMENT = false;    // DEFAULT


/*
    SPECTRUM_GetLimits()
        be careful if it is 64-bit API or 32-bit API, this effects limits
        good to call this function, and use limits to guard other API calls
        RSA_API::Spectrum_Limits
            maxSpan        ; device dependent...RSA306B should be 40 MHz
            minSpan        ; 1 kHz or 100 kHz    // 64-bit or 32-bit
            maxRBW         ; 10 MHz
            minRBW         ; 10 Hz or 100 Hz     // 64-bit or 32-bit
            maxVBW         ; 10 MHz
            minVBW         ; 1 Hz or 100 Hz      // 64-bit or 32-bit
            maxTraceLength ; 64001
            minTraceLength ; 801

*/
    RSA_API::Spectrum_Limits limits_type;
    const double             _LIMITS_TYPE_maxSpan        = INIT_DOUBLE;    // DEFAULT
    const double             _LIMITS_TYPE_minSpan        = INIT_DOUBLE;    // DEFAULT
    const double             _LIMITS_TYPE_maxRBW         = INIT_DOUBLE;    // DEFAULT
    const double             _LIMITS_TYPE_minRBW         = INIT_DOUBLE;    // DEFAULT
    const double             _LIMITS_TYPE_maxVBW         = INIT_DOUBLE;    // DEFAULT
    const double             _LIMITS_TYPE_minVBW         = INIT_DOUBLE;    // DEFAULT
    const int                _LIMITS_TYPE_maxTraceLength = INIT_INT;       // DEFAULT
    const int                _LIMITS_TYPE_minTraceLength = INIT_INT;       // DEFAULT

		
/*
    SPECTRUM_GetSettings(), SPECTRUM_SetSettings()
        get/set the settings for the spectrum API group
        RSA_API::Spectrum_Settings 
            span                           ; must be in range
			rbw                            ; must be in range
			enableVBW                      ; turn video on or off (true/false)
			vbw                            ; must be in range
			traceLength                    ; must be an odd number, must be in range
			RSA_API::SpectrumWindows       ; RSA enum, what type of filtering window gets applied to the transform
			RSA_API::SpectrumVerticalUnits ; RSA enum, what power is measured in for 'frequency vs power'
			actualStartFreq                ; only valid when calling 'SPECTRUM_GetSettings()' ... in Hz
			actualStopFreq                 ; only valid when calling 'SPECTRUM_GetSettings()' ... in Hz
			actualFreqStepSize             ; only valid when calling 'SPECTRUM_GetSettings()' ... in HZ
			actualRBW                      ; only valid when calling 'SPECTRUM_GetSettings()' ... in Hz
			actualVBW                      ; only valid when calling 'SPECTRUM_GetSettings()' ... not used
			actualNumIQSamples             ; only valid when calling 'SPECTRUM_GetSettings()' ... IQ samples for transform
*/
    RSA_API::Spectrum_Settings           settings_type;   
    const double                         _SETTINGS_TYPE_span               = 10e6;                                                        // DEFAULT
    const double                         _SETTINGS_TYPE_rbw                = 1e3;                                                         // DEFAULT
    const bool                           _SETTINGS_TYPE_enableVBW          = false;                                                       // DEFAULT
    const double                         _SETTINGS_TYPE_vbw                = INIT_DOUBLE;                                                 // DEFAULT
    const int                            _SETTINGS_TYPE_traceLength        = 901;                                                         // DEFAULT
    const RSA_API::SpectrumWindows       _SETTINGS_TYPE_WINDOW             = RSA_API::SpectrumWindows::SpectrumWindow_Kaiser;             // DEFAULT
    const RSA_API::SpectrumVerticalUnits _SETTINGS_TYPE_verticalUint       = RSA_API::SpectrumVerticalUnits::SpectrumVerticalUnit_dBm;    // DEFAULT
    const double                         _SETTINGS_TYPE_actualStartFreq    = INIT_DOUBLE;                                                 // DEFAULT
    const double                         _SETTINGS_TYPE_actualStopFreq     = INIT_DOUBLE;                                                 // DEFAULT
    const double                         _SETTINGS_TYPE_actualFreqStepSize = INIT_DOUBLE;                                                 // DEFAULT
    const double                         _SETTINGS_TYPE_actualRBW          = INIT_DOUBLE;                                                 // DEFAULT
    const double                         _SETTINGS_TYPE_actualVBW          = INIT_DOUBLE;                                                 // DEFAULT
    const int                            _SETTINGS_TYPE_actualNumIQSamples = INIT_INT;                                                    // DEFAULT


/*
    SPECTRUM_GetTrace()
        get the specified trace, if data is available
            RSA_API::SpectrumTraces ; select a valid trace, the RSA-306B has 3
            trace_power_v           ; collects data for each trace when acquisition occurs
            trace_points_acquired   ; how many trace points were acquired, used for verification
            'maxTracePoints'        ; what to allocate float*, how many points to get, uses 'spectrum.settings_type.traceLength'
*/
    RSA_API::SpectrumTraces         trace_select[TRACES_306B];
    const RSA_API::SpectrumTraces   _TRACE_SELECT[TRACES_306B] =                     // DEFAULT
        {
            RSA_API::SpectrumTraces::SpectrumTrace1, 
            RSA_API::SpectrumTraces::SpectrumTrace2,   
            RSA_API::SpectrumTraces::SpectrumTrace3
        }; 

    int                             trace_points_acquired[TRACES_306B];
    const int                       _TRACE_POINTS_ACQURIED     = INIT_INT;           // DEFAULT

    std::vector<float> trace_power_v[TRACES_306B];
    const std::size_t               _TRACE_POWER_V_size        = INIT_STL_LENGTH;    // DEFAULT
    const float                     _TRACE_POWER_V_element     = INIT_FLOAT;         // DEFAULT


/*
    SPECTRUM_GetTraceInfo()
        designed to be called after aquiring each trace
        RSA_API::Spectrum_TraceInfo
            timestamp           ; for first sample's acquisition, use REFTIME to help
            acqDataStatus       ; see bitchecks
            acq_status_messages ; records failures, if any
            valid_bitmask       ; for user's conveince
*/
    RSA_API::Spectrum_TraceInfo trace_info_type[TRACES_306B];  
    const uint64_t              _TRACE_INFO_TYPE_timestamp     = 0;                   // DEFAULT
    const uint16_t              _TRACE_INFO_TYPE_acqDataStatus = BITCHECK_SUCCESS;    // DEFAULT

    char        acq_status_messages[SPECTRUM_BITCHECKS][BUF_D];
    //const char* _ACQ_STATUS_MESSAGES                           = BITCHECK_SUCCESS_MESSAGE;    // DEFAULT
    
    const uint16_t valid_bitmask                               = 
        (
            static_cast<uint16_t>(RSA_API::AcqDataStatus_ADC_OVERRANGE	)    |    // bit 0
            static_cast<uint16_t>(RSA_API::AcqDataStatus_REF_OSC_UNLOCK)     |    // bit 1
            static_cast<uint16_t>(RSA_API::AcqDataStatus_LOW_SUPPLY_VOLTAGE) |    // bit 4
            static_cast<uint16_t>(RSA_API::AcqDataStatus_ADC_DATA_LOST)           // bit 5
        );

/*
    SPECTRUM_GetTraceType(), SPECTRUM_SetTraceType()
        get/set characteristics for each trace
            'RSA_API::SpectrumTraces'  ; use "trace_select[]" to select the trace
            is_enabled_trace           ; [], tracks which trace is enabled, set to false to disable
            RSA_API::SpectrumDetectors ; detector type of the trace 
*/
    bool       is_enabled_trace[TRACES_306B];
    const bool _IS_ENABLED_TRACE[TRACES_306B] = // DEFAULT
        {
            true,
            false,
            false
        };

    RSA_API::SpectrumDetectors       detector_select[TRACES_306B];    
    const RSA_API::SpectrumDetectors _DETECTOR_SELECT[TRACES_306B] =    // DEFAULT
        {
            RSA_API::SpectrumDetectors::SpectrumDetector_PosPeak,
            RSA_API::SpectrumDetectors::SpectrumDetector_PosPeak,
            RSA_API::SpectrumDetectors::SpectrumDetector_PosPeak
        };

/*
    SPECTRUM_SetDefault()
        apply default settings
        does not change enable status of the spectrum
            span         = 40 MHz
            rbw          = 300 kHz
            vbw          = 300 kHz
            traceLength  = 801
            window       = Kaiser
            veritcalUnit = dBm
            trace1 is enabled , peak+
            trace2 is disabled, peak-
            trace3 is disabled, average
*/


/*
    SPECTRUM_WaitForTraceReady()
        uses scopped int set to LOOP_TIMEOUT_MS
        uses scopped bool to check if ready
        if timeout macro is active, timeout is applied,
        else loop will poll until data is ready
*/


// extras
    std::vector<double> frequency_v;
    const std::size_t   _FREQUENCY_V_size = INIT_STL_LENGTH;    // DEFAULT
    const float         _FREQUENCY_V_element = INIT_DOUBLE;     // DEFAULT

    std::size_t        peak_index[TRACES_306B];
    const std::size_t  _PEAK_INDEX = INIT_STD_SIZE_T;          // DEFAULT


};
typedef struct rsa306b_spectrum_struct rsa306b_spectrum_struct;


#endif


////////~~~~~~~~END>  rsa306b_spectrum_struct.h
        