/*
   decoding of short blocks
 */

#include <stdlib.h>
#include "aac_rom.h"
#include "imdct.h"
#include "FFR_bitbuffer.h"
#include "intrinsics.h"
#include "block.h"
#include "count.h"
#include "pns.h"



void CShortBlock_Init(CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  int group,band;
  Word8 *pCodeBook;
  Word16 *pScaleFactor;

  pCodeBook    = pAacDecoderChannelInfo->pCodeBook;                         move16();
  pScaleFactor = pAacDecoderChannelInfo->pScaleFactor;                      move16();

  for (group=0; group<MaximumGroups; group++)
  {
    for (band=0; band<MaximumScaleFactorBandsShort; band++)
    {
      pCodeBook[group*MaximumScaleFactorBandsShort+band] = 0;               move16();
      pScaleFactor[group*MaximumScaleFactorBandsShort+band] = 0;            move16();
    }
  }
}

Word16 CShortBlock_ReadSectionData(HANDLE_BIT_BUF bs,
                                   CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 top;
  Word16 band;
  Word16 group;
  Word8 sect_cb;
  Word16 sect_len;
  Word16 sect_len_incr;
  Word16 sect_esc_val;
  Word8 *pCodeBook = pAacDecoderChannelInfo->pCodeBook;
  Word16 ErrorStatus = AAC_DEC_OK;
  Word16 sfbTransmitted = GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo);
                                                                            move16(); move16(); move16();

  sect_esc_val = (1 << 3) - 1 ;                                             move16();
  move16(); /*GetWindowGroups*/
  for (group=0; group<GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++)
  {
    band=0; move16(); test(); sub(band, sfbTransmitted);
    while (band<sfbTransmitted)
    {
      test(); sub(band, sfbTransmitted);
      sect_len = 0 ;                                                        move16();

      sect_cb = (Word8) ReadBits(bs,4) ;
      sect_len_incr = (Word16)ReadBits(bs,3);

      sub(sect_len_incr, sect_esc_val); test(); 
      while (sect_len_incr == sect_esc_val)
      {
        sub(sect_len_incr, sect_esc_val);                                   test();
        sect_len = add(sect_len, sect_esc_val);
        sect_len_incr = (Word16)ReadBits(bs,3);
      }

      sect_len = add(sect_len, sect_len_incr);

      top = add(band, sect_len);
      test(); sub(top, sfbTransmitted);
      if (top > sfbTransmitted) {
        return (AAC_DEC_DECODE_FRAME_ERROR);
      }
      add(band, top); /* save the value of band and execute the loop */
      for (; band < top; band++)
      {
        pCodeBook[group*MaximumScaleFactorBandsShort+band] = sect_cb;       move16(); logic16(); logic16(); logic16();

        test(); logic16();
        if ((pCodeBook[group*MaximumScaleFactorBandsShort+band] == BOOKSCL))
        {
          return AAC_DEC_INVALID_CODE_BOOK;
        }
      }
    }
    move16(); /*GetScaleFactorBandsTotal*/
    for ( ; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++)
    {
      pCodeBook[group*MaximumScaleFactorBandsShort+band] = ZERO_HCB;        move16();logic16();logic16();
    }
  }
  return ErrorStatus;
}

void CShortBlock_ReadScaleFactorData(HANDLE_BIT_BUF bs,
                                     CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                                     Word16 global_gain)
{
  Word16 temp;
  Word8 band;
  Word16 group;
  Word16 position;
  Word16 factor;
  Word8 *pCodeBook;
  Word16 *pScaleFactor;
  const CodeBookDescription *hcb = &HuffmanCodeBooks[BOOKSCL];

  position = 0;                                                             move16();
  factor   = global_gain;                                                   move16();
  pCodeBook    = pAacDecoderChannelInfo->pCodeBook;                         move16();
  pScaleFactor = pAacDecoderChannelInfo->pScaleFactor;                      move16();

  move16(); /*GetWindowGroups*/ 
  move16(); /*GetScaleFactorBandsTransmitted*/
  for (group=0; group < GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++)
  {
    for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
    {
      logic16(); logic16(); 
      switch (pCodeBook[group*MaximumScaleFactorBandsShort+band])
      {
        case ZERO_HCB: /* zero book */
                                                                            test();
          pScaleFactor[group*MaximumScaleFactorBandsShort+band] = 0;        move16();
          break;

        default: /* decode scale factor */
          test(); test(); test(); test();
          temp = CBlock_DecodeHuffmanWord(bs,hcb->CodeBook);
          factor = add(factor, sub(temp, 60)); /* MIDFAC 1.5 dB */
                                                                            move16();
          pScaleFactor[group*MaximumScaleFactorBandsShort+band] = sub(factor, 100);
          break;

        case INTENSITY_HCB: /* intensity steering */
        case INTENSITY_HCB2:
          test(); test(); test();
          temp = CBlock_DecodeHuffmanWord(bs,hcb->CodeBook);
          position = add(position, sub(temp, 60));
                                                                            move16();
          pScaleFactor[group*MaximumScaleFactorBandsShort+band] = sub(position, 100);
          break;

        case NOISE_HCB: /* PNS */
          test(); test(); test(); test();
          CPns_Read(pAacDecoderChannelInfo, bs, hcb, global_gain, band, group);
          break;
      }
    }
  }
}


