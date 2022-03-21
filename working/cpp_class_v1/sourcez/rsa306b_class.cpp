/*
    implementation of the rsa306b_class
        # rsa306b()
        # ~rsa306b()
*/

#include "../includez/rsa306b_class.h"

rsa306b::rsa306b()
{
    rsa306b::test_public = 1;
    rsa306b::test_protected = 2;
    rsa306b::test_private = 3;
    printf("\n\tpublic:  %d  ,  protected:  %d  ,  private:  %d\n",
        test_public, test_protected, test_private);
}


////~~~~


rsa306b::~rsa306b()
{
    rsa306b::test_public = 4;
    rsa306b::test_protected = 5;
    rsa306b::test_private = 6;
    printf("\n\tdestroyed...\n");
    printf("\n\tpublic:  %d  ,  protected:  %d  ,  private:  %d\n",
        test_public, test_protected, test_private);
}


////////~~~~~~~~END>  rsa306b_class.cpp
