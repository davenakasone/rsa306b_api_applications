/*
    this class uses the API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires the 2 shared objects to be linked and the RSA_API.h header
    using 1, and only one instance of this class, can remove the abstraction in the API
    do not try to use more than one instance
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class

#include <stdio.h>
#include "../api_resourcez/RSA_API.h"

class rsa306b
{
    public:
        rsa306b();
        ~rsa306b();
        int test_public;

    protected:
        int test_protected;

    private:
        int test_private;
};


#endif


////////~~~~~~~~END>  rsa306b.h
