/*
   decoder main
 */

#ifndef AACDECODER_H
#define AACDECODER_H

#include "typedef.h"
#include "stdio.h"
#include "sbrdecoder.h"
#include "FFR_bitbuffer.h"


typedef enum {
  AAC_DEC_OK = 0x0,
  AAC_DEC_UNSUPPORTED_FORMAT,
  AAC_DEC_DECODE_FRAME_ERROR,
  AAC_DEC_INVALID_CODE_BOOK,
  AAC_DEC_UNSUPPORTED_WINOW_SHAPE,
  AAC_DEC_PREDICTION_NOT_SUPPORTED_IN_LC_AAC,
  AAC_DEC_UNIMPLEMENTED_CCE,
  AAC_DEC_UNIMPLEMENTED_PCE,
  AAC_DEC_UNIMPLEMENTED_LFE,
  AAC_DEC_UNIMPLEMENTED_GAIN_CONTROL_DATA,
  AAC_DEC_OVERWRITE_BITS_IN_INPUT_BUFFER,
  AAC_DEC_CANNOT_REACH_BUFFER_FULLNESS,
  AAC_DEC_TNS_RANGE_ERROR,
  AAC_DEC_TNS_ORDER_ERROR,
  AAC_DEC_TOO_MANY_CHANNELS
}
AAC_DEC_STATUS;


typedef struct AAC_DECODER_INSTANCE *AACDECODER;

#define  FRAME_SIZE 1024


/* initialization of aac decoder */
AACDECODER CAacDecoderOpen(HANDLE_BIT_BUF hBitBufCore,
                           SBRBITSTREAM *streamSbr,
                           Word32         samplingRate);


/* aac decoder */
Word16 CAacDecoder_DecodeFrame(AACDECODER aacDecoderInstance,
                               Word16    *frameSize,
                               Word32    *sampleRate,
                               Word8     *channelMode,
                               Word16    *numChannels,
                               Word16    *timeData,
                               Flag       frameOK
);

#endif /* #ifndef AACDECODER_H */
