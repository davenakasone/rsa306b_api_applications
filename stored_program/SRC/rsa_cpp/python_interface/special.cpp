/*
    source code for the python interface
    special functions and applications

        < 1 >  spectrum_scanner()
        < 2 >  scan_dump()
        < 3 >  file_select()
        < 4 >  spectrum_scanner_b1()
        < 5 >  spectrum_scanner_b2()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
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

// < 2 >
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
    );
    return juicy;
}

// < 3 >
char* file_select
(
    char* directory
)
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    int selection = 1;

    (void)X_util.find_files_in_directory(directory, X_util.filez_in, true);
    if (X_util.filez_in.size() < static_cast<std::size_t>(1)) 
    { 
        return NULL;
    }

    for (std::size_t xx = 0; xx < X_util.filez_in.size(); xx++)
    {
        (void)strcpy(X_util.helper, X_util.filez_in[xx].c_str());
        (void)strcpy(X_util.holder, X_util.filez_in[xx].c_str());
        if (X_util.extension_matched(X_util.helper, R3F_RAW_EXT) == true)
        {
            (void)strcpy(X_r3f.cutil.helper, X_util.filez_in[xx].c_str());
            (void)strcpy(X_r3f.cutil.holder, X_util.filez_in[xx].c_str());
            X_util.insert_and_change_extension(X_r3f.cutil.helper, IFSTREAM_TAG_EQL, DATA_DEFAULT_EXT);
            X_util.insert_and_change_extension(X_r3f.cutil.holder, IFSTREAM_TAG_ADC, DATA_DEFAULT_EXT);
            X_r3f.load_file(X_util.helper, NULL, X_r3f.cutil.helper, X_r3f.cutil.holder, false, true, true);
            X_util.switch_directory(X_util.holder, DATA_DIRECTORY_RAW);
            X_util.exe_rename(X_util.helper, X_util.holder);
        }
        if (X_util.extension_matched(X_util.helper, SIQ_RAW_EXT) == true)
        {
            (void)strcpy(X_siq.cutil.helper, X_util.filez_in[xx].c_str());
            X_util.insert_and_change_extension(X_siq.cutil.helper, SIQ_TAG_IQ, DATA_DEFAULT_EXT);
            X_siq.load_file(X_util.helper, NULL, X_siq.cutil.helper, false, true);
            X_util.switch_directory(X_util.holder, DATA_DIRECTORY_RAW);
            X_util.exe_rename(X_util.helper, X_util.holder);
        }
    }

    (void)X_util.find_files_in_directory(directory, X_util.filez_in, false);
    (void)X_util.find_files_in_directory(directory, X_util.filez_out, true);
    printf("\nselect a file:\n");
    for (std::size_t xx = 0; xx < X_util.filez_in.size(); xx++)
    {
        printf("[%3lu] %s\n", xx+1, X_util.filez_in[xx].c_str());
    }
    printf("\n\tyour selection:  ");
    std::cin >> selection;
    
    if
    (
        (selection < 1) ||
        (selection > static_cast<int>(X_util.filez_in.size()))
    )
    {
        return NULL;
    }
    (void)strcpy(juicy, X_util.filez_out[selection-1].c_str());
    return juicy;
}

// < 4 >
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

// < 5 >
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


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  special.cpp
