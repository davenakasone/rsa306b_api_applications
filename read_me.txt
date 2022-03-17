the goal is to make a program that can interface with the Tekronix RSA306B Spectrum Analyzer
some outputs of the spectrum analyzer are over 400 MB per measurement
scanning a range of 0.5 GHz to 1.5 GHz is the likely range of partial discharges
field testing will be needed to determine a specific range and power
when successful interfacing is achived, power equipment can be monitored
other enhancements are possible when interfacing is satisfactory


rsa306b_api_applications/

    API_demos_by_Tekronix   # https://github.com/tektronix/RSA_API

    common                  # resources for API use
    
    original_Linux_API      # from manufacturer

    working                 # basic tests to ensure interfacing, self-contained resources per directory
        cpp_freq_span_v1    # basic test using frequency spectrum
        cpp_freq_span_v2    # frequency spectrum, unpacking parameters to prepare for class use, looks good
        example_c           # the C code works, very basic, just to see if device is ok
        example_cpp         # the C++ code works, must be adapted to Linux, good examples here
        example_python      # it works, but python is a bad choice for data acquisition
        iq_stream_cpp_v1    # the IQ files are 400 MB each...
        read_write_C_v1     # tried to do too much, program failed
        read_write_C_v2     # program can maintain for a few samples, then fails
        scanning_C_v1       # using C works, but it will take too much time to get data structures...no STL

    fundamentals            # building blocks that can be used


API Version : 1.0.0014
Detected Devices:
deviceID: 0,	 SN: B037150,	 Type: RSA306B

additional documentation can be found in the google drive:
    https://drive.google.com/drive/folders/1-Yi1jUahgB7YDmauL3ozKffGKSb-tnm9?usp=sharing

unofficial pictures and video:
    https://photos.app.goo.gl/BEBcb8ixF9oWZtsN8
