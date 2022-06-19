# Program Concept
the goal is to make a program that can interface with the Tekronix RSA306B Spectrum Analyzer
scanning a range of 0.5 GHz to 1.5 GHz is the likely range of partial discharges
field testing will be needed to determine a specific range and power
when successful interfacing is achived, power equipment can be monitored
other enhancements are possible when interfacing is satisfactory

## Resources
- this repository          : [here](https://github.com/davenakasone/rsa306b_api_applications)
- youtube                  : (here)[https://www.youtube.com/playlist?list=PLFYKagNjVg0VuUz5Fuu-ekX6TbwMRO9uI]
- pictures and video       : (here)[https://photos.app.goo.gl/BEBcb8ixF9oWZtsN8]
- additional documentation : (here)[https://drive.google.com/drive/folders/1-Yi1jUahgB7YDmauL3ozKffGKSb-tnm9?usp=sharing]

## File Structure
rsa306b_api_applications/

    API_demos_by_Tekronix   // see [here](https://github.com/tektronix/RSA_API)

    common                  // resources for API use
    
    original_Linux_API      // from manufacturer, 1 header, 2 dynamic libraries

    working                 // basic tests to ensure interfacing, self-contained resources per directory
        cpp_block_IQ_v1     // gets IQ from Cplx32 type, includes time, prepared for class use, looks good
        cpp_class_v1        // trying to make a class where the API abstraction is removed (this is the best way so far)
        cpp_class_v2        // most viable design so far, using OO, 19June2022
        cpp_DPX_v1          // basic view of DPX data, may be useful, but very heavy
        cpp_freq_span_v1    // basic test using frequency spectrum
        cpp_freq_span_v2    // frequency spectrum, unpacking parameters to prepare for class use, looks good
        cpp_IF_stream_v1    // has playback, makes very big .r3f files
        cpp_IQ_stream_v1    // makes very big .sig files, probably not best idea, check playbacks
        example_c           // the C code works, very basic, just to see if device is ok
        example_cpp         // the C++ code works, must be adapted to Linux, good examples here + trigger
        example_python      // it works, but python is a bad choice for data acquisition
        iq_stream_cpp_v1    // the IQ files are 400 MB each...
        read_write_C_v1     // tried to do too much, program failed
        read_write_C_v2     // program can maintain for a few samples, then fails
        scanning_C_v1       // using C works, but it will take too much time to get data structures...no STL

    fundamentals            // building blocks that can be used, also a sandbox

## API Information
API Version          :  1.0.0014
FPGA Version         :  V2.1
Firmware Version     :  V1.7
Hardware Version     :  V7
Nomenclature         :  RSA306B
Serial Number        :  B037150

## License
Licenses for software are available for $643,000,000.00 per user per year
Contact us for details [here](mailto:nakasd3@unlv.nevada.edu)