/*
   decoding of long blocks
 */

#include <stdlib.h>
#include "aac_rom.h"
#include "imdct.h"
#include "FFR_bitbuffer.h"
#include "intrinsics.h"
#include "block.h"
#include "count.h"
#include "pulsedata.h"
#include "pns.h"



Word16 CLongBlock_ReadSectionData(HANDLE_BIT_BUF bs,
                                  CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 top;
  Word16 band;
  Word8 sect_cb;
  Word16 sect_len;
  Word16 sect_len_incr;
  Word16 sect_esc_val;
  Word8 *pCodeBook = pAacDecoderChannelInfo->pCodeBook;
  Word16 ErrorStatus;
  Word16 sfbTransmitted = GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo);

  move16(); move16(); 
  ErrorStatus = AAC_DEC_OK;                                                 move16();
  sect_esc_val = (1 << 5) - 1;                                              move16();

  band=0; move16();
  test(); sub(band, sfbTransmitted);
  while ( band < sfbTransmitted)
  {
    test(); sub(band, sfbTransmitted);
    sect_len = 0;                                                           move16();

    sect_cb = (Word8) ReadBits(bs,4);
    sect_len_incr = (Word16)ReadBits(bs,5);
    test(); sub(sect_len_incr, sect_esc_val);
    while (sect_len_incr == sect_esc_val)
    {
      test(); sub(sect_len_incr, sect_esc_val);
      sect_len = add(sect_len, sect_esc_val);
      sect_len_incr = (Word16)ReadBits(bs,5);
    }

    sect_len = add(sect_len, sect_len_incr);

    top = add(band, sect_len);

    test(); sub(top, sfbTransmitted);
    if (top > sfbTransmitted) {
      return AAC_DEC_DECODE_FRAME_ERROR;
    }
    add(band, top); /* save the value of band and execute the loop */
    for (; band < top; band++)
    {
      pCodeBook[band] = sect_cb;                                            move16(); logic16(); logic16(); logic16();

      test(); logic16();
      if ((pCodeBook[band] == BOOKSCL))
      {
        return AAC_DEC_INVALID_CODE_BOOK;
      }
    }
  }

  move16(); /*GetScaleFactorBandsTotal*/
  for (; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    pCodeBook[band] = ZERO_HCB;                                             move16();logic16();logic16();
  }
  return ErrorStatus;
}

void CLongBlock_ReadScaleFactorData(HANDLE_BIT_BUF bs,
                                    CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                                    Word16 global_gain)
{
  Word16 temp;
  Word8 band;
  Word16 position;
  Word16 factor;
  Word8 *pCodeBook;
  Word16 *pScaleFactor;
  const CodeBookDescription *hcb = &HuffmanCodeBooks[BOOKSCL];

  position = 0;                                                             move16();
  factor   = global_gain;                                                   move16();
  pCodeBook    = pAacDecoderChannelInfo->pCodeBook;                         move16();
  pScaleFactor = pAacDecoderChannelInfo->pScaleFactor;                      move16();

  move16(); /*GetScaleFactorBandsTransmitted*/
  for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    switch (pCodeBook[band])
    {
      case ZERO_HCB: /* zero book */
                                                                            test();
        pScaleFactor[band] = 0;                                             move16();
        break;

      default: /* regular scale factor */
        test(); test(); test(); test(); 
        temp = CBlock_DecodeHuffmanWord(bs,hcb->CodeBook);
        factor = add(factor, sub(temp, 60)); /* MIDFAC 1.5 dB */
        pScaleFactor[band] = sub(factor, 100);                              move16();
        break;

      case INTENSITY_HCB: /* intensity steering */
      case INTENSITY_HCB2:
        test(); test(); test(); 
        temp = CBlock_DecodeHuffmanWord(bs,hcb->CodeBook);
        position = add(position, sub(temp, 60));
        pScaleFactor[band] = sub(position, 100);                            move16();
        break;

      case NOISE_HCB:
        test(); test(); test(); test(); 
        CPns_Read(pAacDecoderChannelInfo, bs, hcb, global_gain, (Word16)band, 0);
        break;

    }
  }
}


