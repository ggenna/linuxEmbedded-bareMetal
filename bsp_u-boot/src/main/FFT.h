#ifndef _FFT_H_
#define _FFT_H_

/* function prototypes */
void fft(int N, float (*x)[2], float (*X)[2]);
void fft_rec(int N, int offset, int delta,
             float (*x)[2], float (*X)[2], float (*XX)[2]);
void ifft(int N, float (*x)[2], float (*X)[2]);



#endif //end _FFT_H_
