/*
	removing "w" type functions and variables
	use designated API member for Linux 
	make sure the "RSA_API.h" is not for windows
*/

#include "rsa_cpp.h"
char holder[BIG_WIDTH];


void err_check
(
	RSA_API::ReturnStatus rs
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	// noError = 0 is the only signal that indicates hardware is satisfactory
	// any other error code is a problem, and modifications are needed before proceeding
	if (rs != RSA_API::noError) 
	{
		std::cout << "\nError: " << rs << std::endl;
		//std::system("pause");
		std::exit(0);
	}
}


////~~~~


void print_device_info
(
	int* deviceIDs, 
	int numFound, 
	const char** deviceSerial, 
	const char** deviceType
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	std::cout << "Number of devices found: " << numFound << std::endl;
	for (int i = 0; i < numFound; i++)
	{
		std::cout << "Device ID: " << i;
		std::cout << ", Serial Number: " << deviceSerial[i];
		std::cout << ", Device Type: " << deviceType[i] << std::endl;
	}
}


////~~~~


int search_connect
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	int numFound = 0;
	int* deviceIDs;
	const char** deviceSerial;
	const char** deviceType;
	char apiVersion[200];
	RSA_API::ReturnStatus rs;

	rs = RSA_API::DEVICE_GetAPIVersion(apiVersion);
	std::cout << "API Version: " << apiVersion << std::endl;
	rs = RSA_API::DEVICE_SearchInt(&numFound, &deviceIDs, &deviceSerial, &deviceType);
	if (numFound < 1)
	{
		std::cout << "No devices found, exiting script." << std::endl;
		//std::system("pause");
		std::exit(0);
	}
	else if (numFound == 1)
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		rs = RSA_API::DEVICE_Connect(deviceIDs[0]);
		err_check(rs);
	}
	else
	{
		print_device_info(deviceIDs, numFound, deviceSerial, deviceType);
		int dev;
		std::cout << "Select device between 0 and " << (numFound - 1) << "\n> ";
		std::cin >> dev;
		rs = RSA_API::DEVICE_Connect(deviceIDs[dev]);
		err_check(rs);
		std::cout << "Connected to device " << dev;
		std::cout << ", Serial Number: " << deviceSerial[dev];
		std::cout << ", Device Type: " << deviceType[dev] << std::endl;
	}

	return 0;
}


//// ~~~~


RSA_API::Spectrum_Settings config_spectrum
(
	double cf, 
	double refLevel, 
	double span, 
	double rbw
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::SPECTRUM_SetEnable(true);
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);
	
	RSA_API::SPECTRUM_SetDefault();
	RSA_API::Spectrum_Settings specSet;
	RSA_API::SPECTRUM_GetSettings(&specSet);
	specSet.span = span;
	specSet.rbw = rbw;
	RSA_API::SPECTRUM_SetSettings(specSet);
	RSA_API::SPECTRUM_GetSettings(&specSet);
	
	return specSet;
}


////~~~~


double* create_frequency_array
(
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double* freq = NULL;
	int n = specSet.traceLength;
	freq = new double[n]; // see if you can find the delete/free()
	for (int i=0; i < specSet.traceLength; i++)
	{
		freq[i] = specSet.actualStartFreq + specSet.actualFreqStepSize*i;
	}

	return freq;
}


////~~~~


float* acquire_spectrum
(
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	bool ready = false;
	int timeoutMsec = 0;

	RSA_API::SpectrumTraces trace = RSA_API::SpectrumTrace1;
	int maxTracePoints = specSet.traceLength;
	int outTracePoints = 0;
	float* traceData = NULL;
	int n = maxTracePoints;
	traceData = new float[n]; // where is the delete?
	
	RSA_API::DEVICE_Run();
	RSA_API::SPECTRUM_AcquireTrace();
	while (ready == false)
	{
		RSA_API::SPECTRUM_WaitForTraceReady(timeoutMsec, &ready);
	}
	RSA_API::SPECTRUM_GetTrace(trace, maxTracePoints, traceData, &outTracePoints);
	RSA_API::Spectrum_TraceInfo traceInfo;
	RSA_API::SPECTRUM_GetTraceInfo(&traceInfo);
	RSA_API::DEVICE_Stop();

	std::cout << "Trace Data Status: " << traceInfo.acqDataStatus << std::endl;

	return traceData;
}


////~~~~


