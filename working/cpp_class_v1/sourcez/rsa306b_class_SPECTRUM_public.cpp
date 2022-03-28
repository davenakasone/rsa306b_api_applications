/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    public functions for user action
        public:
            < 1 >
            < > spectrum_print_all()
            
        private:
            # none
        
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
//
void rsa306b::
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    } 
}
*/

////~~~~


/*
    public <  >
    prints all "SPECTRUM" member data
*/
void rsa306b::spectrum_print_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    } 
    this->_spectrum_set_limits_type();

    printf("\nSPECTRUM limits >>>\n");
    printf("\tmaximum span                  :  %lf\n", this->_spectrum_limits_type.maxSpan);
    printf("\tminimum span                  :  %lf\n", this->_spectrum_limits_type.minSpan);
    printf("\tmaximum resolution bandwidth  :  %lf\n", this->_spectrum_limits_type.maxRBW);
    printf("\tminimum resolution bandwidth  :  %lf\n", this->_spectrum_limits_type.minRBW);
    printf("\tmaximum video bandwidth       :  %lf\n", this->_spectrum_limits_type.maxVBW);
    printf("\tminimum video bandwidth       :  %lf\n", this->_spectrum_limits_type.minVBW);
    printf("\tmaximum trace length          :  %d\n", this->_spectrum_limits_type.maxTraceLength);
    printf("\tminimum trace length          :  %d\n", this->_spectrum_limits_type.minTraceLength);
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_public.cpp
