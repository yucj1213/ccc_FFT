%利用MATLAB绘制不同的结果图像并进行比较分析
clear;clc;

aie_data_input = importdata("input.txt");
FFT_data_in = aie_data_input(:,1)+aie_data_input(:,2)*i;
FFT_out_matlab = fft(FFT_data_in);
real_FFT_out_matlab=real(FFT_out0);
imag_FFT_out_matlab=imag(FFT_out0);
real_int16_FFT_out_matlab=aie_srs(real_FFT_out0, 0, 16);
imag_int16_FFT_out_matlab=aie_srs(imag_FFT_out0, 0, 16);
int16_FFT_out_matlab=real_int16_FFT_out_matlab+imag_int16_FFT_out_matlab*i;

FFT_out_aieemu_txt = importdata("FFT_out_aieemu.txt");
FFT_out_aieemu = FFT_out_aieemu_txt(:,1)+FFT_out_aieemu_txt(:,2)*i;
FFT_out_hardware_txt = importdata("FFT_out_hardware.txt");
FFT_out_hardware = FFT_out_hardware_txt(:,1)+FFT_out_hardware_txt(:,2)*i;
L_fft=length(FFT_data_in);

% figure(1)
% subplot(1,3,1)
% title("aieemu仿真结果");
% plot(1:length(FFT_out_aieemu),abs(FFT_out_aieemu));

subplot(1,2,1)
title("matlab仿真结果") 
hold on
plot(1:length(int16_FFT_out_matlab),abs(int16_FFT_out_matlab));
axis([0 L_fft 0 32768])

subplot(1,2,2)
title("hardware运行结果")
hold on
plot(1:length(FFT_out_hardware),abs(FFT_out_hardware));
axis([0 L_fft 0 32768])

X=abs(int16_FFT_out_matlab)-abs(FFT_out_hardware);

figure(2)
title("hardware compare with matlab")
hold on
plot(1:length(FFT_out_hardware),X);
