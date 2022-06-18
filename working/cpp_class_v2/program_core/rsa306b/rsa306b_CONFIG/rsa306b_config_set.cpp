/*
    API group "CONFIG", setters

    public :
        #  none
    
    private :
        < 1 >  _config_set_vars()
        < 2 >  _config_set_reference_level_dbm()
        < 3 >  _config_set_center_frequency_hz()
        < 4 >  _config_set_external_reference_frequency_source_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
int rsa306b_class::_config_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    // vars.config.reference_level_dbm
    if (this->vars.config.reference_level_dbm == this->_vars.config.reference_level_dbm)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno change in the reference level\n");
        #endif
    }
    else
    {
        this->_vars.gp.call_status = this->_config_set_reference_level_dbm();
        if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.config.center_frequency_hz
    if (this->vars.config.center_frequency_hz == this->_vars.config.center_frequency_hz)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno change in the center frequency\n");
        #endif
    }
    else
    {
        this->_vars.gp.call_status = this->_config_set_center_frequency_hz();
        if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.config.frequency_reference_source_select
    if (this->vars.config.frequency_reference_source_select == this->_vars.config.frequency_reference_source_select)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno change in the frequency source\n");
        #endif
    }
    else
    {
        this->_vars.gp.call_status = this->_config_set_external_reference_frequency_source_select();
        if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
        if (this->_vars.config.frequency_reference_source_select == RSA_API::FRS_EXTREF)
        {
            this->_config_get_external_reference_frequency_hz();
            if (this->_vars.gp.api_status != RSA_API::noError)
            {
                #ifdef DEBUG_MIN
                    printf("\n\tfailure reading external reference frequency\n");
                #endif
                return this->constants.CALL_FAILURE;
            }
        }
    }

    return this->constants.CALL_SUCCESS;
}


////~~~~


/*
    < 2 > private
*/
int rsa306b_class::_config_set_reference_level_dbm()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.config.reference_level_dbm < this->constants.REFERENCE_LEVEL_MIN_dbm ||
        this->vars.config.reference_level_dbm > this->constants.REFERENCE_LEVEL_MAX_dbm  )
    {
        #ifdef DEBUG_MIN
            printf("\n\treference level { %lf }  ,  out of range [ %lf , %lf ]\n",
                this->vars.config.reference_level_dbm,
                this->constants.REFERENCE_LEVEL_MIN_dbm,
                this->constants.REFERENCE_LEVEL_MAX_dbm);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status =
        RSA_API::CONFIG_SetReferenceLevel(this->vars.config.reference_level_dbm);
    this->_gp_confirm_api_status();
    this->_config_get_reference_level_dbm();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 3 > private
*/
int rsa306b_class::_config_set_center_frequency_hz()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.config.center_frequency_hz < this->_vars.config.min_center_frequency_hz ||
        this->vars.config.center_frequency_hz > this->_vars.config.max_center_frequency_hz  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tcenter frequency { %lf }  ,  out of range [ %lf , %lf ]\n",
                this->vars.config.center_frequency_hz,
                this->_vars.config.min_center_frequency_hz,
                this->_vars.config.max_center_frequency_hz);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_SetCenterFreq(
            this->vars.config.center_frequency_hz);
    this->_gp_confirm_api_status();
    this->_config_get_center_frequency_hz();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 4 > private
*/
int rsa306b_class::_config_set_external_reference_frequency_source_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.config.frequency_reference_source_select != RSA_API::FRS_EXTREF &&
        this->vars.config.frequency_reference_source_select != RSA_API::FRS_INTERNAL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvlaid frequency reference source\n");
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status =
        RSA_API::CONFIG_SetFrequencyReferenceSource(
            this->vars.config.frequency_reference_source_select);
    this->_gp_confirm_api_status();
    this->_config_get_frequency_reference_source_select();
    return this->_gp_confirm_return();
}


////////~~~~~~~~END>  rsa306b_config_set.cpp
