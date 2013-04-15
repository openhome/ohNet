/*
   long/short decoding
 */

#include <assert.h>
#include "aac_rom.h"
#include "FFR_bitbuffer.h"
#include "intrinsics.h"
#include "block.h"
#include "basic_op.h"
#include "count.h"

#include "tns.h"


/*
  Compensate additional scaling by the factor 0.5 in overlap&add 
  accumulator does not provide overflow bits.
*/


Word32 CBlock_EvalPow43(Word32 a)
{
  Word16 x0;
  Word16 x0_stern;
  Word32 f_x;
  Word32 f_x0;
  Word32 f_strich_x0;
  Word32 delta;
 
  a        = L_shr(a, (INT_BITS - 2) - LD_MANT);
  x0       = a & (MANT_SIZE-1);                                             logic16();
  x0_stern = shr(x0, (LD_DELTA));

                                                                            logic16(); test();
  if (x0 & (DELTA_SIZE-1))
  {
    /* use linear approx */
    delta       = L_shl(L_deposit_l(x0 & (DELTA_SIZE-1)),
                        (INT_BITS - 1) - LD_DELTA);                         logic16();
    f_x0        = InverseQuantTable[x0_stern];                              move32();
    f_strich_x0 = L_sub(InverseQuantTable[x0_stern+1], 
                        InverseQuantTable[x0_stern]);
    f_x         = L_add(f_x0, fixmul(f_strich_x0, delta));
  }
  else
  {
    /* use exact table value */
    f_x         = InverseQuantTable[x0_stern];                              move32();
  }
  return(f_x);
}


Word16 CBlock_GetQuantExponent(Word32 value,
                               Word16 scfMod)
{
  Word16 specExp = -INT_BITS;                                               move16();
  
                                                                            test();
  if (value!= 0)
  {
    Word16 ex;
    Word32 s,t;
    Word32 u,v;

    v  = value;                                                             move32();
    ex = ffr_norm32(v);

    v  = L_shl(v, ex);
    specExp = sub((INT_BITS-1), ex);

    assert(specExp < 14);

    s = CBlock_EvalPow43(v);
    t = specExpMantTableComb[scfMod][specExp];                              move32();
    logic16(); logic16(); /* the table is 8-bit aligned */
    specExp = (Word16)specExpTableComb[scfMod][specExp];                    move16();
    u = fixmul(s,t);
    specExp = sub(specExp, ffr_norm32(u));        /* align mantissa left, reduce exponent */
  }  
  return specExp;
}

Word32 CBlock_Quantize(Word32 value,
                       Word16 scfMod,
                       Word16 scale)
{
  Word16 ex;
  Word16 shifter;
  Word16 specExp;
  Word16 sign;
  Word32 tmp;
  Word32 s,t,u;
  Word32 quantValue;

  sign       = 0;                                                           move16();
  quantValue = 0;                                                           move32();

  tmp = value;                                                              move32();
                                                                            test();
  if (value!= 0)
  {
//    Word16 sh, sl, th, tl;
                                                                            test();
    if (value < 0)
    {
      /* negate and save sign */
      tmp  = L_negate(tmp);
      sign = 1;                                                             move16();
    }

    /* "normalize" value */
    ex = ffr_norm32(tmp);

    tmp     = L_shl(tmp, ex);
    specExp = sub(INT_BITS-1, ex);

    assert(specExp < 14); /* this fails if abs(value) > 8191 */
    
    /* we have now a "mantissa" and an exponent part:
       abs(value) = accu*2^specExp, 0.5 <=accu < 1.0, 0 <= specExp < 14 */
    
    /* calculate "mantissa" ^4/3 */
    s = CBlock_EvalPow43(tmp);

    /* get appropriate exponent multiplier for specExp^3/4 combined with scfMod */
    t = specExpMantTableComb[scfMod][specExp];                              move32();

    /* multiply "mantissa" ^4/3 with exponent multiplier */
#if 0
    L_Extract(s, &sh, &sl);
    L_Extract(t, &th, &tl);
    u = Mpy_32(sh, sl, th, tl);
#else
    u = fixmul(s, t);
#endif
    /* get appropriate exponent shifter */
    logic16(); logic16(); /* the table is 8-bit aligned */
    specExp    = (Word16)specExpTableComb[scfMod][specExp];                 move16();
   
    /* shift to get final value: we have to shift left by specExp, and then shift right by scale */
    shifter    = sub(negate(scale), specExp);
    quantValue = L_shr(u,shifter);
    /* apply sign */
                                                                            test();
    if (sign)
      quantValue = L_negate(quantValue);

  }
  return(quantValue);
}

