Hippocampal Sharp Wave Ripple Detection and Analysis
=============

Actually it is mainly based on a digital band-pass filter using window functions.

With fixed passband(1000Hz~1500Hz) and center frequency(1250Hz).

It can be applied on Arduino due (32-bit cortex-m3 ARM).

The further improvement is basically try to make it flexiable, to provide a GUI with some specifications as input.

The window function applying in the project is Chebyshev windows using Parks-McClellan algorithm, the source code 

and h-file are from 'http://t-filter.appspot.com' temporarily.

If there are any comments or suggestions, please sent me an E-mail to 'diegozengtao@gmail.com'


===============Update on July 30th===============

Now the project has huge development: It is a flexible bandpass filter using four different wiondow functions(Kaiser,

Hanning, Hamming, and rectangular). The hardware is still  Arduino due (32-bit cortex-m3 ARM).

The input are: 

1. The sidelobe attenuation 

2. fc1 and fc2 (For hanning, hamming and retangular)
                   
   fs1, fp1, fp2, fs2 (For kaiser)
                      
3. Sampling frequency (Users need to do calibration of the hardware setting in 'Calibration.ino'
                   
4. The input signal will convey into the Arduino due board through the analongInput(A0)
                   
The output will be exported by digitalOutput DAC0/DAC1, and the final results will be represented in the Oscilloscope. 

For the convolution algrithom, there is a reference from 'http://t-filter.appspot.com'. Other codes are my indenpendent 

work.

If there are any comments or suggestions, please sent me an E-mail to 'diegozengtao@gmail.com'

===============Update on September 5th===============

User Manual 1.0 Uploaded.

This is my first time to write user manual in LaTex.

Please complie it with “PdfTex”

Forgive me about the Tex code form. I will improve my programming skills in the future by practising.

If there are any comments or suggestions, please sent me an E-mail to 'diegozengtao@gmail.com'
