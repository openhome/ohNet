/*
   parametric stereo bitstream processing and decoding
 */

#ifndef __PS_BITDEC_H
#define __PS_BITDEC_H

#include "FFR_bitbuffer.h"
#include "ps_dec.h"

#define EXTENSION_ID_PS_CODING   2


Word16
ReadPsData (HANDLE_PS_DEC h_ps_dec,
            HANDLE_BIT_BUF hBitBuf,
            Word16 nBitsLeft);

void
DecodePs(HANDLE_PS_DEC h_ps_dec);


#endif