/*
  \brief  Shift spectral data to common scale
*/
void CLongBlock_ScaleSpectralData(CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 index;
  Word8  band;
  Word16 *pSfbScale;
  Word16 *pSpecScale;
  Word32 *pSpectralCoefficient;

  const Word16 *BandOffsets = GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo);
  move16();
  pSfbScale            = pAacDecoderChannelInfo->pSfbScale;                 move16();
  pSpecScale           = pAacDecoderChannelInfo->pSpecScale;                move16();
  pSpectralCoefficient = pAacDecoderChannelInfo->pSpectralCoefficient;      move16();

  /* rescale to global scale */
  index=0; move16(); 
  move16(); /*GetScaleFactorBandsTotal*/
  for (index=0, band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    Word16 shf = sub(pSpecScale[0], pSfbScale[band]);
    pSfbScale[band] = pSpecScale[0];                                        move16();
    move16(); /*BandOffsets[band+1]*/
    for (index=BandOffsets[band]; index < BandOffsets[band+1]; index++)
    {
      pSpectralCoefficient[index] = L_shr(pSpectralCoefficient[index],shf); move32();

    }
  }
}

Word16 CLongBlock_ReadSpectralData(HANDLE_BIT_BUF bs,
                                   CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 i, index, step;
  Word8  band;
  Word16 scfExp, scfMod, specExp, locMax;
  Word16 QuantizedCoef[MaximumBinsLong];
  Word8 *pCodeBook;
  Word16 *pSfbScale;
  Word16 *pSpecScale;
  Word16 *pScaleFactor;
  Word32 *pSpectralCoefficient;
  const Word16 *BandOffsets = GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo);
  move16();

  pCodeBook            = pAacDecoderChannelInfo->pCodeBook;                 move16();
  pSfbScale            = pAacDecoderChannelInfo->pSfbScale;                 move16();
  pSpecScale           = pAacDecoderChannelInfo->pSpecScale;                move16();
  pScaleFactor         = pAacDecoderChannelInfo->pScaleFactor;              move16();
  pSpectralCoefficient = pAacDecoderChannelInfo->pSpectralCoefficient;      move16();

  pSpecScale[0] = 0;                                                        move16();

  for (index=0; index < MaximumBinsLong; index++)
  {
    QuantizedCoef[index] = 0;                                               move16();
  }

  move16(); /*GetScaleFactorBandsTotal*/
  for (band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++) {
    pSfbScale[band] = 0;                                                    move16();
  }

  move16(); /*GetScaleFactorBandsTransmitted*/
  for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    const CodeBookDescription *hcb;

    test(); test(); test(); test(); sub(0,0); sub(0,0); sub(0,0); sub(0,0); 
    if ((pCodeBook[band] == ZERO_HCB) || (pCodeBook[band] == INTENSITY_HCB) || (pCodeBook[band] == INTENSITY_HCB2) || (pCodeBook[band] == NOISE_HCB))
      continue;

    logic16(); logic16(); /* for the Word8 -> (int) cast */
    hcb = &HuffmanCodeBooks[(int) pCodeBook[band]] ;

    step = 0;                                                               move16();

    move16();  /*BandOffsets[band+1]*/
    for (index=BandOffsets[band]; index < BandOffsets[band+1]; index += step)
    {
      step = CBlock_UnpackIndex(CBlock_DecodeHuffmanWord(bs,hcb->CodeBook),&QuantizedCoef[index],hcb);

                                                                            test();
      if (hcb->Offset == 0)
      {
        for (i=0; i < step; i++)
        {
                                                                            test();
          if (QuantizedCoef[index+i])
          {
                                                                            test();
            if (ReadBits(bs,1)) /* sign bit */
            {
              QuantizedCoef[index+i] = negate(QuantizedCoef[index+i]);      move16();
            }
          }
        }
      }

      test(); logic16();
      if (pCodeBook[band] == ESCBOOK)
      {
        QuantizedCoef[index] = CBlock_GetEscape(bs,QuantizedCoef[index]);   move16(); move16();
        QuantizedCoef[index+1] = CBlock_GetEscape(bs,QuantizedCoef[index+1]);

        sub(0,0); sub(0,0); test(); test(); 
        if (abs_s(QuantizedCoef[index]) > MAX_QUANTIZED_VALUE || abs_s(QuantizedCoef[index+1]) > MAX_QUANTIZED_VALUE) {
          return AAC_DEC_DECODE_FRAME_ERROR;
        }
      }
    }
  }
  /* apply pulse data */
  CPulseData_Apply(&pAacDecoderChannelInfo->PulseData,
                   GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo),
                   QuantizedCoef);
  move16(); /*GetScaleFactorBandsTransmitted*/
  for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    sub(0,0); sub(0,0); sub(0,0); 
    test(); test(); test(); logic16(); logic16(); 
    if ((pCodeBook[band] == ZERO_HCB) || (pCodeBook[band] == INTENSITY_HCB) || (pCodeBook[band] == INTENSITY_HCB2))
      continue;

    /* scalefactor exponents and scalefactor manissa for current band */
    scfExp = shr(pScaleFactor[band], 2);
    scfMod = pScaleFactor[band] & 3;                                        logic16();
    locMax = 0;                                                             move16();

    move16(); /*BandOffsets[band+1]*/
    for (index=BandOffsets[band]; index < BandOffsets[band+1]; index ++)
    {
                                                                            test();
      if (abs(QuantizedCoef[index]) > locMax)
        locMax = abs(QuantizedCoef[index]);
    }

    specExp = CBlock_GetQuantExponent(locMax,scfMod);
    pSfbScale[band] = add(scfExp, specExp);                                 move16();
  }

  index=0; move16();
  move16(); /*GetScaleFactorBandsTransmitted*/
  for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
  {
    /* scalefactor exponents and scalefactor mantissa for current band */
    scfExp = shr(pScaleFactor[band], 2);
    scfMod = pScaleFactor[band] & 3;                                        logic16();

    move16(); /*BandOffsets[band+1]*/
    for (index=BandOffsets[band]; index < BandOffsets[band+1]; index++)
    {
      move32(); sub(scfExp,pSfbScale[band]);
      pSpectralCoefficient[index] = CBlock_Quantize(QuantizedCoef[index],scfMod,scfExp-pSfbScale[band]);
    }
  }

  /* zero out spectral data beyond max_sfb; index is now first bin of max_sfb+1 */
  for ( ; index < MaximumBinsLong; index++)
  {
    pSpectralCoefficient[index] = (Word32) 0;                               move32();
  }

  return AAC_DEC_OK;
}

