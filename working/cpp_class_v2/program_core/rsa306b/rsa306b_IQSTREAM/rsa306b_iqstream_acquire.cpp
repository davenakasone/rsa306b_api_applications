/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_acquire_data_to_file()
        < 2 >  _iqstream_acquire_data_direct()
    
    user should have configured with "iqstream_set_vars()" before acquiring data
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    connection check already occured
*/
void rsa306b_class::_iqstream_acquire_data_to_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    bool is_complete = false;
    bool is_writing = false;

    this->device_run();
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Start();
    this->_gp_confirm_api_status();

    if (this->_vars.trig.mode_select == RSA_API::freeRun)
    {
        while (is_complete == false)
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_GetDiskFileWriteStatus
                (
                    &is_complete,
                    &is_writing
                );
            this->_gp_confirm_api_status();
        }
    }
    else    // triggered mode
    {
        while (is_complete == true && 
               is_writing == true   )
        {
            // timeout required, see p73 ....sleep + counter?
        }
        printf("\n\tTODO\n");
    }

    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Stop();
    this->_gp_confirm_api_status();
    RSA_API::IQSTREAM_GetDiskFileInfo(&this->_vars.iqstream.fileinfo_type);
    this->_iqstream_get_disk_fileinfo();    // bit check is handeled
    this->device_stop();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_acquire_data_direct()
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
        return;
    }
}


////////~~~~~~~~END>  rsa306b_iqstream_acquire.cpp
