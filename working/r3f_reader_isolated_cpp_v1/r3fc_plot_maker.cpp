/*
    these functions help outputing data to plot
    remember that the latest sample occupies the lowest index
        ...the oldest sample is at the highest index
            use the "LIFO" or "stack" to prepare the data

        public:
            < 1 >  prepare_plot_from_header()
            < 2 >  prepare_plot_from_data()

        private:
            # none
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (output_file == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the file name\n");
        #endif
        return;
    }
    this->_fptr_write = fopen(output_file, "w");

    for (int ii = 0; ii < this->_members.number_of_table_entries; ii++)
    {
        snprintf(this->_holder, BUF_HOLDER-1, "%f,%f,%f,\n",
            this->_members.table_frequency[ii],
            this->_members.table_amplitude[ii],
            this->_members.table_phase[ii]);
        fputs(this->_holder, this->_fptr_write);
    }
    fclose(this->_fptr_write);
    this->_fptr_write = NULL;
    #ifdef DEBUG_MIN
        printf("\n\theader data ready to plot, see '%s'\n",
            output_file);
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
void r3f_manager_class::prepare_plot_from_data
(
    const char* input_file,
    const char* output_file
) 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (input_file == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the input file name\n");
        #endif
        return;
    }
    if (output_file == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the output file name\n");
        #endif
        return;
    }
    if (this->_fptr_read != NULL || 
        this->_fptr_write != NULL )
    {
        #ifdef DEBUG_MIN
            printf("\n\terror in FILE* members\n");
        #endif
        return;
    }

    this->_fptr_read = fopen(input_file, "r");
    if (this->_fptr_read == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinput file not found\n");
        #endif
        return;
    }
    this->_fptr_write = fopen(output_file, "w");
    this->_process_header(false);
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    this->_fptr_write = fopen(output_file, "w");
    
    double omega = 2 * M_PI * this->_members.center_frequency_if_sampled_hz ;
    double period = 1 / this->_members.samples_per_second;
    int total_data_frames = (this->_bytes_in_file - 
                             this->_members.size_of_frame_bytes) / 
                             this->_members.size_of_frame_bytes; 
    long int total_samples = this->_members.number_of_samples_per_frame *
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
        this->_byte_index = this->_members.size_of_frame_bytes * ii;
        fseek(this->_fptr_read, 0L, SEEK_SET);
        fseek(this->_fptr_read, this->_byte_index, SEEK_CUR);

        for (int jj = 0; jj < this->_members.number_of_samples_per_frame; jj++)
        {
            fread(&sample_getter, sizeof(int16_t), 1, this->_fptr_read);
            in_phase.push(sample_getter *
                          this->_members.sample_gain_scaling_factor *
                          std::cos(omega * time_series.front()));
            quadrature.push(sample_getter *
                            this->_members.sample_gain_scaling_factor *
                            std::sin(omega * time_series.front()));
            time_series.pop();
        }
    }
    #ifdef DEBUG_MIN
        printf("\n\ttime series size:  %lu  ,  empty():  %d\n",
            time_series.size(), time_series.empty());
    #endif
    for (long int ii = 0; ii < total_samples; ii++)
    {
        time_series.push(ii*period);
    }

    for (long int ii = 1; ii <= total_samples; ii++)
    {
        snprintf(this->_holder, BUF_HOLDER-1, "%0.12lf,%0.12lf,%0.12lf,\n",
            time_series.front(),
            in_phase.top(),
            quadrature.top());
        fputs(this->_holder, this->_fptr_write);
        time_series.pop();
        in_phase.pop();
        quadrature.pop();
    }

    fclose(this->_fptr_read); this->_fptr_read = NULL;
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    #ifdef DEBUG_MIN
        printf("\n\tIQ(t) data ready to plot, see '%s'\n",
            output_file);
        printf("%d %d %d\n",
            time_series.empty(),
            in_phase.empty(),
            quadrature.empty());
    #endif
}


////////~~~~~~~~END>  r3fc_plot_maker.cpp
