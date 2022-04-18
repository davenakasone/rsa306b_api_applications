/*
    this object is made for "*.r3f" files
    it will extract the IF data and place it into an output file
    data processing is also possbile

    adjust as needed
    "*.r3a" and "*.r3h" files are undesirable (for now)

    commonly used techniques:

        int fseek(FILE *stream, long int offset, int whence)
            int whence == SEEK_SET, go to the beginning of the file, resets EOF // call often
            int whence == SEEK_CUR, set the file pointer to the offset position
            int whence == SEEK_END, set the file pointer to EOF
        
        size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

        long int ftell(FILE *stream)

        FILE *fopen(const char *filename, const char *mode)

        int fclose(FILE *stream)

        int snprintf ( char * s, size_t n, const char * format, ... );

        int fputs(const char *str, FILE *stream)
*/


#ifndef H_r3f_manager_class
#define H_r3f_manager_class


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "r3f_manager_struct.h"    // <stdint.h>, <float.h>


#define BUF_HELPER 256
#define BUF_HOLDER 512


class r3f_manager
{
    public:

        r3f_manager();     // constructor
        ~r3f_manager();    // destructor

        void time_split_begin();      // records start of CPU time split
        double time_split_end();      // measures CPU time split and returns result
        double get_running_time();    // returns CPU seconds since instance created

        void decode_print(long int decode_start, long int decode_stop);                             // prints char and int data to match bytes
        void decode_write(const char* decode_file, long int decode_start, long int decode_stop);    // writes char and int data to match bytes

        r3f_manager_struct members;


    private:

        char helper[BUF_HELPER];
        char holder[BUF_HOLDER];
        FILE* fptr_read;
        FILE* fptr_write;

        bool time_split_is_marked;
        clock_t cpu_start;
        clock_t cpu_mark;
        clock_t cpu_now;

        r3f_manager_struct _members;

        void initialize();


};


#endif


////////~~~~~~~~END>  r3f_manager.h