/*
  \brief  Shift spectral data to common scale
*/
void CShortBlock_ScaleSpectralData(CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 index;
  Word8 band;
  Word16 window, groupwin, group;
  Word16 *pSfbScale;
  Word16 *pSpecScale;
  const Word16 *BandOffsets = GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo);
  Word32 *pSpectralCoefficient;
  move16();
  pSfbScale            = pAacDecoderChannelInfo->pSfbScale;                 move16();
  pSpecScale           = pAacDecoderChannelInfo->pSpecScale;                move16();
  pSpectralCoefficient = pAacDecoderChannelInfo->pSpectralCoefficient;      move16();


  /* rescale to global scale */
  window=0; move16(); 
  move16(); /*GetWindowGroups*/ move16(); /*GetScaleFactorBandsTotal*/
  for (group=0; group < GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++)
  {
    move16(); /* GetWindowGroupLength */
    for (groupwin=0; groupwin < GetWindowGroupLength(&pAacDecoderChannelInfo->IcsInfo,group); groupwin++, window++)
    {
      for (band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++)
      {
        Word16 shf = sub(pSpecScale[window], pSfbScale[window*MaximumScaleFactorBandsShort+band]);
                                                                            move16();
        pSfbScale[window*MaximumScaleFactorBandsShort+band] = pSpecScale[window];
        move16(); /* BandOffsets[band+1] */
        for (index=BandOffsets[band]; index<BandOffsets[band+1]; index++)
        {
                                                                            move32();
          pSpectralCoefficient[window*MaximumBinsShort+index] = L_shr(pSpectralCoefficient[window*MaximumBinsShort+index],shf);

        }
      }
    }
  }
}