/*!
  \brief Read huffman codeword

  The function reads the huffman codeword from the bitstream and
  returns the index value.

  \return  index value
*/
Word16 CBlock_DecodeHuffmanWord(HANDLE_BIT_BUF bs,                                 /*!< pointer to bitstream */
                                const Word16 (*CodeBook) [HuffmanEntries])         /*!< pointer to sideinfo of the current codebook */
{
  Word16 val;
  Word16 index = 0;                                                         move16();

  /* This is an inconditional jump. No instrumentation is needed */
  while (true)
  {
    move16(); logic16(); logic16(); /* the table is 8-bit aligned */
    val = CodeBook[index][ReadBits(bs,HuffmanBits)];
 
                                                                            logic16(); test();
    if ((val & 1) == 0)
    {
      index = shr(val, 2);
      continue;
    }
    else
    {
                                                                            logic16(); test();
      if (val & 2)
      {
        WindBitBufferBidirectional(bs,-1);
      }

      val = shr(val, 2);
      break;
    }
  }
  return val;
}


/*!
  \brief Read escape sequence of codeword

  The function reads the escape sequence from the bitstream,
  if the absolute value of the quantized coefficient has the
  value 16.

  \return  quantized coefficient
*/
Word16 CBlock_GetEscape(HANDLE_BIT_BUF bs,  /*!< pointer to bitstream */
                        const Word16 q)     /*!< quantized coefficient */
{
  Word16 i, off, neg ;

                                                                            test();
  if (q < 0)
  {
    test(); sub(q,-16);
    if (q != -16) return q;
    neg = 1;                                                                move16();
  }
  else
  {
    test(); sub(q,16);
    if (q != +16) return q;
    neg = 0;                                                                move16();
  }

  for (i=4; ; i++)
  {
    test();
    if (ReadBits(bs,1) == 0)
      break;
  }

  test(); sub(i,12);
  if(i > 12) /* MAX_QUANTIZED VALUE in ESC syntax is 11111111 0 111111111111 */
    return (MAX_QUANTIZED_VALUE + 1); /* returning invalid value that will be captured later */
  else
    off = (Word16)ReadBits(bs,i);

  i = add(off, shl(1, i));

                                                                            test();
  if (neg) i = negate(i);

  return i;
}

/*!
  \brief Conversion of index values to quantized coefficients

  The function converts the index values to quantized coefficients.

  \return  dimension
*/
Word16 CBlock_UnpackIndex(Word16 idx,                        /*!< pointer to index */
                          Word16 *qp,                        /*!< pointer to quantized coefficients */
                          const CodeBookDescription *hcb)    /*!< pointer to sideinfo of the current codebook */
{
  Word16 offset, bits, mask;

  offset = hcb->Offset;                                                     move16();
  bits   = hcb->numBits;                                                    move16();
  mask   = sub(shl(1, bits), 1);

  test(); sub(hcb->Dimension, 4);
  if (hcb->Dimension == 4)
  {
    qp[0] = sub((idx & mask), offset);                                      logic16(); move16();
    idx   = shr(idx, bits);
    qp[1] = sub((idx & mask), offset);                                      logic16(); move16();
    idx   = shr(idx, bits);
    qp[2] = sub((idx & mask), offset);                                      logic16(); move16();
    idx   = shr(idx, bits);
    qp[3] = sub((idx & mask), offset);                                      logic16(); move16();
  }
  else
  {
    qp[0] = sub((idx & mask), offset);                                      logic16(); move16();
    idx   = shr(idx, bits);
    qp[1] = sub((idx & mask), offset);                                      logic16(); move16();
  }
  return hcb->Dimension;
}

