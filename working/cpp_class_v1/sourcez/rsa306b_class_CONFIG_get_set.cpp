/*
    implementation of the rsa306b_class
    using "CONFIG" function group of the API
    getters and setters for member variables

        public:
            < 1 >  config_get_center_frequency_hz()
            < 2 >  config_get_center_frequency_max_hz()
            < 3 >  config_get_center_frequency_min_hz()
            < 4 >  config_get_reference_level_dbm()
            < 5 >  config_get_frequency_reference_source()
            < 6 >  config_get_external_frequency_reference_hz()
    
        private:
            < 1 >  _config_set_center_frequency_hz()
            < 2 >  _config_set_reference_level_dbm()
            < 3 >  _config_set_frequency_reference_source();
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    updates center frequency, then returns current value
*/
double rsa306b::config_get_center_frequency_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return INIT_DOUBLE;
    }
    this->_config_set_center_frequency_hz();
    return this->_config_center_frequency_hz;
}


////~~~~


/*
    public < 2 >
    returns value identified at connection
*/
double rsa306b::config_get_center_frequency_max_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return INIT_DOUBLE;
    }
    return this->_config_center_frequency_max_hz;
}


////~~~~


/*
    public < 3 >
    returns value identified at connection
*/
double rsa306b::config_get_center_frequency_min_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return INIT_DOUBLE;
    }
    return this->_config_center_frequency_min_hz;
}


////~~~~


/*
    public < 4 >
    
*/
double rsa306b::config_get_reference_level_dbm()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return INIT_DOUBLE;
    }
    this->_config_set_reference_level_dbm();
    return this->_config_reference_level_dbm;
}


////~~~~


/*
    public < 5 >
    confirms source, then returns value
*/
RSA_API::FREQREF_SOURCE rsa306b::config_get_frequency_reference_source()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return RSA_API::FRS_INTERNAL;
    }
    this->_config_set_frequency_reference_source();
    return this->_config_frequency_reference_source_select;
}


////~~~~


/*
    public < 6 >
    confirms if external source is connected
    returns frequency in Hz if connected
*/
double rsa306b::config_get_external_frequency_reference_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
        return INIT_DOUBLE;
    }

    this->_config_set_frequency_reference_source();
    if (this->_config_frequency_reference_source_select == RSA_API::FRS_EXTREF)
    {
        this->_api_return_status = RSA_API::CONFIG_GetExternalRefFrequency(
            &this->_config_external_reference_frequency_hz);
        this->_api_error_check();
        return this->_config_external_reference_frequency_hz;
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("\n\tnot using an external reference soucre, returning default\n");
        #endif
        return INIT_DOUBLE;
    }
}


////~~~~


/*
    private < 1 >
    sets the center frequency variable with the API
*/
void rsa306b::_config_set_center_frequency_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, configuration not possible\n");
        #endif
    }
    this->_api_return_status = RSA_API::CONFIG_GetCenterFreq(
        &this->_config_center_frequency_hz);
    this->_api_error_check();
}


////~~~~


/*
    private < 2 >
    sets the reference level variable with the API
*/
void rsa306b::_config_set_reference_level_dbm()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, configuration not possible\n");
        #endif
    }
    this->_api_return_status = RSA_API::CONFIG_GetReferenceLevel(
        &this->_config_reference_level_dbm);
    this->_api_error_check();
}


////~~~~


/*
    private < 3 >
    sets the source variable with the API
*/
void rsa306b::_config_set_frequency_reference_source()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, configuration not possible\n");
        #endif
    }
    this->_api_return_status = RSA_API::CONFIG_GetFrequencyReferenceSource(
        &this->_config_frequency_reference_source_select);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_CONFIG_get_set.cpp