Word16 CShortBlock_ReadSpectralData(HANDLE_BIT_BUF bs,
                                    CAacDecoderChannelInfo *pAacDecoderChannelInfo)
{
  Word16 i,index,step;
  Word8 band;
  Word16 window, group, groupwin, groupoffset;
  Word16 scfExp, scfMod, specExp, locMax;
  Word16 QuantizedCoef[MaximumWindows][MaximumBinsShort];
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

  for (window=0; window < MaximumWindows; window++)
  {
    pSpecScale[window] = 0;                                                 move16();
    move16(); /*GetScaleFactorBandsTotal*/
    for (band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++) {
      pSfbScale[window*MaximumScaleFactorBandsShort+band] = 0;              move16();
    }

    for (index=0; index < MaximumBinsShort; index++) {
      QuantizedCoef[window][index] = 0;                                     move16();
    }
  }

  groupoffset = 0;                                                          move16();
  move16(); /*GetWindowGroups*/; move16() /*GetScaleFactorBandsTransmitted*/; 
  for (group=0; group < GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++)
  {
    move16(); /*GetWindowGroupLength*/
    for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
    {
      const CodeBookDescription *hcb;

      logic16(); logic16(); /* for the Word8 -> (int) cast */
      hcb = &HuffmanCodeBooks[(int) pCodeBook[group*MaximumScaleFactorBandsShort+band]];

      scfExp = shr(pScaleFactor[group*MaximumScaleFactorBandsShort+band], 2);
      scfMod = pScaleFactor[group*MaximumScaleFactorBandsShort+band] & 3;   logic16();
      for (groupwin=0; groupwin < GetWindowGroupLength(&pAacDecoderChannelInfo->IcsInfo,group); groupwin++)
      {
        window = add(groupoffset, groupwin);

        sub(0,0); sub(0,0); sub(0,0); sub(0,0); 
        test(); test(); test(); test(); logic16(); logic16(); 
        if (  (pCodeBook[group*MaximumScaleFactorBandsShort+band] == ZERO_HCB)
            ||(pCodeBook[group*MaximumScaleFactorBandsShort+band] == INTENSITY_HCB)
            ||(pCodeBook[group*MaximumScaleFactorBandsShort+band] == INTENSITY_HCB2)
            ||(pCodeBook[group*MaximumScaleFactorBandsShort+band] == NOISE_HCB))
          continue;

        step = 0 ;                                                          move16();
        locMax=0 ;                                                          move16();
        move16(); /*BandOffsets[band+1]*/
        for (index=BandOffsets[band]; index < BandOffsets[band+1]; index+=step)
        {
          step = CBlock_UnpackIndex(CBlock_DecodeHuffmanWord(bs,hcb->CodeBook),&QuantizedCoef[window][index],hcb);

                                                                            test();
          if (hcb->Offset == 0)
          {
            for (i=0; i < step; i++)
            {
                                                                            test();
              if (QuantizedCoef[window][index+i])
              {
                                                                            test();
                if (ReadBits(bs,1)) /* sign bit */
                {
                                                                            move16();
                  QuantizedCoef [window][index+i] = negate(QuantizedCoef [window][index+i]);
                }
              }
            }
          }

          test(); logic16();
          if (pCodeBook[group*MaximumScaleFactorBandsShort+band] == ESCBOOK)
          {
                                                                            move16(); move16();
            QuantizedCoef[window][index] = CBlock_GetEscape(bs,QuantizedCoef[window][index]);
            QuantizedCoef[window][index+1] = CBlock_GetEscape(bs,QuantizedCoef[window][index+1]);

            sub(0,0); sub(0,0); test(); test();
            if (abs_s(QuantizedCoef[window][index]) > MAX_QUANTIZED_VALUE || abs_s(QuantizedCoef[window][index+1]) > MAX_QUANTIZED_VALUE) {
              return (AAC_DEC_DECODE_FRAME_ERROR);
            }

          }

          /* save abs of local maxima in this band */
          for (i=0; i < step; i++)
          {
                                                                            test();
            if (abs_s(QuantizedCoef[window][index+i]) > locMax)
              locMax = abs_s(QuantizedCoef[window][index+i]);
          }
        }

        /* save global scale maxima in this sfb */
        specExp = CBlock_GetQuantExponent(locMax,scfMod);
                                                                            move16();
        pSfbScale[window*MaximumScaleFactorBandsShort+band] = add(scfExp, specExp);
      }
    }
    groupoffset = add(groupoffset, GetWindowGroupLength(&pAacDecoderChannelInfo->IcsInfo,group));
  }
  window=0; move16();
  move16(); /*GetWindowGroups*/; move16(); /*GetScaleFactorBandsTransmitted*/
  for (group=0; group < GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++)
  {
    move16(); /*GetWindowGroupLength*/
    for (groupwin=0; groupwin < GetWindowGroupLength(&pAacDecoderChannelInfo->IcsInfo,group); groupwin++, window++)
    {
      index = 0;                                                            move16();

      /* quantize & apply scalefactors */
      for (band=0; band < GetScaleFactorBandsTransmitted(&pAacDecoderChannelInfo->IcsInfo); band++)
      {
        /* scalefactor exponents and scalefactor mantissa for current band */
        scfExp = shr(pScaleFactor[group*MaximumScaleFactorBandsShort+band], 2);
        scfMod = pScaleFactor[group*MaximumScaleFactorBandsShort+band] & 3; logic16();
        move16(); /*BandOffsets[band+1]*/
        for (index=BandOffsets[band]; index < BandOffsets[band+1] ;index++)
        {
          move32(); sub(scfExp,
                        pSfbScale[window*MaximumScaleFactorBandsShort+band]);
          pSpectralCoefficient[window*MaximumBinsShort+index] = CBlock_Quantize(QuantizedCoef[window][index],scfMod,scfExp-pSfbScale[window*MaximumScaleFactorBandsShort+band]);
        }
      }

      for (; index < MaximumBinsShort; index++) {
        pSpectralCoefficient[window*MaximumBinsShort+index] = 0L;   move32();
      }
    }
  }

  return AAC_DEC_OK;
}