static void 
NoLap1(Word32 *coef,
       Word16 *out,
       Word16 cuScale,
       Word16 stride)
{
  int i;

  for (i=0; i<Size07; i++) {
    out[stride*i] = etsiopround(L_shl(L_negate(coef[Size07-1-i]),cuScale)); move16();
  }
}


static void 
NoLap2(Word32 *coef,
       Word16 *out,
       Word16 cuScale,
       Word16 stride)
{
  int i;
  Word32 accu;

  for(i=0; i<Size07; i++) {
    accu = L_shl(L_negate(coef[Size07-1-i]) , cuScale);
    out[stride*i] = etsiopround(L_shl(accu, 1));                            move16();
  }
}


static void 
StartLap(Word32 *coef,
         Word16 *out,
         Word16 cuScale,
         Word16 stride)
{
  int i;

  for (i=0; i<Size01; i++) {
    out[stride*i] = etsiopround(L_shl(coef[i],cuScale));                    move16();
  }
}

static void 
StopLap(Word32 *coef,
        Word16 *prev,
        Word16 *out,
        const Word16 *window,
        Word16 cuScale,
        Word16 stride)
{
  int i;
  Word32 accu;
  for (i=0; i<Size01; i++)
  {
    accu = L_sub(L_shl(fixmul_32x16b(coef[Size15+i],                  window[i]),            cuScale),
                 L_mult(prev[Size08-1-i], window[Size01*2-1-i]));
    out[stride*(Size07+i)] = etsiopround(L_shl(accu,1));                    move16();
  }

  for (i=0; i<Size01; i++)
  {
    accu = L_sub(L_shl(fixmul_32x16b(L_negate(coef[Size08*2-1-i]),  window[Size01+i]),     cuScale),
                 L_mult(prev[Size07+i], window[Size01-1-i]));
    out[stride*(Size08+i)] = etsiopround(L_shl(accu,1));                    move16();
  }

}