/*!
  \brief Read the element of the individual channel stream for long blocks

  The function reads the element of the individual channel stream for
  long blocks.

  \return  none
*/
Word16 CLongBlock_Read(HANDLE_BIT_BUF bs,                              /*!< pointer to bitstream */
                       CAacDecoderChannelInfo *pAacDecoderChannelInfo, /*!< pointer to aac decoder channel info */
                       Word16 global_gain)                             /*!< global gain */
{
  Flag GainControlDataPresent;
  Word16 ErrorStatus;

  ErrorStatus = AAC_DEC_OK;                                                 move16();

                                                                            test();
  if ((ErrorStatus = CLongBlock_ReadSectionData(bs,pAacDecoderChannelInfo)))
    return ErrorStatus;

  CLongBlock_ReadScaleFactorData(bs,pAacDecoderChannelInfo,global_gain);

  CPulseData_Read(bs,&pAacDecoderChannelInfo->PulseData);

                                                                            test();
  if( (ErrorStatus = CTns_Read(bs,pAacDecoderChannelInfo)) )
    return ErrorStatus;

  GainControlDataPresent = ReadBits(bs,1);
                                                                            test();
  if (GainControlDataPresent)
  {
    return AAC_DEC_UNIMPLEMENTED_GAIN_CONTROL_DATA;
  }

  ErrorStatus = CLongBlock_ReadSpectralData(bs, pAacDecoderChannelInfo);
  return ErrorStatus;
}

/*!
  \brief Read the element of the individual channel stream for short blocks

  The function reads the element of the individual channel stream for
  short blocks. Gain control data is not supported.

  \return  none
*/
Word16 CShortBlock_Read(HANDLE_BIT_BUF bs,                              /*!< pointer to bitstream */
                        CAacDecoderChannelInfo *pAacDecoderChannelInfo, /*!< pointer to aac decoder channel info */
                        Word16 global_gain)                             /*!< global gain */
{
  Flag GainControlDataPresent;
  Word16 ErrorStatus; 

  ErrorStatus = AAC_DEC_OK;                                                 move16();
  
                                                                            test();
  if ((ErrorStatus = CShortBlock_ReadSectionData(bs,pAacDecoderChannelInfo)))
    return ErrorStatus;

  CShortBlock_ReadScaleFactorData(bs,pAacDecoderChannelInfo,global_gain);

  CPulseData_Read(bs,&pAacDecoderChannelInfo->PulseData);

                                                                            test();
  if ((ErrorStatus = CTns_Read(bs,pAacDecoderChannelInfo)))
     return ErrorStatus;


  GainControlDataPresent = ReadBits(bs,1);

                                                                            test();
  if (GainControlDataPresent)
  {
    return AAC_DEC_UNIMPLEMENTED_GAIN_CONTROL_DATA;
  }

  ErrorStatus = CShortBlock_ReadSpectralData(bs,pAacDecoderChannelInfo);
  return ErrorStatus;
}

void Lap1(Word32 *coef,         /*!< pointer to current spectrum */
          Word16 *prev,         /*!< pointer to overlap data */
          Word16 *out,          /*!< pointer to ouptput time samples */
          const Word16 *window, /*!< pointet to window coefficients */
          Word16 cuScale,       /*!< scalefactor of current samples */
          Word16 size,          /*!< number of spectral lines */
          Word16 stride)        /*!< stride */
{
  Word32 accu;
  Word16 i;

  for (i=0; i<size; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(coef[size+i],   window[i]),  cuScale),
                 L_mult(prev[size-1-i], window[size*2-1-i]));
    out[stride*i]        = etsiopround(L_shl(accu, 1));                     move16();
  }
  
  for (i=0; i<size; i++) {
    accu = L_sub(L_shl(fixmul_32x16b(L_negate(coef[size*2-1-i]), window[size+i]), cuScale),
                 L_mult(prev[i], window[size-1-i]));
    out[stride*(i+size)] = etsiopround(L_shl(accu, 1));                     move16();
  }    
}


void Lap2(Word32 *coef,         /*!< pointer to current spectrum */
          Word32 *prev,         /*!< pointer to previous spectrum */
          Word16 *out,          /*!< pointer to ouptput time samples */
          const Word16 *window, /*!< pointet to window coefficients */
          Word16 cuScale,
          Word16 size,          /*!< number of spectral lines */
          Word16 stride         /*!< stride */
  )
{
  Word32 accu;
  Word16 i;

  for (i=0; i<size; i++) {
    accu = L_sub(fixmul_32x16b(coef[size+i],               window[i]),
                 fixmul_32x16b(prev[size-1-i],             window[size*2-1-i]));
    out[stride*i]        = etsiopround(L_shl(accu, cuScale));   move16();
  }

  for (i=0; i<size; i++) {
    accu = L_sub(fixmul_32x16b(L_negate(coef[size*2-1-i]), window[size+i]),
                 fixmul_32x16b(prev[i],                    window[size-1-i]));
    out[stride*(i+size)] = etsiopround(L_shl(accu, cuScale));   move16();
  }
}

