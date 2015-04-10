/*
   temporal noise shaping tool
 */

#include "aac_rom.h"
#include "tns.h"
#include "FFR_bitbuffer.h"
#include "channelinfo.h"
#include "intrinsics.h"
#include "count.h"


/*!
  \brief Calculate maximum absolute value

  The function returns the maximum absolute value.

  \return  maximum absolute value
*/
static Word32 
MaximumAbs(Word32 a, /*!< value 1 */
           Word32 b) /*!< value 2 */
{

  Word32 tmp;

  Word32 abs_a;
  Word32 abs_b;

  abs_a = L_abs( a );
  abs_b = L_abs( b );

  tmp = L_sub( abs_a, abs_b );

                                                           test();
  if (tmp<0)
    return abs_b;
  else
    return abs_a;

}

/*!
  \brief Returns the minimum of 3 values

  \return  minimum value
*/
static Word16 
Minimum(Word16 a, /*!< value 1 */
        Word16 b, /*!< value 2 */
        Word16 c) /*!< value 3 */
{
  return S_min(S_min(a,b),c);
}

/*!
  \brief Returns the tns data present bit

  \return  tns data present bit
*/
Flag TnsPresent(CTnsData *pTnsData) /*!< pointer to tns side info */
{
  return (pTnsData->TnsDataPresent);
}

/*!
  \brief Converts index values to parcor coefficients

  \return  none
*/
static void 
TnsDecodeCoefficients(const CFilter *filter, /*!< pointer to filter side info */
                      Word16 *a)          /*!< pointer to parcor coefficients */
{
  Word16 i;
  move16();
  for (i=0; i < filter->Order; i++)
  {

    Word16 tmp;
    tmp = sub( filter->Resolution, 3 );
                                                           test();
    if (tmp == 0) {
      a[i+1] = tnsCoeff3[filter->Coeff[i]+4];              move16();
    }
    else {
      a[i+1] = tnsCoeff4[filter->Coeff[i]+8];              move16();
    }
  }
}

/*!
  \brief Conversion of parcor coefficients to lpc coefficients

  \return  none
*/
static void 
TnsParcor2Lpc( Word16 *parcor, /*!< pointer to parcor coefficients */
               Word16 *lpc,    /*!< pointer to lpc coefficients */
               Word16 *scale,  /*!< pointer shift factor */
               Word16  order)  /*!< filter order */

{
  Word16 i,j,status;
  Word32 z1;
  Word16 z[MaximumOrder+1];
  Word16 w[MaximumOrder+1];
  Word32 accu1,accu2;

  status = 1;                                              move16();
  *scale = 0;                                              move16();
  test();
  while ( status ) {
                                                           test();
    status = 0;                                            move16();

    for ( i = MaximumOrder; i >= 0; i-- ) {
      z[i] = 0;                                            move16();
      w[i] = 0;                                            move16();
    }

    for (i=0; i<=order; i++)
    {
                                                           test();
      if (i == 0)
        accu1 = L_shr( 0x7fffffff, *scale );      
      else
        accu1 = (Word32)0;                                 move32();

      z1 = accu1;                                          move32();

      for (j=0; j<order; j++)
      {
        w[j] = etsiopround(accu1);                           move16();

        accu1 = L_mac(accu1, parcor[j], z[j]);
                                                           test();
        if ( L_abs(accu1) == 0x7fffffff )
          status = 1;                                      move16();
      }
      sub(order,1);
      for (j=order-1; j>=0; j--)
      {
        accu2  = L_deposit_h(z[j]);
        accu2  = L_mac(accu2, parcor[j], w[j]);
        z[j+1] = etsiopround(accu2);                         move16();
        L_sub(0,0);                                        test();
        if( L_abs(accu2) == 0x7fffffff )
          status = 1;                                      move16();
      }

      z[0] = etsiopround(z1);                                move16();
      lpc[i] = extract_h(accu1);                           move16();

    }

    accu1 = L_deposit_l(sub(status,1));
                                                           test();
    if (accu1 == 0) {
      *scale = add(*scale, 1);                             move16();
    }
  }
}


