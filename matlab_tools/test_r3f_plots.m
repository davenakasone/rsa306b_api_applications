%{
    1  :  try plotting the corection data from the "*.r3f" 
    2  :  try plotting the block data from the "*.r3f" 

%}
close all;
clear all;
clc;
select = 1;

%-----------------------------------------------------------------------------------------------------
if select == 1
    corrections = readtable("plot_header.csv");
    temp = size(corrections);
    table_size = temp(1);
    frequencies = corrections.Var1 ./ 1e6;
    amplitudes = corrections.Var2
    phases = rad2deg(corrections.Var3);
    
    figure(Position=[100, 100, 900, 900]);
    
    subplot(2, 1, 1);
    hold on;
    title("Amplitude Corrections", FontSize = 20);
    xlabel("frequency [MHz]", FontSize=15);
    ylabel("amplitude [dB]", FontSize=15);
    plot(frequencies, amplitudes, "b-", LineWidth=3);
    grid on;
    hold off;
    
    subplot(2, 1, 2);
    hold on;
    title("Phase Corrections", FontSize = 20);
    xlabel("frequency [MHz]", FontSize=15);
    ylabel("amplitude [rad/sec]", FontSize=15);
    plot(frequencies, phases, "r-", LineWidth=3);
    grid on;
    hold off;
end


%-----------------------------------------------------------------------------------------------------
if select == 2
    raw_data = readtable("plot_data.csv")
    t_t = raw_data.Var1;
    I_t = raw_data.Var2;
    Q_t = raw_data.Var3;
    temp = size(t_t);
    data_size = temp(1);

    skip = 100;
    %
    dots = 1000;
    range_t = [min(t_t, [], "all"), max(t_t, [], "all")];
    buf_t = 0;%(range_t(2) - range_t(1)) / dots;
    range_I = [min(I_t, [], "all"), max(I_t, [], "all")];
    buf_I = 0;%(range_I(2) - range_I(1)) / dots;
    range_Q = [min(Q_t, [], "all"), max(Q_t, [], "all")];
    buf_Q = 0;%(range_Q(2) - range_Q(1)) / dots;
    axis_t = linspace(range_t(1)-buf_t, range_t(2)+buf_t, dots);
    axis_I = linspace(range_I(1)-buf_I, range_I(2)+buf_I, dots);
    axis_Q = linspace(range_Q(1)-buf_Q, range_Q(2)+buf_Q, dots);
    %}
    figure(Position=[100, 100, 2000, 1000]);
    hold on;
    grid on;
    view(45, 25);
    title("In-Phase and Quadrature components of Intermidiate Frequency", FontSize=20);
    %}
    xlim([range_t(1)-buf_t, range_t(2)+buf_t]);
    ylim([range_I(1)-buf_I, range_I(2)+buf_I]);
    zlim([range_Q(1)-buf_Q, range_Q(2)+buf_Q]);
    %}
    xlabel("time (s)", FontSize=10);
    ylabel("I", FontSize=10);
    zlabel("Q", FontSize=10);
    %
    plot3(axis_t, 0*axis_t, 0*axis_t, "k-", LineWidth=2);
    plot3(0*axis_I, axis_I, 0*axis_I, "k-", LineWidth=2);
    plot3(0*axis_Q, 0*axis_Q, axis_Q, "k-", LineWidth=2);
    %}

    %plot3(t_t(3), I_t(3), Q_t(3), "r.", LineWidth=5, MarkerSize=10);
    for ii = 1:skip:data_size
        %plot3(t_t, I_t, Q_t, "r-", LineWidth=1);
        quiver3(t_t(ii), 0, 0, t_t(ii), I_t(ii), Q_t(ii));
    end
    hold off;
end


%-----------------------------------------------------------------------------------------------------
if select == 99

end
%%%%%%%%~~~~~~~~END>  xxx.m