/*
    variables needed for the API group "CONFIG" 
        CONFIG_GetCenterFreq()              , CONFIG_SetCenterFreq()
        CONFIG_GetExternalRefFrequency() 
        CONFIG_GetFrequecnyReferenceSource(), CONFIG_SetFrequencyReferenceSource()
        CONFIG_GetMaxCenterFreq()           , GetMinCenterFreq()
        CONFIG_GetReferenceLevel()          , CONFIG_SetReferenceLevel()
        CONFIG_Preset()
        
    obsolete :
        CONFIG_GetExternalRefEnable()
        CONFIG_SetExternalRefEnable()

    active :
        double                  center_frequency_hz
        double                  external_reference_frequency_hz
        RSA_API::FREQREF_SOURCE frequency_reference_source_select
        double                  max_center_frequency_hz
        double                  min_center_frequency_hz
        double                  reference_level_dbm
        
    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/


#ifndef H_rsa306b_config_struct
#define H_rsa306b_config_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_config_struct
{


// limiting constants :
    const double REFERENCE_LEVEL_MAX_DBM = 30.0;      // highest measurable signal power
    const double REFERENCE_LEVEL_MIN_DBM = -130.0;    // smallest measurable signal power
    const double EXTERNAL_FREQUENCY      = 10e6;      // external reference frequency, required
    const double EXTERNAL_AMPLITUDE_DBM  = 10;        // allows +/- 10 dbm maximum amplitude  
    
/*
    CONFIG_GetCenterFreq(), CONFIG_SetCenterFreq()
        get/set the center frequency, set the TRKGEN first if you have RSA500
        this center frequency determines where spectrum is centered
        limited by variables after finding min/max center frequency range
*/
    double       center_frequency_hz;
    const double _CENTER_FREQUENCY_HZ = 315.0e6;    // DEFAULT


/*
    CONFIG_GetExternalRefFrequency()
        external frequency must be enabled in order to query a useful result
*/
    double       external_reference_frequency_hz;
    const double _EXTERNAL_REFERENCE_FREQUENCY_HZ = INIT_DOUBLE;    // DEFAULT


/*
    CONFIG_GetFrequnecyReferenceSource(), CONFIG_SetFrequnecyReferenceSource()
        get/set the frequency reference source
        note that the RSA306b can only use "INTERNAL" and "EXTERNAL" references
        uses the RSA_API emum
        internal reference source is always valid, never changed unless requested
        external reference source uses signal connected to "Ref in" SMA connector
            this frequency drives the internal oscillators
            if no connection is provided, the switch to "internal" will be automatic
            if the PLL can't lock, then an error will result
*/
    RSA_API::FREQREF_SOURCE       frequency_reference_source_select;
    const RSA_API::FREQREF_SOURCE _FREQUENCY_REFERENCE_SOURCE_SELECT = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;    // DEFAULT


/*
    CONFIG_GetMaxCenterFreq(), CONFIG_GetMinCenterFreq()
        query to deternine the range on max/min center frequency
        can change with temperature
        used to limit "center_frequency_hz"
*/
    double       max_center_frequency_hz;
    const double _MAX_CENTER_FREQUENCY_HZ = INIT_DOUBLE;    // DEFAULT

    double       min_center_frequency_hz;
    const double _MIN_CENTER_FREQUENCY_HZ = INIT_DOUBLE;    // DEFAULT


/*
    CONFIG_GetReferenceLevel(), CONFIG_SetReferenceLevel()
        this should be set to highest possible signal input power (dBm) that may be measured
        signal path gain through VGA and attentuation will be determined by this
        too low :
            signal path is overdriven and ADC reads nonsense
        too high :
            signal has a lot of extra noise
        limited by :
            "REFERENCE_LEVEL_MAX_DBM"
            "REFERENCE_LEVEL_MIN_DBM"
*/
    double       reference_level_dbm;    
    const double _REFERENCE_LEVEL_DBM = -15.7;    // DEFAULT


/*
    CONFIG_Preset()
        good function to call when starting the device
        - trigger mode set to "free run"
        - center frequency set to 1.5 GHz
        - span set to 40 MHz
        - IQ record length set to 1024 samples
        - reference level is set to 0 dBm
*/


};
typedef struct rsa306b_config_struct rsa306b_config_struct;


#endif


////////~~~~~~~~END>  rsa306b_config_struct.h
