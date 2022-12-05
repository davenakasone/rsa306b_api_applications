/*
    source code for the python interface
    special functions and applications

        < 1 >  scan_dump()
        < 2 >  spectrum_scanner()
        < 3 >  spectrum_scanner_b1()
        < 4 >  spectrum_scanner_b2()
        < 5 >  trigger_dump()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
char* scan_dump                    
(
    const int    smode,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const double threshold
)
{
    double ffstart = fstart;
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    if (ffstart < 10.0e6)
    {
        ffstart = 10.0e6;
    }
    
    if 
    (
        X_rsa.scan_dump
        (
            smode,
            ffstart,
            fstop,
            reflevel,
            RSA_API::SpectrumTrace1, // python users only get trace[0]
            10.0e3,
            20.0e6,
            999,
            threshold,
            10,
            juicy
        ) != CODEZ::_0_no_errors
    )
    {
        return NULL;
    }
    return juicy;
    
}

// < 2 >
char* spectrum_scanner
(
    double fstart, 
    double fstop, 
    double threshold, 
    int loitering,
    double reflevel,
    double rbw,
    double span,
    int tlen
)
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    (void)X_rsa.spectrum_scanner
        (
            static_cast<int>(RSA_API::SpectrumTrace1), // python users only get trace[0]
            fstart, 
            fstop, 
            threshold, 
            loitering, 
            juicy,
            reflevel, 
            rbw, 
            span, 
            tlen
        );
    return juicy;
}

// < 3 >
char* spectrum_scanner_b1
(
    double fstart, 
    double fstop, 
    double threshold, 
    int loitering,
    double reflevel,
    double rbw,
    double span,
    int tlen
)
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    (void)X_rsa.spectrum_scanner
        (
            RSA_API::SpectrumTrace1, // python users only get trace[0]
            fstart, 
            fstop, 
            threshold, 
            loitering, 
            juicy,
            reflevel, 
            rbw, 
            span, 
            tlen
        );
    return juicy;
}

// < 4 >
char* spectrum_scanner_b2
(
    double fstart, 
    double fstop, 
    double threshold, 
    int loitering,
    double reflevel,
    double rbw,
    double span,
    int tlen
)
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    (void)X_rsa.spectrum_scanner
        (
            RSA_API::SpectrumTrace1, // python users only get trace[0]
            fstart, 
            fstop, 
            threshold, 
            loitering, 
            juicy,
            reflevel, 
            rbw, 
            span, 
            tlen
        );
    return juicy;
}

// < 5 >
char* trigger_dump
(
    const int    loitering,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const double triglevel,
    const double rbw,
    const double span,
    const int    tlen,
    int          record_ms
)
{
    double ffstart = fstart;
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    if (ffstart < 10.0e6)
    {
        ffstart = 10.0e6;
    }

    if 
    (
        X_rsa.triggered_dump
        (
            loitering,                                  // how many times to loiter on each bin
            ffstart,                                    // stopping frequency (Hz)
            fstop,                                      // starting frequency (Hz)
            reflevel,                                   // configuration reference level (dBm)
            triglevel,                                  // trigger IF power level (dBm)
            RSA_API::SpectrumTraces::SpectrumTrace1,    // which trace
            rbw,                                        // resolution bandwidth (Hz)
            span,                                       // span (Hz)
            tlen,                                       // points in a trace
            record_ms,                                  // milli-seconds to record SIQ and R3F
            juicy                                       // directory where files will go                  
        ) != CODEZ::_0_no_errors
    )
    {
        return NULL;
    }
    return juicy;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  special.cpp
