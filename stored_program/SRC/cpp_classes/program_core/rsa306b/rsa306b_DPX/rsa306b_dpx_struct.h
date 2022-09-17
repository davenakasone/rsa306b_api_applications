/*
    variables needed for the API group "DPX" 

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    limiting constants :  <CONSTANT_NAME>             // no leading underscore

    to setup and acquire DPX data :
        1)  stop the device
        2)  setup the DPX
        3)  call DPX_SetEnable() to enable an acquisition
        4)  run the device
        5)  while device is running, call DPX_WaitForDataReady() to wait for frame buffer to become available
        6)  when the frame is available, call DPX_GetFrameBuffer() for bitmaps and traces
        7)  call DPX_FinishFrameBuffer() to indicatd that client is done transfering the data frame
        8)  repeat waiting and taking data for all the frame buffers you want
        9)  when done, and frame buffers are complete, stop the device
        10) for high-resolution lines, if spectrogram is enabled, call these:
                DPX_GetSogramHiResLineCountLatest()
                DPX_GetSogramHiResLine()
                DPX_GetSogramHiResLineTimestamp()
                DPX_GetSogramHiResLineTriggered()
    
    the spectrum bitmap :
        - see page # 36
        - starts in top left, moves right to width - 1
        - has height "height - 1"
        - signal level increase downwards
        - frequency increases to the right
        - each value represents a hit-count on the pixel at the index
        - "x" axis is the spectrum frequency
        - "y" axis is the spectrum signal level
        - DPX_SetParameters() gives you the scale of the bitmap
    
    the sogram bitmpa :
        - see page # 37

    this is a complicated group, there is a lot to understand
*/


