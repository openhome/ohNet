/*
   fft functions
 */
#ifndef __FFT32X32S_H__
#define __FFT32X32S_H__

#include "typedef.h"

void DSP_fft32x32s(Word32 npoints,
                   Word32 * ptr_x ) ;

void inv_dit_fft_8pt(Word32 *x, Word32 *real, Word32 *imag);

#endif
