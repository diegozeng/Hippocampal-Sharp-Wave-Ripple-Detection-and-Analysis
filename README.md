Filter-Design
=============

Actually it is a digital band-pass filter using window functions.

With fixed passband(1000Hz~1500Hz) and center frequency(1250Hz).

It can be applied on Arduino due (32-bit cortex-3 ARM).

The further improvement is basically try to make it flexiable, to provide a GUI with some specifications as input.

The window function applying in the project is Chebyshev windows using Parks-McClellan algorithm, the source code 

and h-file are from 'http://t-filter.appspot.com' temporarily.

If there are any comments or suggestions, please sent me an E-mail to 'diegozengtao@gamil.com'
