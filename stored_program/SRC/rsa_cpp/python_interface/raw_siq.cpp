/*
    source code for the python interface
    using the r3f_manager class

        < 1 >  get_siq_csv
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
char* get_siq_csv()
{
    int select = -1;
    char selection[BUF_C];
    memset(selection, '\0', sizeof(selection));
    std::size_t vsize = 0;

    (void)X_util.find_files_with_extension(DATA_DIRECTORY_RAW, SIQ_RAW_EXT, X_util.filez_in, true);
    (void)X_util.find_files_with_extension(DATA_DIRECTORY_RAW, SIQ_RAW_EXT, X_util.filez_out, false);
    vsize = X_util.filez_in.size();
    if (vsize < static_cast<std::size_t>(1))
    {
        return NULL;
    }
    
    printf("\nSIQ, CSV plot, IQ, make from:\n");
    for (std::size_t xx = 0; xx < vsize; xx++)
    {
        printf("[%3lu]  %s\n", xx+1, X_util.filez_out[xx].c_str());
    }
    printf("your selection (-1 to exit)  :  ");
    std::cin >> selection;
    select = atoi(selection);
    if 
    (
        (select < 1) || 
        (select > static_cast<int>(vsize))
    )
    {
        return NULL;
    }

    (void)snprintf(X_util.helper, sizeof(X_util.helper), "%s%s%s", 
        DATA_DIRECTORY_PROCESSED, 
        IFSTREAM_TAG_ADC, 
        X_util.filez_out[static_cast<std::size_t>(select-1)].c_str());
    (void)X_util.h_change_extension(X_util.helper, DATA_DEFAULT_EXT);
    if 
    (
        X_siq.load_file
        (
            X_util.filez_in[static_cast<std::size_t>(select)].c_str(), 
            NULL, 
            X_util.helper, 
            false, 
            true
        ) != CODEZ::_0_no_errors
    )
    {
        return NULL;
    }
    return X_util.helper;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  raw_siq.cpp