int peak_power_detector
(
	float* traceData,
	double* freq, 
	RSA_API::Spectrum_Settings specSet
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	int peakIndex = 0;
	for (int i = 0; i < specSet.traceLength; i++)
	{
		if (traceData[i] > traceData[peakIndex])
		{
			peakIndex = i;
		}
	}

	return peakIndex;
}


////~~~~


void spectrum_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double cf = 1e9;
	double refLevel = -30;
	double span = 40e6;
	double rbw = 300e3;
	RSA_API::Spectrum_Settings specSet;
	double* freq = NULL;
	float* traceData = NULL;
	int peakIndex = 0;

	search_connect();
	RSA_API::CONFIG_Preset();
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	specSet = config_spectrum(cf, refLevel, span, rbw);
	traceData = acquire_spectrum(specSet);
	freq = create_frequency_array(specSet);
	peakIndex = peak_power_detector(traceData, freq, specSet);
	
	std::cout << "Start frequency: " << freq[0] << std::endl;
	std::cout << "Center frequency: " << freq[(specSet.traceLength - 1) / 2] << std::endl;
	std::cout << "Stop frequency: " << freq[specSet.traceLength - 1] << std::endl;
	std::cout << "Maximum value: " << traceData[peakIndex] << " dBm" << std::endl;
	std::cout << "Frequency of max amplitude: " << freq[peakIndex] << " Hz" << std::endl;

	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();

	//Clean up arrays
	delete[] freq;
	delete[] traceData;
	freq = NULL;
	traceData = NULL;

	//Stop the program so we can see printouts
	//std::system("pause");
	std::cout << "\nspectrum_example complete  ,  any key to continue:  ";
	std::cin >> holder;
}


////~~~~ 


double* config_block_iq
(
	double cf, 
	double refLevel, 
	double iqBw, 
	int recordLength
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double iqSampleRate = 0;
	double* time = NULL;
	int n = recordLength;
	time = new double[n];
	RSA_API::ReturnStatus rs;

	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	RSA_API::IQBLK_SetIQBandwidth(iqBw);
	RSA_API::IQBLK_SetIQRecordLength(recordLength);
	rs = RSA_API::IQBLK_GetIQSampleRate(&iqSampleRate);
	err_check(rs);

	//simple C++ implementation of numpy.linspace()
	double step = recordLength/iqSampleRate/(recordLength-1);
	for (int i = 0; i < recordLength; i++)
	{
		time[i] = i*step;
	}

	return time;
}


////~~~~


RSA_API::Cplx32* acquire_block_iq
(
	int recordLength
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::Cplx32* iqData = NULL;
	int n = recordLength;
	iqData = new RSA_API::Cplx32[n]; // who calls delete?
	bool ready = false;
	int timeoutMsec = 100;
	int outLength = 0;

	RSA_API::DEVICE_Run();
	RSA_API::IQBLK_AcquireIQData();
	while (ready == false)
	{
		RSA_API::IQBLK_WaitForIQDataReady(timeoutMsec, &ready);
	}
	RSA_API::IQBLK_GetIQDataCplx(iqData, &outLength, recordLength);
	RSA_API::DEVICE_Stop();

	return iqData;
}


////~~~~


void block_iq_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_connect();
	double cf = 1e9;
	double refLevel = 0;
	double iqBw = 40e6;
	int recordLength = 1000;
	double* time = NULL;
	RSA_API::Cplx32* iqData = NULL;

	time = config_block_iq(cf, refLevel, iqBw, recordLength);
	iqData = acquire_block_iq(recordLength); 
	std::cout << "Disconnecting." << std::endl;
	std::cout << "Also this is boring because I can't plot anything." << std::endl;
	RSA_API::DEVICE_Disconnect();

	//Clean up arrays
	delete[] time;
	delete[] iqData;
	time = NULL;
	iqData = NULL;

	//Stop the program so we can see printouts
	//system("pause");
	std::cout << "\nblock_iq_example complete  ,  any key to continue:  ";
	std::cin >> holder;
}


////~~~~


void config_dpx
(
	double cf, 
	double refLevel, 
	double span, 
	double rbw
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double yTop = refLevel;
	double yBottom = yTop - 100;
	double timeResolution = 1e-3;
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	RSA_API::DPX_SetEnable(true);
	RSA_API::DPX_SetParameters(span, rbw, 801, 1, RSA_API::VerticalUnit_dBm, yTop, yBottom, false, 1.0, false);
	RSA_API::DPX_SetSogramParameters(timeResolution, timeResolution, yTop, yBottom);
	RSA_API::DPX_Configure(true, true);
	RSA_API::DPX_SetSpectrumTraceType(0, RSA_API::TraceTypeMaxHold);
	RSA_API::DPX_SetSpectrumTraceType(1, RSA_API::TraceTypeAverage);
	RSA_API::DPX_SetSpectrumTraceType(2, RSA_API::TraceTypeMinHold);
}


