/*
   long/short decoding
 */

#ifndef BLOCK_H
#define BLOCK_H
#include "channelinfo.h"
#include "FFR_bitbuffer.h"
#include "defines.h"


Word32 CBlock_EvalPow43(Word32 a);
Word32 CBlock_Quantize(Word32 value, Word16 scfMod, Word16 scale);
  
Word16 CBlock_GetEscape(HANDLE_BIT_BUF bs, const Word16 q);
Word16 CBlock_GetQuantExponent(Word32 value, Word16 scfMod);
Word16 CBlock_UnpackIndex(Word16 idx, Word16 *qp, const CodeBookDescription *hcb);
Word16 CBlock_DecodeHuffmanWord(HANDLE_BIT_BUF bs, const Word16 (*CodeBook) [HuffmanEntries]);

void CShortBlock_Init(CAacDecoderChannelInfo *pAacDecoderChannelInfo);

Word16 CLongBlock_Read (HANDLE_BIT_BUF bs, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16 global_gain);
Word16 CShortBlock_Read(HANDLE_BIT_BUF bs, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16 global_gain);

void CLongBlock_ReadScaleFactorData(HANDLE_BIT_BUF bs, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16 global_gain);
Word16 CLongBlock_ReadSectionData(HANDLE_BIT_BUF bs,CAacDecoderChannelInfo *pAacDecoderChannelInfo);
Word16 CLongBlock_ReadSpectralData(HANDLE_BIT_BUF bs,CAacDecoderChannelInfo *pAacDecoderChannelInfo);

void CShortBlock_ReadScaleFactorData(HANDLE_BIT_BUF bs, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16 global_gain);
Word16 CShortBlock_ReadSectionData(HANDLE_BIT_BUF bs,CAacDecoderChannelInfo *pAacDecoderChannelInfo);
Word16 CShortBlock_ReadSpectralData(HANDLE_BIT_BUF bs,CAacDecoderChannelInfo *pAacDecoderChannelInfo);

void CLongBlock_ScaleSpectralData(CAacDecoderChannelInfo *pAacDecoderChannelInfo);
void CShortBlock_ScaleSpectralData(CAacDecoderChannelInfo *pAacDecoderChannelInfo);

void CLongBlock_FrequencyToTime (CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16[], const Word16);
void CShortBlock_FrequencyToTime(CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo, CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16[], const Word16);

void Lap1(Word32 *coef, Word16 *prev, Word16 *out, const Word16 *window, Word16 cuScale, Word16 size, Word16 stride);
void Lap2(Word32 *coef, Word32 *prev, Word16 *out, const Word16 *window, Word16 cuScale, Word16 size, Word16 stride);

void CPns_InitInterChannelData(CAacDecoderChannelInfo *pAacDecoderChannelInfo);

void CPns_InitPns(CAacDecoderChannelInfo *pAacDecoderChannelInfo);

Word16 CPns_IsPnsUsed (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                       const Word16 group,
                       const Word16 band);

Word16 CPns_IsPnsUsed (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                       const Word16 group,
                       const Word16 band);

void CPns_SetCorrelation(CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                         const Word16 group,
                         const Word16 band);

Word16 CPns_IsCorrelated(CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                         const Word16 group,
                         const Word16 band);

void CPns_Read (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                HANDLE_BIT_BUF bs,
                const CodeBookDescription *hcb,
                Word16 global_gain,
                Word16 band,
                Word16 group);

void CPns_Apply (CAacDecoderChannelInfo *pAacDecoderChannelInfo[],
                 Word16 channel);


#endif /* #ifndef BLOCK_H */
