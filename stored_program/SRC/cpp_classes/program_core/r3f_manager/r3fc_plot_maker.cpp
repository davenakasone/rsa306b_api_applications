/*
    these functions help outputing data to plot
    remember that the latest sample occupies the lowest index
        ...the oldest sample is at the highest index
            use the "LIFO" or "stack" to prepare the data

        public:
            < 1 >  prepare_plot_from_header()
            < 2 >  prepare_plot_from_iq()

        private:
            #  none
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    gets the frequecny
    plot against:
        amplitude correction
        phase correction
    call after calling "file_proccess()"

    [ frequency  amplitude  phase ]
*/
void r3f_manager_class::prepare_plot_from_header
(
    const char* output_file
) 
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (output_file == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "allocate the file name");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    
    if (this->_fptr_write != NULL)
    {
        fclose(this->_fptr_write);
        this->_fptr_write = NULL;
    }
    this->_fptr_write = fopen(output_file, "w");
    if (this->_fptr_write == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "failed to open output file for writing");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        if (ii == this->_vars.number_of_table_entries-1)
        {
            snprintf(this->_holder, BUF_F-1, "%f,%f,%f",
                this->_vars.table_frequency[ii],
                this->_vars.table_amplitude[ii],
                this->_vars.table_phase[ii]);
        }
        else
        {
            snprintf(this->_holder, BUF_F-1, "%f,%f,%f\n",
                this->_vars.table_frequency[ii],
                this->_vars.table_amplitude[ii],
                this->_vars.table_phase[ii]);
        }
        fputs(this->_holder, this->_fptr_write);
    }
    fclose(this->_fptr_write);
    this->_fptr_write = NULL;
    
    #ifdef DEBUG_MAX
        snprintf(X_ddts, sizeof(X_ddts), "header data ready to plot, see '%s'", output_file);
        snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(false);
    #endif
}


/*
    public < 2 >
    prepares time series, using timestamp
    raw IF data from ADC is made into I and Q data
    scaling factor is applied

    [ time  I  Q ]

    don't forget: IQ(t) = I(t) + jQ(t)
    might want to apply more corrections and filter
*/
void r3f_manager_class::prepare_plot_from_iq
(
    const char* input_file,
    const char* output_file
) 
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (input_file == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "input file-path-name not allocated");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (output_file == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "output file-path-name not allocated");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->_fptr_read != NULL || 
        this->_fptr_write != NULL )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "FILE* are busy somewhere else");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    this->_fptr_read = fopen(input_file, "r");
    if (this->_fptr_read == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "failed to open:  %s", input_file);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_fptr_write = fopen(output_file, "w");
    this->_process_header(false);
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    this->_fptr_write = fopen(output_file, "w");
    
    double omega = 2 * M_PI * this->_vars.center_frequency_if_sampled_hz ;
    double period = 1 / this->_vars.samples_per_second;
    int total_data_frames = (this->_bytes_in_file - 
                             this->_vars.size_of_frame_bytes) / 
                             this->_vars.size_of_frame_bytes; 
    long int total_samples = this->_vars.number_of_samples_per_frame *
                             total_data_frames;
    std::queue<double> time_series;
    for (long int ii = 0; ii < total_samples; ii++)
    {
        time_series.push(ii*period);
    }

    std::stack<double> in_phase;
    std::stack<double> quadrature;
    int16_t sample_getter;
    for (long int ii = 1; ii <= total_data_frames; ii++)
    {
        this->_byte_index = this->_vars.size_of_frame_bytes * ii;
        fseek(this->_fptr_read, 0L, SEEK_SET);
        fseek(this->_fptr_read, this->_byte_index, SEEK_CUR);

        for (int jj = 0; jj < this->_vars.number_of_samples_per_frame; jj++)
        {
            fread(&sample_getter, sizeof(int16_t), 1, this->_fptr_read);
            in_phase.push(sample_getter *
                          this->_vars.sample_gain_scaling_factor *
                          std::cos(omega * time_series.front()));
            quadrature.push(sample_getter *
                            this->_vars.sample_gain_scaling_factor *
                            std::sin(omega * time_series.front()));
            time_series.pop();
        }
    }
    #ifdef DEBUG_MAX
        printf("\n\ttime series size:  %lu  ,  empty():  %d\n",
            time_series.size(), time_series.empty());
    #endif
    for (long int ii = 0; ii < total_samples; ii++)
    {
        time_series.push(ii*period);
    }

    for (long int ii = 1; ii <= total_samples; ii++)
    {
        if (ii == total_samples-1)
        {
            snprintf(this->_holder, BUF_F-1, "%0.12lf,%0.12lf,%0.12lf",
                time_series.front(),
                in_phase.top(),
                quadrature.top());
        }
        else
        {
            snprintf(this->_holder, BUF_F-1, "%0.12lf,%0.12lf,%0.12lf\n",
                time_series.front(),
                in_phase.top(),
                quadrature.top());
        }
        fputs(this->_holder, this->_fptr_write);
        time_series.pop();
        in_phase.pop();
        quadrature.pop();
    }

    fclose(this->_fptr_read); this->_fptr_read = NULL;
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    #ifdef DEBUG_MAX
        snprintf(X_ddts, sizeof(X_ddts), "IQ(t) ready : '%s' , ismpty vecs:  %d %d %d (want 1 1 1)",
            output_file,
            time_series.empty(),
            in_phase.empty(),
            quadrature.empty());
        snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(false);
    #endif
}


////////~~~~~~~~END>  r3fc_plot_maker.cpp