////~~~~


void acquire_dpx
(
	RSA_API::DPX_FrameBuffer* fb
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	bool frameAvailable = false;
	bool ready = false;

	RSA_API::DEVICE_Run();
	while (frameAvailable == false)
	{
		RSA_API::DPX_IsFrameBufferAvailable(&frameAvailable);
	}
	while (ready == false)
	{
		RSA_API::DPX_WaitForDataReady(100, &ready);
	}
	RSA_API::DPX_GetFrameBuffer(fb);
	RSA_API::DPX_FinishFrameBuffer();
	RSA_API::DEVICE_Stop();
}


////~~~~


void dpx_example()
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_connect();
	double cf = 2.4453e9;
	double refLevel = -30;
	double span = 40e6;
	double rbw = 300e3;
	RSA_API::DPX_FrameBuffer fb;

	config_dpx(cf, refLevel, span, rbw);
	acquire_dpx(&fb);
	std::cout << "\nFFTs in frame: " << fb.fftCount << std::endl;
	std::cout << "DPX FrameBuffers acquired: " << fb.frameCount << std::endl;
	std::cout << "DPX Bitmap is "<< fb.spectrumBitmapWidth << 
		" x " << fb.spectrumBitmapHeight << " pixels." << std::endl;
	std::cout << "DPX Spectrogram is " << fb.sogramBitmapWidth <<
		" x " << fb.sogramBitmapHeight << " pixels." << std::endl;
	std::cout << "Valid traces in spectrogram: " << fb.sogramBitmapNumValidLines << std::endl;
	
	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();

	//Stop the program so we can see printouts
	//system("pause");
	std::cout << "\ndpx_example complete  ,  any key to continue:  ";
	std::cin >> holder;
}


////~~~~


void config_if_stream
(
	double cf,
	double refLevel, 
	char* fileDir, 
	char* fileName, 
	int durationMsec
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	RSA_API::IFSTREAM_SetDiskFilePath(fileDir);
	RSA_API::IFSTREAM_SetDiskFilenameBase(fileName);
	RSA_API::IFSTREAM_SetDiskFilenameSuffix(-2);
	RSA_API::IFSTREAM_SetDiskFileLength(durationMsec);
	RSA_API::IFSTREAM_SetDiskFileMode(RSA_API::StreamingModeFramed);
	RSA_API::IFSTREAM_SetDiskFileCount(1);
}


////~~~~


void if_stream_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_connect();
	double cf = 2.4453e9;
	double refLevel = -30;
	char fileDir [BIG_WIDTH] = "C:\\SignalVu-PC Files\\";
	char fileName [BIG_WIDTH] = "if_stream_test";
	int durationMsec = 1000;
	int waitTime = 10;
	bool writing = true;

	config_if_stream(cf, refLevel, fileDir, fileName, durationMsec);

	RSA_API::DEVICE_Run();
	RSA_API::IFSTREAM_SetEnable(true);
	while (writing == true)
	{
		sleep(waitTime/1000);
		RSA_API::IFSTREAM_GetActiveStatus(&writing);
	}
	RSA_API::DEVICE_Stop();
	std::cout << "Streaming finished." << std::endl;
	
	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();

	//Stop the program so we can see printouts
	//system("pause");
	std::cout << "\nany key to continue:  ";
	std::cin >> holder;
}


////~~~~


void config_iq_stream
(
	double cf, 
	double refLevel, 
	double bw, 
	char* fileName, 
	RSA_API::IQSOUTDEST dest, 
	int suffixCtl, 
	int durationMsec
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	double bwActual = 0;
	double sampleRate = 0;
	RSA_API::CONFIG_SetCenterFreq(cf);
	RSA_API::CONFIG_SetReferenceLevel(refLevel);

	RSA_API::IQSTREAM_SetAcqBandwidth(bw);
	RSA_API::IQSTREAM_SetOutputConfiguration(dest, RSA_API::IQSODT_INT16);
	RSA_API::IQSTREAM_SetDiskFilenameBase(fileName);
	RSA_API::IQSTREAM_SetDiskFilenameSuffix(suffixCtl);
	RSA_API::IQSTREAM_SetDiskFileLength(durationMsec);
	RSA_API::IQSTREAM_GetAcqParameters(&bwActual, &sampleRate);
}