static void 
LongShortLapIllegal(Word32 *current,
                    Word16 *prev,
                    Word16 *out,
                    const Word16 *shortWindow,
                    const Word16 *shortWindowPrev,
                    const Word16 *longWindowPrev,
                    Word16 cuScale,
                    Word16 stride)
{
  int i;
  Word32 accu;
  /* 0,...,Size07-1 */
  for (i=0; i<Size07; i++) {
    accu = L_mult(prev[Size08-1-i], negate(longWindowPrev[Size16-1-i]));
    out[stride*i] = etsiopround(L_shl(accu, 1));                            move16();
  }

  /* Size07,...,Size08-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(current[Size01+i], shortWindowPrev[i]), cuScale),
                 L_mult(prev[Size01-1-i],  longWindowPrev[Size09-1-i]));
    out[stride*(Size07+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size08,...,Size09-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(L_negate(current[Size02-1-i]), shortWindowPrev[Size01+i]),  cuScale),
                 L_mult(prev[i], longWindowPrev[Size08-1-i]));
    out[stride*(Size08+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size09,...,Size10-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(current[Size03+i],   shortWindow[i]),             cuScale),
                       L_shl(fixmul_32x16b(current[Size01-1-i], shortWindow[Size02-1-i]),    cuScale)),
                 L_mult(prev[i+Size01], longWindowPrev[Size07-1-i]));
    out[stride*(Size09+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size10,...,Size11-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(L_negate(current[Size04-1-i]), shortWindow[Size01+i]),      cuScale),
                       L_shl(fixmul_32x16b(current[i],                    shortWindow[Size01-1-i]),    cuScale)),
                 L_mult(prev[i+Size02], longWindowPrev[Size06-1-i]));
    out[stride*(Size10+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size11,...,Size12-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(current[Size05+i],   shortWindow[i]),             cuScale),
                       L_shl(fixmul_32x16b(current[Size03-1-i], shortWindow[Size02-1-i]),    cuScale)),
                 L_mult(prev[i+Size03], longWindowPrev[Size05-1-i]));
    out[stride*(Size11+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size12,...,Size13-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(L_negate(current[Size06-1-i]), shortWindow[Size01+i]),      cuScale),
                       L_shl(fixmul_32x16b(current[Size02+i],             shortWindow[Size01-1-i]),    cuScale)),
                 L_mult(prev[i+Size04], longWindowPrev[Size04-1-i]));
    out[stride*(Size12+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size13,...,Size14-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(current[Size07+i],   shortWindow[i]),             cuScale),
                       L_shl(fixmul_32x16b(current[Size05-1-i], shortWindow[Size02-1-i]),    cuScale)),
                 L_mult(prev[i+Size05], longWindowPrev[Size03-1-i]));
    out[stride*(Size13+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size14,...,Size15-1 */
  for(i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(L_negate(current[Size08-1-i]), shortWindow[Size01+i]),      cuScale),
                       L_shl(fixmul_32x16b(current[Size04+i],             shortWindow[Size01-1-i]),    cuScale)),
                 L_mult(prev[i+Size06], longWindowPrev[Size02-1-i]));
    out[stride*(Size14+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }

  /* Size15,...,Size16-1 */
  for (i=0; i<Size01; i++) {
    accu = L_sub(L_sub(L_shl(fixmul_32x16b(current[Size09+i],   shortWindow[i]),             cuScale),
                       L_shl(fixmul_32x16b(current[Size07-1-i], shortWindow[Size02-1-i]),    cuScale)),
                 L_mult(prev[i+Size07], longWindowPrev[Size01-1-i]));
    out[stride*(Size15+i)] = etsiopround(L_shl(accu, 1));                   move16();
  }


  for (i=0; i<Size01; i++) {
    accu = L_sub(fixmul_32x16b(L_negate(current[Size10-1-i]), shortWindow[Size01+i]),
                 fixmul_32x16b(current[Size06+i],             shortWindow[Size01-1-i]));
    prev[i] = etsiopround(L_shl(accu, cuScale));                            move16();
  }

}
void CShortBlock_FrequencyToTime(CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo,
                                 CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                                 Word16 outSamples[],
                                 const Word16 stride)
{
  Word16 i, j, cuScale, scale, maxScale, imdctScale[8];
  COverlapAddData *pOverlapAddData;
  Word32 *pSpectralCoefficient;
  Word16 *pSpecScale;
  const Word16 *shortWindow;
  const Word16 *shortWindowPrev;
  const Word16 *longWindowPrev;

  pOverlapAddData      = &pAacDecoderStaticChannelInfo->OverlapAddData;     move16();

  shortWindow     = pAacDecoderStaticChannelInfo->pShortWindow[(int) GetWindowShape(&pAacDecoderChannelInfo->IcsInfo)]; move16();
  shortWindowPrev = pAacDecoderStaticChannelInfo->pShortWindow[(int) pOverlapAddData->WindowShape]; move16();
  longWindowPrev  = pAacDecoderStaticChannelInfo->pLongWindow[(int) pOverlapAddData->WindowShape]; move16();
  pSpectralCoefficient = pAacDecoderChannelInfo->pSpectralCoefficient;      move16();
  pSpecScale           = pAacDecoderChannelInfo->pSpecScale;                move16();

  /* Inverse MDCT */
  for (i=0; i<MaximumWindows; i++) {
    CShortBlock_InverseTransform(&pSpectralCoefficient[i*Size02],&imdctScale[i]);
  }

  /* Calculate minumum scalefactor of all blocks */
  maxScale = add(pSpecScale[0], imdctScale[0]);

  for (i=1; i<MaximumWindows; i++) {
    Word16 tmp = add(pSpecScale[i], imdctScale[i]);
    maxScale = maxScale > tmp ? maxScale : tmp;                             test(); move16();
  }

  /* Apply minimum scalefactor to all blocks */
  for (i=0; i<MaximumWindows; i++)
  {
    scale = sub(sub(maxScale, pSpecScale[i]), imdctScale[i]);

    for (j=0; j<Size02; j++){
                                                                            move32();
      pSpectralCoefficient[i*Size02+j] = L_shr(pSpectralCoefficient[i*Size02+j],scale);
    }
  }

  /*
    Compensate additional scaling by the factor 0.5 in overlap&add if the
    accumulator does not provide overflow bits.
  */

  cuScale = add(maxScale, -16-6-1);


  /* Overlap & Add */
  switch(pOverlapAddData->WindowSequence)
  {
    Word16 overlapTmp[Size01];

    case EightShortSequence:
    case LongStartSequence:
      test(); test();
      for (i=0; i<Size07; i++){
        outSamples[stride*i] = shl(pOverlapAddData->pOverlapBuffer[i],1);   move16();
      }
      Lap1(&pSpectralCoefficient[0],&pOverlapAddData->pOverlapBuffer[Size07],
           &outSamples[stride*Size07],shortWindowPrev,cuScale,Size01,stride);

      for (i=0; i<Size01; i++){
        overlapTmp[i] = etsiopround(L_shl(pSpectralCoefficient[i],cuScale));  move16();
      }
      Lap1(&pSpectralCoefficient[Size02],overlapTmp,
           &outSamples[stride*Size09],shortWindow,cuScale,Size01,stride);

      for (i=0; i<Size01; i++){
        overlapTmp[i] = etsiopround(L_shl(pSpectralCoefficient[i+Size02],cuScale));  move16();
      }
      Lap1(&pSpectralCoefficient[Size04],overlapTmp,
           &outSamples[stride*Size11],shortWindow,cuScale,Size01,stride);

      for (i=0; i<Size01; i++){
        overlapTmp[i] = etsiopround(L_shl(pSpectralCoefficient[i+Size04],cuScale));  move16();
      }
      Lap1(&pSpectralCoefficient[Size06],overlapTmp,
           &outSamples[stride*Size13],shortWindow,cuScale,Size01,stride);

      Lap2(&pSpectralCoefficient[Size08],&pSpectralCoefficient[Size06],
           pOverlapAddData->pOverlapBuffer,shortWindow,cuScale,Size01,1);

      for (i=0; i<Size01; i++)
      {
        outSamples[stride*(Size15+i)] = shl(pOverlapAddData->pOverlapBuffer[i], 1);  move16();

                                                                            move16();
        pOverlapAddData->pOverlapBuffer[i] = pOverlapAddData->pOverlapBuffer[i+Size01];
      }
    break;

    case OnlyLongSequence:
    case LongStopSequence:
      test(); test(); test(); test();
      LongShortLapIllegal(pSpectralCoefficient,pOverlapAddData->pOverlapBuffer,outSamples, shortWindow,shortWindowPrev,longWindowPrev,cuScale,stride);
    break;
  }

  Lap2(&pSpectralCoefficient[Size10],&pSpectralCoefficient[Size08],
       &pOverlapAddData->pOverlapBuffer[Size01],shortWindow,cuScale,Size01,1);
  Lap2(&pSpectralCoefficient[Size12],&pSpectralCoefficient[Size10],
       &pOverlapAddData->pOverlapBuffer[Size03],shortWindow,cuScale,Size01,1);
  Lap2(&pSpectralCoefficient[Size14],&pSpectralCoefficient[Size12],
       &pOverlapAddData->pOverlapBuffer[Size05],shortWindow,cuScale,Size01,1);

  for (i=0; i<Size01; i++) {
                                                                            move16();
    pOverlapAddData->pOverlapBuffer[i+Size07] = etsiopround(L_shl(pSpectralCoefficient[Size14+i],cuScale));
  }

  pOverlapAddData->WindowShape = GetWindowShape(&pAacDecoderChannelInfo->IcsInfo);
  pOverlapAddData->WindowSequence = GetWindowSequence(&pAacDecoderChannelInfo->IcsInfo);
}