static void 
ShortLongLapIllegal(Word32 *coef,
                    Word16 *prev,
                    Word16 *out,
                    const Word16 *window_long,
                    const Word16 *window_short,
                    Word16 cuScale,
                    Word16 stride)
{
  int i;
  Word32 accu;
  /* 0,...,Size07-1 */
  for (i=0; i<Size07; i++) {
    accu = L_add(L_shl(fixmul_32x16b(coef[Size08+i],window_long[i]) , cuScale),
                 L_deposit_h(prev[i]));
    out[stride*i] = etsiopround(L_shl(accu, 1));                            move16();
  }

  /* Size07,...,Size08-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(coef[Size15+i],   window_long[Size07+i]),    cuScale),
                 L_mult(prev[Size08-1-i], window_short[Size02-1-i]));
    out[stride*(i+Size07)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size08,...,Size09-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(L_negate(coef[Size16-1-i]), window_long[Size08+i]),    cuScale),
                 L_mult(prev[Size07+i], window_short[Size01-1-i]));
    out[stride*(i+Size08)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size09,...,Size16-1 */
  for (i=0; i<Size07; i++) {
    accu = L_shl(fixmul_32x16b(L_negate(coef[Size15-1-i]), window_long[Size09+i]), cuScale);
    out[stride*(i+Size09)] = etsiopround(L_shl(accu, 1));                   move16();
  }

}

