/*
    implementation of the essential components in the rsa306b class
    functions and members of "general purpose"

        public:
            # rsa306b()
            # ~rsa306b()
            # get_api_return_status()
            # get_api_return_status_string()
            # get_internal_return_status()

        private:
            # _api_error_check()
            # _internal_error_check()
            # _init_member_variables()
*/

#include "../includez/rsa306b_class.h"


/*
    public
    the constructor for the class
    there is no need for multiple constructors (for now)
    ensures all variables are initialized to known values
*/
rsa306b::rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  constructor\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_init_member_variables();
    this->_api_error_check();
    this->_internal_error_check();
}


////~~~~


/*
    public
    the desctructor for the class
    stops a running device, if running
    disconnects a connected device, if connected
    deallocates dynamic member variables if necessary
*/
rsa306b::~rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  destructor\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == true)
    {
        this->_api_return_status = RSA_API::DEVICE_Disconnect();
        this->_api_error_check();
        sleep(1);
    }
}


////~~~~


/*
    public
    returns integer matching the error in the API enum
    user is responsible for matching the value
*/
RSA_API::ReturnStatus rsa306b::get_api_return_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    return this->_api_return_status;
}


////~~~~


/*
    public
    updates string with API return status and error message
    caller must allocate input string, make at least 256 chars
*/
void rsa306b::get_api_return_status_string(char* carrier)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (carrier == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\tallocate the string before calling\n");
        #endif
        return;
    }

    const char* temp;
    temp = RSA_API::DEVICE_GetErrorString(this->_api_return_status);
    snprintf(carrier, BUF_D-1, 
        "error code:  %d  ,  error message:  %s", this->_api_return_status, temp);
}


////~~~~


/*
    public
    returns current state of internal return status indicator
*/
int rsa306b::get_internal_return_status()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
   return this->_internal_return_status;
}


////~~~~


/*
    private
    matches current state of the ReturnStatus variable to the enum
    indicates if an error has occured, otherwise does nothing
    good practice to call after each API function is used, unless speed is needed
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b::_api_error_check()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_ERR
            this->get_api_return_status_string(this->_helper_string);
            printf("\t###   !!!   API ERROR   !!!   ###   %s\n", 
                this->_helper_string);
        #endif
        #ifdef DEBUG_MIN
            printf("\t###   !!!   API ERROR   !!!   ###\n");
        #endif
    }
}


////~~~~


/*
    private
    called to indicate error conditions after internal function calls
    requires DEBUG_CLI or DEBUG_MIN to be activated
*/
void rsa306b::_internal_error_check()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_internal_return_status != CALL_SUCCESS)
    {
        #if defined (DEBUG_ERR) || (DEBUG_CLI)
            printf("\t###   !!!   INTERNAL ERROR   !!!   ###\n");
        #endif
    }
}


////~~~~


/*
    private
    call any time member variables should be reset to known values
    deallocates dynamically member variables if needed, and places on NULL
    initialization values are in "rsa306b_class.h"
*/
void rsa306b::_init_member_variables()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    // general purpose
    memset(this->_helper_string, '\0', BUF_E);
    memset(this->_holder_string, '\0', BUF_F);
    this->_api_return_status = RSA_API::noError;
    this->_internal_return_status = CALL_SUCCESS;

    // ALIGN

    // CONFIG

    // DEVICE
}
       

////////~~~~~~~~END>  rsa306b_class.cpp
