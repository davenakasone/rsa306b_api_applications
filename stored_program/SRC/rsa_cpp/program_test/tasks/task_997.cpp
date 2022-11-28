/*
    best common utility option for deleting directories
*/

#include "../testz.h"

#ifdef UNIT_TESTING

int t997_repz = 5;
static void t997_populate();
static void t997_data_reset();

void task_997()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  delete directories\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    t997_populate();
    printf("\ncheck the directory, any key to delete (no filling) :  ");
    std::cin >> X_util.helper;
    (void)X_util.rm_rf(DATA_DIRECTORY, NULL, NULL, false);
    printf("\ncheck the directory, should be no files :  ");
    std::cin >> X_util.helper;

    X_util.exe_mkdir(DATA_DIRECTORY);
    X_util.exe_mkdir(DATA_DIRECTORY_PROCESSED);
    X_util.exe_mkdir(DATA_DIRECTORY_RAW);
    X_util.exe_mkdir(DATA_DIRECTORY_SEQUENCED);
    t997_populate();
    printf("\ncheck the directory, any key to delete (with filling) :  ");
    std::cin >> X_util.helper;
    (void)X_util.rm_rf(DATA_DIRECTORY, "stuff.txt", "\n\tstuffing\n", true);
    (void)X_util.rm_rf(DATA_DIRECTORY_PROCESSED, "stuff.txt", "\n\tstuffing\n", true);
    (void)X_util.rm_rf(DATA_DIRECTORY_RAW, "stuff.txt", "\n\tstuffing\n", true);
    (void)X_util.rm_rf(DATA_DIRECTORY_SEQUENCED, "stuff.txt", "\n\tstuffing\n", true);
    printf("\ncheck the directory, should backfilled file :  ");
    std::cin >> X_util.helper;

    t997_data_reset();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void t997_data_reset()
{
    t997_populate();
    printf("\ncheck the directory, any key to delete (no filling) :  ");
    std::cin >> X_util.helper;
    (void)X_util.rm_rf(DATA_DIRECTORY, FILLER_NAME, FILLER_CONTENTS, true);
    printf("\ncheck the directory, only ./DATA/%s :  ", FILLER_NAME);
    std::cin >> X_util.helper;

    (void)X_util.rm_rf(DATA_DIRECTORY_PROCESSED, FILLER_NAME, FILLER_CONTENTS, true);
    (void)X_util.rm_rf(DATA_DIRECTORY_RAW, FILLER_NAME, FILLER_CONTENTS, true);
    (void)X_util.rm_rf(DATA_DIRECTORY_SEQUENCED, FILLER_NAME, FILLER_CONTENTS, true);
    printf("\ncheck the directory, has original structure with back-filled files :  ");
}


////~~~~


static void t997_populate()
{
    FILE* fptr = NULL;
    char dsub[BUF_D];
    for (int ii = 0; ii < t997_repz; ii++)
    {
        (void)sprintf(dsub, "dir_%d/", ii);

        (void)sprintf(X_util.helper, "%s%s", DATA_DIRECTORY, dsub);
        (void)X_util.exe_mkdir(X_util.helper);
        for (int ww = 0; ww < t997_repz; ww++)
        {
            sprintf(X_util.holder, "%spotatoe_%d.txt", X_util.helper, ww);
            fptr = fopen(X_util.holder, "w");
            (void)fputs(FILLER_CONTENTS, fptr);
            (void)fclose(fptr);
            printf("%s\n", X_util.holder);
        }

        (void)sprintf(X_util.helper, "%s%s", DATA_DIRECTORY_PROCESSED, dsub);
        (void)X_util.exe_mkdir(X_util.helper);
        for (int xx = 0; xx < t997_repz; xx++)
        {
            sprintf(X_util.holder, "%spotatoe_%d.txt", X_util.helper, xx);
            fptr = fopen(X_util.holder, "w");
            (void)fputs(FILLER_CONTENTS, fptr);
            (void)fclose(fptr);
            printf("%s\n", X_util.holder);
        }

        (void)sprintf(X_util.helper, "%s%s", DATA_DIRECTORY_RAW, dsub);
        (void)X_util.exe_mkdir(X_util.helper);
        for (int yy = 0; yy < t997_repz; yy++)
        {
            sprintf(X_util.holder, "%spotatoe_%d.txt", X_util.helper, yy);
            fptr = fopen(X_util.holder, "w");
            (void)fputs(FILLER_CONTENTS, fptr);
            (void)fclose(fptr);
            printf("%s\n", X_util.holder);
        }

        (void)sprintf(X_util.helper, "%s%s", DATA_DIRECTORY_SEQUENCED, dsub);
        (void)X_util.exe_mkdir(X_util.helper);
        for (int zz = 0; zz < t997_repz; zz++)
        {
            sprintf(X_util.holder, "%spotatoe_%d.txt", X_util.helper, zz);
            fptr = fopen(X_util.holder, "w");
            (void)fputs(FILLER_CONTENTS, fptr);
            (void)fclose(fptr);
            printf("%s\n", X_util.holder);
        }
    }
}


#endif    // UNIT_TESTING


/////////~~~~~~~~END>  task_997.cpp