#ifndef H_rsa306b_dpx_struct
#define H_rsa306b_dpx_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_dpx_struct
{
/*
    DPX_Configure()
        enables or disables the spectrum and DPX spectrogram modes
        must be called after any DPX settings changed and the device is in the stop state
        this function configures a lot of hardware
*/
    // bool       enable_spectrum;
    // const bool _ENABLE_SPECTRUM = false;       // DEFAULT            use the DPX_SettingStruct....

    // bool       enable_spectrogram;
    // const bool _ENABLE_SPECTROGRAM = false;    // DEFAULT


/*
    DPX_FinishFrameBuffer()
        tells device frame was acquired
        must be called before next frame will be available
*/


/*
    DPX_GetEnable(), DPX_SetEnable()
        state of the DPX mode
        "true" means that the DPX is enabled
        "false" means that the DPX is not enabled
*/
    bool       is_enabled;
    const bool _IS_ENABLED = false;    // DEFAULT


/*
    DPX_GetFrameBuffer()
        returns the current DPX frame buffer, bitmaps (spectrum and spectrogram "sogram") + spectrum traces
        std::vector collectors
            spectrum_bitmap_v        ; collects "spectrumBitmap" in struct "DPX_FrameBuffer"                 , 2 dimensions
            spectrum_traces_v        ; collects "spectrumTraces" in struct "DPX_FrameBuffer"                 , 3 dimensions
            sogram_bitmap_v          ; collects "sogramBitmap" in struct "DPX_FrameBuffer"                   , 2 dimensions
            sogram_bitmap_timestamp_v; collects "sogramBitmapTimestampArray" in struct "DPX_FrameBuffer"     , 2 dimensions
            sogram_bitmap_trigger_v  ; collects "sogramBitmapContainTriggerArray" in struct "DPX_FrameBuffer", 2 dimensions
        struct DPX_FrameBuffer
            fftPerFrame                     ; fft operations performed in the frame
            fftCount                        ; total fft operations performed since DPX acquisition started
            frameCount                      ; total number of DPX frames since DPX acquisition started
            timestamp                       ; acquisition timestamp of this frame
            acqDataStatus                   ; see AcqDataStatus enumeration for bit definitions
            minSigDuration                  ; minimum signal duration, in seconds, for 100% POI
            minSigDurOutOfRange             ; true if the minimum signal duration is out of range
            spectrumBitmapWidth             ; spectrum bitmap width, in pixels
            spectrumBitmapHeight            ; spectrum bitmap height, in pixels
            spectrumBitmapSize              ; total pixels in spectrum bitmap, width * height
            spectrumTraceLength             ; number of trace points in the spectrum trace
            numSpectrumTraces               ; number of spectrum traces
            spectrumEnabled                 ; true if the spectrum was enabled, see DPX_Configure()
            spectrogramEnabled              ; true if the spectrogram was enabled, see DPX_Configure()
            spectrumBitmap                  ; used to acquire data, but transfers to std::vector in scope
            spectrumTraces                  ; used to acquire data, but transfers to std::vector in scope
            sogramBitmapWidth               ; spectrogram bitmap width, in pixels
            sogramBitmapHeight              ; spectrogram bitmap height, in pixels
            sogramBitmapSize                ; spectrogram bitmap pixels, width * height
            sogramBitmapNumValidLines       ; valid horizontal lines "spectrums" in the spectrogram bitmap
            sogramBitmap                    ; used to acquire data, but transfers to std::vector in scope
            sogramBitmapTimestampArray      ; std::vector collects, each row has time, last is oldest
            sogramBitmapContainTriggerArray ; correspons to map, if triggered, pass to std::vector

*/
    char        acq_data_status_message[BUF_E];          // call-check acqDataStatus and record message
    const char* _ACQ_DATA_STATUS_MESSAGE = INIT_CHARP;   // DEFAULT

    std::vector<std::vector<float>> spectrum_bitmap_v;
    const float                     _SPECTRUM_BITMAP_V_element = INIT_FLOAT;         // DEFAULT, element value
    const std::size_t               _SPECTRUM_BITMAP_V_rows    = INIT_STL_LENGTH;    // DEFAULT, number of rows
    const std::size_t               _SPECTRUM_BITMAP_V_cols    = INIT_STL_LENGTH;    // DEFAULT, number of columns

    std::vector<std::vector<std::vector<float>>> spectrum_traces_v;
    const float                                  _SPECTRUM_TRACES_V_element = INIT_FLOAT;         // DEFAULT, element value
    const std::size_t                            _SPECTRUM_TRACES_V_traces  = TRACES_306B;        // DEFAULT, number of "traces"
    const std::size_t                            _SPECTRUM_TRACES_V_rows    = INIT_STL_LENGTH;    // DEFAULT, number of rows
    const std::size_t                            _SPECTRUM_TRACES_V_cols    = INIT_STL_LENGTH;    // DEFAULT, number of columns

    std::vector<std::vector<uint8_t>> sogram_bitmap_v;   
    const uint8_t                     _SOGRAM_BITMAP_V_element = INIT_UINT8;         // DEFAULT, element value
    const std::size_t                 _SOGRAM_BITMAP_V_rows    = INIT_STL_LENGTH;    // DEFAULT, number of rows
    const std::size_t                 _SOGRAM_BITMAP_V_cols    = INIT_STL_LENGTH;    // DEFAULT, number of columns

    std::vector<double> sogram_bitmap_timestamp_v;
    const double        _SOGRAM_BITMAP_TIMESTAMP_V_element = INIT_DOUBLE;        // DEFAULT, element value
    const std::size_t   _SOGRAM_BITMAP_TIMESTAMP_V_rows    = INIT_STL_LENGTH;    // DEFAULT, number of rows
    const std::size_t   _SOGRAM_BITMAP_TIMESTAMP_V_cols    = INIT_STL_LENGTH;    // DEFAULT, number of columns

    std::vector<std::vector<int16_t>> sogram_bitmap_trigger_v;
    const uint16_t                    _SOGRAM_BITMAP_TRIGGER_V_element = INIT_INT16;         // DEFAULT, element value
    const std::size_t                 _SOGRAM_BITMAP_TRIGGER_V_rows    = INIT_STL_LENGTH;    // DEFAULT, number of rows
    const std::size_t                 _SOGRAM_BITMAP_TRIGGER_V_cols    = INIT_STL_LENGTH;    // DEFAULT, number of columns

    RSA_API::DPX_FrameBuffer frame_buffer_type;
    const int32_t            _FRAME_BUFFER_TYPE_fftPerFrame                     = INIT_INT32;     // DEFAULT
    const int64_t            _FRAME_BUFFER_TYPE_fftCount                        = INIT_INT64;     // DEFAULT
    const int64_t            _FRAME_BUFFER_TYPE_frameCount                      = INIT_INT64;     // DEFAULT 
    const double             _FRAME_BUFFER_TYPE_timestamp                       = INIT_DOUBLE;    // DEFAULT 
	const uint32_t           _FRAME_BUFFER_TYPE_acqDataStatus                   = INIT_UINT32;    // DEFAULT 
	const double             _FRAME_BUFFER_TYPE_minSigDuration                  = INIT_DOUBLE;    // DEFAULT 	
    const bool               _FRAME_BUFFER_TYPE_minSigDurOutOfRange             = true;           // DEFAULT
    const int32_t            _FRAME_BUFFER_TYPE_spectrumBitmapWidth             = INIT_INT32;     // DEFAULT 
    const int32_t            _FRAME_BUFFER_TYPE_spectrumBitmapHeight            = INIT_INT32;     // DEFAULT 
    const int32_t            _FRAME_BUFFER_TYPE_spectrumBitmapSize              = INIT_INT32;     // DEFAULT 
    const int32_t            _FRAME_BUFFER_TYPE_spectrumTraceLength             = INIT_INT32;     // DEFAULT 
	const int32_t            _FRAME_BUFFER_TYPE_numSpectrumTraces               = INIT_INT32;     // DEFAULT 
	const bool               _FRAME_BUFFER_TYPE_spectrumEnabled                 = false;          // DEFAULT 
    const bool               _FRAME_BUFFER_TYPE_spectrogramEnabled              = false;          // DEFAULT 
    const float*             _FRAME_BUFFER_TYPE_spectrumBitmap                  = NULL;           // DEFAULT 
    const float**            _FRAME_BUFFER_TYPE_spectrumTraces                  = NULL;           // DEFAULT 
	const int32_t            _FRAME_BUFFER_TYPE_sogramBitmapWidth               = INIT_INT32;     // DEFAULT 
	const int32_t            _FRAME_BUFFER_TYPE_sogramBitmapHeight              = INIT_INT32;     // DEFAULT 
    const int32_t            _FRAME_BUFFER_TYPE_sogramBitmapSize                = INIT_INT32;     // DEFAULT 
    const int32_t            _FRAME_BUFFER_TYPE_sogramBitmapNumValidLines       = INIT_INT32;     // DEFAULT
	const uint8_t*           _FRAME_BUFFER_TYPE_sogramBitmap                    = NULL; 	      // DEFAULT
	const double*            _FRAME_BUFFER_TYPE_sogramBitmapTimestampArray      = NULL;           // DEFAULT 
	const int16_t*           _FRAME_BUFFER_TYPE_sogramBitmapContainTriggerArray = NULL;           // DEFAULT 

/*
    DPX_GetFrameInfo()
        frame_count ; total number of DPX frames, since DPX acquisition started
        fft_count   ; total number of fft operations performed since DPX acquisition started
*/
    int64_t       frame_count;
    const int64_t _FRAME_COUNT = INIT_INT64;    // DEFAULT 

    int64_t       fft_count;
    const int64_t _FFT_COUNT = INIT_INT64;      // DEFAULT 


/*
    DPX_GetRBWRange()
        queries a valid RBW, based on span
        frequency_span_hz ; is measured in Hz and must be > 0 && < 40e6
        rbw_min_hz        ; resulting RBW lower bound for control and configuration
        rbw_max_hz        ; resulting RBW upper bound for control and configuration
        limited by :
            FREQUENCY_SPAN_MIN_HZ 
            FREQUENCY_SPAN_MAX_HZ 
*/
    double       frequency_span_hz;
    const double _SPAN_HZ = INIT_DOUBLE;       // DEFAULT

    double       rbw_min_hz;
    const double _RBW_MIN_HZ = INIT_DOUBLE;    // DEFAULT

    double       rbw_max_hz;
    const double _RBW_MAX_HZ = INIT_DOUBLE;    // DEFAULT


/*
    DPX_GetSettings()
    after changing DPX settings, call "DPX_Configure()" for a proper DPX_GetSettings()
    DPX_SettingsStruct
        enableSpectrum   ; true if the DPX spectrum is enabled, else false
        enableSpectrogram; true if the DPX spectrogram is enabled, else false
        bitmapWidth      ; DPX spectrum bitmap width in pixels
        bitmapHeight     ; DPX spectrum bitmap height in pixels
        traceLength      ; number of trace points
        decayFactor      ; base on "presistenceTimeSec" in "DPX_SetParameters()", hit count of each pixel is multiplied by this
        actualRBW        ; actual resolution bandwidth in Hz
*/
    RSA_API::DPX_SettingsStruct settings_type;
    const bool                  _SETTINGS_TYPE_enableSpectrum    = false;          // DEFAULT
    const bool                  _SETTINGS_TYPE_enableSpectrogram = false;          // DEFAULT
    const int32_t               _SETTINGS_TYPE_bitmapWidth       = INIT_INT32;     // DEFAULT
    const int32_t               _SETTINGS_TYPE_bitmapHeight      = INIT_INT32;     // DEFAULT
    const int32_t               _SETTINGS_TYPE_traceLength       = INIT_INT32;     // DEFAULT
    const float                 _SETTINGS_TYPE_decayFactor       = INIT_FLOAT;     // DEFAULT
    const double                _SETTINGS_TYPE_actualRBW         = INIT_DOUBLE;    // DEFAULT


/*
    DPX_GetSogramHiResLine()
        query high resolution line specified by "line_index"
        shifts to first valid index automatically
        spectrogram high resolution lines are updated when DPX is acquring, so call this DPX is stopped
        line_data_v              ; a pointer loads this, holds data stored in spectrogram high resolution line
        line_data_elements       ; number of elements in "line_data_v"
        line_index               ; line index to get the high resolution line from the spectrogram
        line_data_scaling_factor ; for dBm, multiply this by "data_v" to get a good result
        trace_points             ; amount of trace points to return
        first_valid_point        ; where the first valid trace point should be

*/
    std::vector<int16_t> line_data_v;
    const uint16_t       _LINE_DATA_V_element = INIT_INT16;      // DEFAULT
    const std::size_t    _LINE_DATA_V_size = INIT_STL_LENGTH;    // DEFAULT

    int32_t       line_data_elements;
    const int32_t _LINE_DATA_LENGTH = INIT_INT32;                // DEFAULT

    int32_t       line_index;
    const int32_t _LINE_INDEX = INIT_INT32;                      // DEFAULT

    double       line_data_scaling_factor;
    const double _LINE_DATA_SCALING_FACTOR = INIT_DOUBLE;        // DEFAULT

    int32_t trace_points;
    const int32_t _TRACE_POINTS = INIT_INT32;                    // DEFAULT

    int32_t first_valid_point;
    const int32_t _FIRST_VALID_POINT = INIT_INT32;               // DEFAULT


/*
    DPX_GetSogramHiResLineCountLatest()
        find out how many high resolution lines there are in the device
        each high resolution line can have multiple ffts
        DPX acquisition could have been stopped at any time
        latest high resolution lines may not contain all the fft's as a high resolution line
        line_count ; how many high resolution lines are ready for acquisition
*/
    int32_t       line_count;
    const int32_t _LINE_COUNT = INIT_INT32;    // DEFAULT


/*
    DPX_GetSogramHiResLineTimestamp()
        the spectrogram high resolutions always update while DPX is running, so call after stopping DPX
        line_timestamp ; for this given line index, the time stamp is quired
        line_index     ; the index of the high resolution spectrogram line
*/
double       line_timestamp;
const double _LINE_TIMESTAMP = INIT_DOUBLE;    // DEFAULT

int32_t       line_index;
const int32_t _LINE_INDEX = INIT_INT32;        // DEFAULT


/*
    DPX_GetSogramHiResLineTriggered()
    line_index     ; the index of the high resolution spectrogram line, already defined
    was_triggered  ; true indicates that the line at specified index was triggered
*/
    bool       was_triggered;
    const bool _WAS_TRIGGERED = false;    // DEFAULT

/*
    DPX_GetSogramSettings()
    basic query
    DPX_SogramSettingsStruct
        bitmapWidth          ; DPX spectrogram bitmap width, in pixels
        bitmapHeight         ; DPX spectrogram bitmap height, in pixels
        sogramTraceLineTime  ; time per each DPX spectrogram high resolution line, in seconds
        sogramBitmapLineTime ; time per each DPX spectrogram bitmap line, in seconds

*/
    RSA_API::DPX_SogramSettingsStruct sogram_settings_type;
    const int32_t                     _SOGRAM_SETTINGS_TYPE_bitmapWidth = INIT_INT32;              // DEFAULT
    const int32_t                     _SOGRAM_SETTINGS_TYPE_bitmapHeight = INIT_INT32;             // DEFAULT
    const double                      _SOGRAM_SETTINGS_TYPE_sogramTraceLineTime = INIT_DOUBLE;     // DEFAULT
    const double                      _SOGRAM_SETTINGS_TYPE_sogramBitmapLineTime = INIT_DOUBLE;    // DEFAULT


/*
    DPX_IsFrameBufferAvailable()
        frame_available ; true means that the frame is available for acquisition, else false
*/
    bool       frame_available;
    const bool _FRAME_AVAILABLE = false;

/*
    DPX_Reset()
        clears the spectrum bitmap
        resets the spectrum traces
        resets the spectrogram bitmap
        resets the spectrogram traces
        sets the  fft cound to 0
        and sets frame count to 0
*/


/*
    DPX_SetParameters()
        sets a lot of important parameters
        frequency_span_hz ; defined in "DPX_GetRBWRange()"
        rbw_hz       ; must be > 0 Hz
        bitmap_width ; must be > 0 && < 801, bitmap width in pixels
        trace_points_per_pixel   ; used to derive "trace_points_total", only 1, 3, and 5 are acceptable 
        trace_points_total       ; trace_points_per_pixel * bitmap_width 
        vertical_unit_select     ; uses RSA enum to select vertical units, stay with dBm...
        y_top                    ; max value on the "y" axis, must be > y_bottom
        y_bottom                 ; min value on the "y" axis, must be < y_top
        infinite_persistence     ; causes every data point to remain on the screen when enabled
        persistence_time_seconds ; amount of time that previous signals remain on the screen
        show_only_trigger_frame  ; if true, DPX frame is only available when trigger occurs, if false frame is continous
        limited by :
            RBW_MIN_HZ
            BITMAP_WIDTH_MIN 
            BITMAP_WIDTH_MAX
            TRACE_POINT_PER_PIXEL_1
            TRACE_POINT_PER_PIXEL_3
            TRACE_POINT_PER_PIXEL_5

*/
    double       rbw_hz;
    const double _RBW_HZ = INIT_DOUBLE;                                                   // DEFAULT

    int32_t       bitmap_width;
    const int32_t _BITMAP_WIDTH = INIT_INT32;                                             // DEFAULT

    int32_t       trace_points_per_pixel;
    const int32_t _TRACE_POINTS_PER_PIXEL = INIT_INT32;                                   // DEFAULT

    int32_t trace_points_total;
    const int32_t _TRACE_POINTS_TOTAL = INIT_INT32;                                       // DEFAULT

    RSA_API::VerticalUnitType vertical_unit_select;
    const RSA_API::VerticalUnitType _VERTICAL_UNIT_SELECT = RSA_API::VerticalUnit_dBm;    // DEFAULT

    double y_top;
    const double _Y_TOP = INIT_DOUBLE;                                                    // DEFAULT

    double y_bottom;
    const double _Y_BOTTOM = INIT_DOUBLE;                                                 // DEFAULT

    bool       infinite_persistence;
    const bool _INFINITE_PERSISTENCE = false;                                             // DEFAULT

    double       persistence_time_seconds;
    const double _PERSISTENCE_TIME_SECONDS = INIT_DOUBLE;                                 // DEFAULT

    bool       show_only_trigger_frame;
    const bool _SHOW_ONLY_TRIGGER_FRAME = false;                                          // DEFAULT


/*
    DPX_SetSogramParameters()
        sets amount of time each spectrogram line represents
        and signal level range of the spectrogram
        time_per_bitmap_line_seconds ; amounth of time, per bitmap line, in seconds (each line is made of 1 or more high-res lines)
        time_resolution_seconds      ; amount of time each spectrogram high-res line represents, in seconds, must be >= 1 ms
        power_min                    ; min signal level in vertical units, see "DPX_SetParameters()" "y_bottom"
        power_max                    ; max signal level in vertical units, see "DPX_SetParameters()" "y_top"
        limited by :
            TIME_RESOLUTION_SECONDS_MIN 
*/
    double       time_per_bitmap_line_seconds;
    const double _TIME_PER_BITMAP_LINE_SECONDS = INIT_DOUBLE;    // DEFAULT

    double       time_resolution_seconds;
    const double _TIME_RESOLUTION_SECONDS = INIT_DOUBLE;         // DEFAULT

    double       power_min;
    const double _POWER_MIN = INIT_DOUBLE;                       // DEFAULT

    double       power_max;
    const double _POWER_MAX = INIT_DOUBLE;                       // DEFAULT


/*
    DPX_SetSogramTraceType()
        be ware of the enums that will cause errors
        spectrogram_trace_type_select; max, min, average are fine, do not use "TraceTypeMaxHold" or "TraceTypeMinHold"
*/
    RSA_API::TraceType       spectrogram_trace_type_select;
    const RSA_API::TraceType _SPECTROGRAM_TRACE_TYPE_SELECT = RSA_API::TraceType::TraceTypeMax;    // DEFAULT


/*
    DPX_SetSpectrumTraceType()
        trace_index                ; use the enum to pick the trace (0, 1, or 2)
        spectrum_trace_type_select ; can use all values in the enum

*/
    int32_t       trace_index[TRACES_306B];
    const int32_t _TRACE_INDEX [TRACES_306B] =     // DEFAULT
        {
            static_cast<int32_t>(RSA_API::DPX_TRACEIDX_1),
            static_cast<int32_t>(RSA_API::DPX_TRACEIDX_2),
            static_cast<int32_t>(RSA_API::DPX_TRACEIDX_3)
        };                 

    RSA_API::TraceType       spectrum_trace_type_select[TRACES_306B];
    const RSA_API::TraceType _SPECTRUM_TRACE_TYPE_SELECT[TRACES_306B] = // DEFAULT
        {
            RSA_API::TraceType::TraceTypeMax,
            RSA_API::TraceType::TraceTypeMax,
            RSA_API::TraceType::TraceTypeMax
        };


/*
    DPX_WaitForReady()
        if data is not ready, and timeout is exceeded, ready parameter will be false
        else, ready parameter is true and data is ready
        timeout_ms ; milli-seconds to hang the loop and wait for data
        is_ready   ; true if data is ready, else false

*/  
    int       timeout_ms;
    const int _TIMEOUT_MS = 2;       // DEFAULT

    bool       is_ready;
    const bool _IS_READY = false;    // DEFAULT


// limiting constants :
    const uint8_t SOGRAM_DIVISOR          = 254U;          // sogram bitmap: (max - min) / 254, 0: signal level <= minPow, 254: signal level >= maxPow
    const int16_t SOGRAM_TRIGGER_OCCURED  = 1;             // sogram bitmap trigger array indicates "1" if a trigger occured
    const int16_t SOGRAM_NO_TRIGGER       = 0;             // sogram bitmap trigger array indicates "0" if there was no trigger
    const double  FREQUENCY_SPAN_MIN_HZ   = 1e6;           // the frequency span minimum, in Hz, must be > 0 Hz
    const double  FREQUENCY_SPAN_MAX_HZ   = 39.0e6;        // the frequency span maximum, in Hz, must be < 40.0 MHz
    const double  RBW_MIN_HZ              = 1e3;           // the RBW must be > 0 Hz
    const int32_t BITMAP_WIDTH_MIN        = 21;            // bitmap width must be > 0 pixels
    const int32_t BITMAP_WIDTH_MAX        = 801;           // bitmap width must be <= 801
    const int32_t TRACE_POINT_PER_PIXEL_1 = 1;             // a valid "trace-points-per-pixel" is 1
    const int32_t TRACE_POINT_PER_PIXEL_3 = 3;             // a valid "trace-points-per-pixel" is 3
    const int32_t TRACE_POINT_PER_PIXEL_5 = 5;             // a valid "trace-points-per-pixel" is 5
    const double  TIME_RESOLUTION_SECONDS_MIN = 1.0e-2;    // time resolution must be >= 1 ms


};
typedef struct rsa306b_dpx_struct rsa306b_dpx_struct;


#endif


////////~~~~~~~~END>  rsa306b_dpx_struct.h