/*!
  \brief Tns filtering of the spectrum

  \return  none
*/
static void 
TnsFilterIIR(Word32 *  spec,   /*!< pointer to spectrum */
             Word16 *  lpc,    /*!< pointer to lpc coefficients */
             Word16 * stateLo,
             Word16 * stateHi,
             Word32 size,    /*!< nunber of filtered spectral lines */
             Word16 inc,    /*!< increment or decrement */
             Word16 order,   /*!< filter order */
             Word16 scaleLpc)/*!< number of scales lpc coefficients */

{
  Word16 i,j;
  Word32 accu;
  Word16 accu_s;


  for (i=0; i<order; i++)
  {
    stateLo[i] = 0;                                                                                move16();
    stateHi[i] = 0;                                                                                move16();
  }

  accu_s = add(inc,1);
                                                                                                   test();
  if (accu_s == 0)
  {
    spec += size-1; L_sub(size,1);
  }
  for (i=0; i<size; i++)
  {
	accu = L_sub(fixmul_32x16b( *spec, lpc[0]), Mpy_32_16(stateHi[0], stateLo[0], lpc[1]));

    sub(order,1);
    for (j=order-1; j>0; j--)
    {
      accu = L_sub( accu, Mpy_32_16(stateHi[j], stateLo[j], lpc[j+1]) );

      stateHi[j] = stateHi[j-1];                                                                   move16();
      stateLo[j] = stateLo[j-1];                                                                   move16();
    }
    
    accu = L_shl( accu, scaleLpc );

    stateHi[0] = extract_h(accu);
    stateLo[0] = shr(extract_l(accu),1) & 0x7FFF;                                                  move16(); logic16();

    *spec = accu;                                                                                  move32();

    spec += inc;
  }

}

/*!
  \brief Read tns data from bitstream

  \return  none
*/
Word16 
CTns_Read(HANDLE_BIT_BUF bs,                              /*!< pointer to bitstream */
          CAacDecoderChannelInfo *pAacDecoderChannelInfo) /*!< pointer to aac decoder channel info */
{
  Word16 window;
  Word16 n_filt,order;
  Word16 length,coef_res,coef_compress;  
  CTnsData *pTnsData = &pAacDecoderChannelInfo->TnsData;                                           move16();

  pTnsData->TnsDataPresent = (Flag) ReadBits(bs,1); move16();

                                                                                                   test();
  if (!pTnsData->TnsDataPresent) 
    return AAC_DEC_OK;
  move16(); /*GetWindowsPerFrame*/
  for (window = 0; window < GetWindowsPerFrame(&pAacDecoderChannelInfo->IcsInfo); window++)
  {
    pTnsData->NumberOfFilters[window] = n_filt =
      (Word16) ReadBits(bs,IsLongBlock(&pAacDecoderChannelInfo->IcsInfo) ? 2 : 1);                  test();move16();move16();
                                                                                                   test();
    if (n_filt)                                                                                    
    {
      Word16 accu;
      Word16 index;
      Word16 nextstopband;

      coef_res = (Word16) ReadBits(bs,1);

      nextstopband = GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo);                   move16();

      for (index=0; index < n_filt; index++)
      {
        CFilter* filter = &pTnsData->Filter[window][index];                                        move16();

        length = (Word16) ReadBits(bs,IsLongBlock(&pAacDecoderChannelInfo->IcsInfo) ? 6 : 4);      test(); move16();

        filter->StartBand = sub(nextstopband, length);                                              move16();
        filter->StopBand  = nextstopband;                                                           move16();
        
        nextstopband = filter->StartBand;                                                           move16();

                                                                                                   test();
        if(filter->StartBand < 0)                                                                   
          return AAC_DEC_TNS_RANGE_ERROR;

        filter->Order = order =
          (Word16) ReadBits(bs,IsLongBlock(&pAacDecoderChannelInfo->IcsInfo) ? 5 : 3);             test();move16();move16();

        accu = sub( filter->Order, MaximumOrder);                                                  test();
        if( accu > 0 )  
          return AAC_DEC_TNS_ORDER_ERROR;

        test();
        if (order)
        {
          Word16 i;
          Word16 coef,s_mask,n_mask;

          filter->Direction = ReadBits(bs,1) ? -1 : 1;                                             test(); move16();

          coef_compress = (Word16) ReadBits(bs,1);

          filter->Resolution = add(coef_res, 3);                                                   move16();

          s_mask = sgn_mask[coef_res + 1 - coef_compress];                                         move16();                              
          n_mask = neg_mask[coef_res + 1 - coef_compress];                                         move16();

          for (i=0; i < order; i++)
          {
            coef = (Word16) ReadBits(bs,sub(filter->Resolution, coef_compress));
                                                                                                   logic16();test();
            if ( coef & s_mask ) {
              filter->Coeff[i] = (coef | n_mask);                                                  logic16();move16(); 
            }                                        
            else {
              filter->Coeff[i] = coef;                                                             move16();
            }
          }
        }
      }
    }
  }
  return AAC_DEC_OK;
}

