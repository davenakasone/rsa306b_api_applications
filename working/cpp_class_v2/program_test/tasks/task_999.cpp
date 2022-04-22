/*
    inital structure of version #2 is emplaced
    basic features are tested as the core program is developed
*/

#include "../testz.h"


void task_999()
{
    printf("\n%s()  ,  getting the core program structured\n", __func__);
    {
        rsa306b_class rsa;

        rsa.print_constants();
        rsa.print_gp();
        printf("\n>>>>>>>>>>    <<<<<<<<<<<<\n");
        rsa.print_everything();
    }

    printf("\n%s()  ,  test complete\n", __func__);
}

/////////~~~~~~~~END>  task_999.cpp