static void 
LongShortLapIllegal(Word32 *coef,
                    Word16 *prev,
                    Word16 *out,
                    const Word16 *window_long,
                    const Word16 *window_short,
                    Word16 cuScale,
                    Word16 stride)
{
  int i;
  Word32 accu;
   /* 0,...,Size07-1 */
  for (i=0; i<Size07; i++) {
    accu = L_mult(prev[Size08-1-i], negate(window_long[Size16-1-i]));
    out[stride*i] = etsiopround(L_shl(accu, 1));                            move16();
  }

  /* Size07,...,Size08-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(coef[Size15+i],   window_short[i]),         cuScale),
                 L_mult(prev[Size01-1-i], window_long[Size09-1-i]));
    out[stride*(Size07+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size08,...,Size09-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(L_negate(coef[Size16-1-i]), window_short[Size01+i]),  cuScale),
                 L_mult(prev[i], window_long[Size08-1-i]));
    out[stride*(Size08+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size09-Size16-1 */
  for (i=0; i<Size07; i++) {
    accu = L_sub(L_shl(L_negate(coef[Size15-1-i]), cuScale),
                 L_mult(prev[i+Size01], window_long[Size07-1-i]));
    out[stride*(Size09+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

}

void CLongBlock_FrequencyToTime(CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo,
                                CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                                Word16 outSamples[],
                                const Word16 stride)
{
  Word16 i, cuScale, imdctScale;
  COverlapAddData *pOverlapAddData;
  Word32   *pSpectralCoefficient;
  Word16   *pSpecScale;
  const Word16 *pLongWindow;
  const Word16 *pShortWindow;

  pOverlapAddData = &pAacDecoderStaticChannelInfo->OverlapAddData;          move16();

  pLongWindow  = pAacDecoderStaticChannelInfo->pLongWindow[(int) pOverlapAddData->WindowShape];
  pShortWindow = pAacDecoderStaticChannelInfo->pShortWindow[(int) pOverlapAddData->WindowShape];
  move16(); move16();
  pSpectralCoefficient = pAacDecoderChannelInfo->pSpectralCoefficient;      move16();
  pSpecScale = pAacDecoderChannelInfo->pSpecScale;                          move16();

  /* Inverse IMDCT */
  CLongBlock_InverseTransform(pSpectralCoefficient,&imdctScale);

  /*
    Compensate additional scaling by the factor 0.5 in overlap&add if the
    accumulator does not provide overflow bits.
  */
  cuScale = add(add(pSpecScale[0], imdctScale), -1-16-9);

  /* Overlap&Add */
  switch(GetWindowSequence(&pAacDecoderChannelInfo->IcsInfo))
  {
    case OnlyLongSequence:
                                                                            test();
      switch(pOverlapAddData->WindowSequence)
      {
        case OnlyLongSequence:
        case LongStopSequence:
          test(); test();
          Lap1(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples,pLongWindow,cuScale,Size08,stride);
        break;
        case LongStartSequence:
        case EightShortSequence:
          test(); test(); test(); test();
          ShortLongLapIllegal(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples,pLongWindow,pShortWindow,cuScale,stride);
        break;
      }
      for (i=0; i<Size08; i++) {
        pOverlapAddData->pOverlapBuffer[i] = etsiopround(L_shl(pSpectralCoefficient[i],cuScale));       move16();
      }
    break;

    case LongStartSequence:
      test(); test();
      switch(pOverlapAddData->WindowSequence)
      {
        case OnlyLongSequence:
        case LongStopSequence:
          test(); test();
          Lap1(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples,pLongWindow,cuScale,Size08,stride);
        break;
        case LongStartSequence:
        case EightShortSequence:
          test(); test(); test(); test();
          ShortLongLapIllegal(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples,pLongWindow,pShortWindow,cuScale,stride);
        break;
      }
      NoLap1(&pSpectralCoefficient[Size01],pOverlapAddData->pOverlapBuffer,cuScale,1);
      StartLap(pSpectralCoefficient,&(pOverlapAddData->pOverlapBuffer[Size07]),cuScale,1);
    break;

    case LongStopSequence:
      test(); test(); test(); 
      switch(pOverlapAddData->WindowSequence)
      {
        case EightShortSequence:
        case LongStartSequence:
          test(); test(); 
          for (i=0; i<Size07; i++) {
            outSamples[stride*i] = shl(pOverlapAddData->pOverlapBuffer[i], 1);             move16();
          }
          StopLap(pSpectralCoefficient, pOverlapAddData->pOverlapBuffer,outSamples,pShortWindow,cuScale,stride);
          NoLap2(&pSpectralCoefficient[Size08],&outSamples[stride*Size09],cuScale,stride);
        break;
        case OnlyLongSequence:
        case LongStopSequence:
          test(); test(); test(); test();
          LongShortLapIllegal(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples,pLongWindow,pShortWindow,cuScale,stride);
        break;
      }
      for (i=0; i<Size08; i++) {
        pOverlapAddData->pOverlapBuffer[i] = etsiopround(L_shl(pSpectralCoefficient[i], cuScale));   move16();
      }
    break;
  }
  
  /* logic16() is used for representing the complexity associated 
     with data located on 8-bit boundary */
  pOverlapAddData->WindowShape = GetWindowShape(&pAacDecoderChannelInfo->IcsInfo);
  pOverlapAddData->WindowSequence = GetWindowSequence(&pAacDecoderChannelInfo->IcsInfo);
}




