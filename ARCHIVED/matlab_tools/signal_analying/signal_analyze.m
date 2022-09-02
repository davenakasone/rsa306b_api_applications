%{
    1  :  the signal analyzer
    2  :  get the frame

%}
close all;
clear all;
clc;
select = 2;

%-----------------------------------------------------------------------------------------------------
if select == 1
    in_samples = readtable("adc_ee482.csv");
    temp = size(in_samples);
    frames = temp(1) / 8178;
    adc = double(in_samples.Var1);
    %pspectrum(adc, 2*112e6)
    signalAnalyzer(adc(1:8178));
end


%-----------------------------------------------------------------------------------------------------
if select == 2
    in_samples = readtable("adc_ee482.csv");
    temp = size(in_samples);
    frames = temp(1) / 8178;
    adc = double(in_samples.Var1);
    %spectrogram(fft(adc(1:8178)));
    %spectrogram(fft(adc(8178*1:8178*2)));
    spectrogram(fft(adc(8178*2:8178*3)));
end


%-----------------------------------------------------------------------------------------------------
if select == 99

end
%%%%%%%%~~~~~~~~END>  xxx.m