////~~~~


void iqstream_status_parser
(
	uint32_t acqStatus
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	if (acqStatus == 0)
		printf("No errors in IQ streaming detected.\n");
	else
	{
		if (acqStatus & RSA_API::IQSTRM_STATUS_OVERRANGE)
		{
			std::cout << "Input overrange." << std::endl;
		}
		if (acqStatus & RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY)
		{
			std::cout << "Streaming discontinuity, loss of data has occurred." << std::endl;
		}
		if (acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT)
		{
			std::cout << "Input buffer > 75% full." << std::endl;
		}
		if (acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT)
		{
			std::cout << "Input buffer overflow, IQStream processing too slow, data loss has occurred." << std::endl;
		}
		if (acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT)
		{
			std::cout << "Output buffer > 75% full." << std::endl;
		}
		if (acqStatus & RSA_API::IQSTRM_STATUS_OBUFFOVFLOW)
		{
			std::cout << "Output buffer overflow, file writing too slow, data loss has occurred." << std::endl;
		}
	}
}


////~~~~


void iq_stream_example
(
	void
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_connect();
	double cf = 2.4453e9;
	double refLevel = -30;
	
	double bw = 40e6;
	RSA_API::IQSOUTDEST dest = RSA_API::IQSOD_FILE_SIQ;
	int suffixCtl = -2;
	int durationMsec = 2000;
	int waitTime = 10;
	char fileName[BIG_WIDTH] = "C:\\SignalVu-PC Files\\iq_stream_test";
	RSA_API::IQSTRMFILEINFO iqStreamInfo;

	bool complete = false;
	bool writing = false;

	config_iq_stream(cf, refLevel, bw, fileName, dest, suffixCtl, durationMsec);
	RSA_API::DEVICE_Run();
	RSA_API::IQSTREAM_Start();
	while (complete == false)
	{
		sleep(waitTime);
		RSA_API::IQSTREAM_GetDiskFileWriteStatus(&complete, &writing);
	}
	RSA_API::IQSTREAM_Stop();
	std::cout << "Streaming finished." << std::endl;
	RSA_API::IQSTREAM_GetDiskFileInfo(&iqStreamInfo);
	iqstream_status_parser(iqStreamInfo.acqStatus);
	RSA_API::DEVICE_Stop();

	std::cout << "Disconnecting." << std::endl;
	RSA_API::DEVICE_Disconnect();

	//Stop the program so we can see printouts
	//system("pause");
	std::cout << "\nany key to continue:  ";
	std::cin >> holder;
}


////~~~~


void config_trigger
(
	RSA_API::TriggerMode trigMode, 
	double trigLevel, 
	RSA_API::TriggerSource trigSource
)
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	RSA_API::TRIG_SetTriggerMode(trigMode);
	RSA_API::TRIG_SetIFPowerTriggerLevel(trigLevel);
	RSA_API::TRIG_SetTriggerSource(trigSource);
	RSA_API::TRIG_SetTriggerPositionPercent(10);
}


////~~~~


void if_playback()
{
#ifdef DEBUG_CLI
	printf("\n\t%s()  ,  %d\n", __func__, __LINE__);
#endif

	search_connect();
	const char* fileName = "C:\\SignalVu-PC Files\\if_stream_test.r3f";
	char FileName[300];
	snprintf(FileName, 300, "%s", fileName);   // %S is 1-byte-char type for sWprintf
	
	FILE* fp = fopen(FileName, "rb");
	if (fp == NULL)
	{
		printf("Error Opening File: %s\n", FileName);
	}
	
	int start = 0;
	int stop = 100;
	double skip = 0;
	bool loop = false;
	bool rt = true;
	bool complete = false;

	RSA_API::PLAYBACK_OpenDiskFile(FileName, start, stop, skip, loop, rt);
	RSA_API::DEVICE_Run();
	while (complete == false)
	{
		RSA_API::PLAYBACK_GetReplayComplete(&complete);
	}
	std::cout << "Playback Complete: " << complete << std::endl;
	//std::system("pause");
	std::cout << "\nany key to continue:  ";
	std::cin >> holder;
}


////////~~~~~~~~END>  consumers.cpp
