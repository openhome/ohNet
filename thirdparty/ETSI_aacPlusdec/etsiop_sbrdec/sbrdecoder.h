/*
   SBR library interface
*/

#ifndef __SBRDECODER_H
#define __SBRDECODER_H

#include "typedef.h"

#define SBR_EXTENSION          13  /* 1101 */
#define SBR_EXTENSION_CRC      14  /* 1110 */

#define MAXNRELEMENTS           2
#define MAXNRSBRCHANNELS        2
#define MAXSBRBYTES           269

#define SBRDEC_OK               0

typedef enum
{
  SBR_ID_SCE = 0,
  SBR_ID_CPE,
  SBR_ID_CCE,
  SBR_ID_LCS,
  SBR_ID_LFE,
  SBR_ID_DSE,
  SBR_ID_PCE,
  SBR_ID_FIL,
  SBR_ID_END
}
SBR_ELEMENT_ID;

typedef struct
{
  Word16  elementID;     /*!< ID_SCE (mono) or ID_CPE (stereo) */
  Word16  extensionType; /*!< e.g. SBR_EXTENSION or SBR_EXTENSION_MPEG */
  Word16  sizePayload;   /*!< length of data */
  Word8  *pData;         /*!< Pointer to actual data */
}
SBR_ELEMENT_STREAM;

typedef struct
{
  Word16 nrElements;                            /*!< Number of valid SBR streams */
  SBR_ELEMENT_STREAM sbrElement[MAXNRELEMENTS];
}
SBRBITSTREAM;


typedef struct SBR_DECODER_INSTANCE *SBRDECODER;


SBRDECODER openSBR (Word32 sampleRate, Word16 samplesPerFrame, Flag bDownSample, Flag bApplyQmfLp) ;

Word16 applySBR (SBRDECODER    self,
                 SBRBITSTREAM *Bitstr,
                 Word16       *TimeData,
                 Word16        *numChannels,
                 Flag         frameOK,
                 Flag         bDownSample,
                 Flag         bBitstreamDownMix);
#endif