/*!
  \brief Apply tns to spectral lines

  \return  none
*/
void CTns_Apply (CAacDecoderChannelInfo *pAacDecoderChannelInfo, /*!< pointer to aac decoder info */
                 Word16 maxSfb)                                  /*!< highest sfb up to which TNS shall be applied */
{
  Word16 i;
  Word16 scaleLpc;
  Word32 maxSpectralLine;
  CTnsData *pTnsData = &pAacDecoderChannelInfo->TnsData;
  Word32 *pSpectrum = pAacDecoderChannelInfo->pSpectralCoefficient;

  Word16 window,index,start,stop,size,scaleSpec;
  
  Word16 lpc[MaximumOrder+1];
  Word16 CoeffParc[MaximumOrder+1];
  Word16 stateLo[MaximumOrder];
  Word16 stateHi[MaximumOrder];
                                                                                                   move16(); move16();

  test();
  if (!pTnsData->TnsDataPresent) return;

  move16(); /*GetWindowsPerFrame*/
  for (window=0; window < GetWindowsPerFrame(&pAacDecoderChannelInfo->IcsInfo); window++)
  {
    move16(); /*pTnsData->NumberOfFilters[window]*/
    for (index=0; index < pTnsData->NumberOfFilters[window]; index++)
    {
      CFilter* filter = &pTnsData->Filter[window][index];                                          move16();

      TnsDecodeCoefficients(filter,CoeffParc);

      start = Minimum(filter->StartBand,GetMaximumTnsBands(&pAacDecoderChannelInfo->IcsInfo),
                      maxSfb);

      start = GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo)[start];                  move16();

      stop = Minimum(filter->StopBand, GetMaximumTnsBands(&pAacDecoderChannelInfo->IcsInfo),
                     maxSfb);

      stop = GetScaleFactorBandOffsets(&pAacDecoderChannelInfo->IcsInfo)[stop];                    move16();

      size = sub(stop,start);                                                                      

                                                                                                   test();
      if (size <= 0) continue;
                                                                                                   test();
      if (filter->Order <= 0) continue;

      TnsParcor2Lpc(&CoeffParc[1],lpc,&scaleLpc,filter->Order);

      maxSpectralLine = 0;                                                                         move32();

      for (i=0; i<size; i++)
        maxSpectralLine =  MaximumAbs(pSpectrum[start+i],maxSpectralLine);                         
      scaleSpec = norm_l(maxSpectralLine);                                                         
      
      scaleSpec = sub(sub(scaleSpec, 3), scaleLpc);

      {
        Word32 *pTmp = pSpectrum + start; move16();
        for ( i = size; i != 0; i-- ) {
          *pTmp = L_shl(*pTmp, scaleSpec);                                                         move32();
          pTmp++;
        }
      }

      TnsFilterIIR(&pSpectrum[shl(window,7)+start],lpc, stateLo, stateHi, size,
                   filter->Direction,filter->Order,scaleLpc);

      {
        Word32 *pTmp = pSpectrum + start; move16();
        for ( i = size; i != 0; i-- ) {
          *pTmp = L_shr(*pTmp, scaleSpec);                                                         move32();
          pTmp++;
        }
      }

    }
  }
}