/*
   joint stereo processing
 */

#include "aac_rom.h"
#include "FFR_bitbuffer.h"
#include "intrinsics.h"
#include "count.h"
#include "stereo.h"

/*!
  \brief Read joint stereo data from bitstream

  The function reads joint stereo data from bitstream.

  \return  none
*/

void CJointStereo_Read(HANDLE_BIT_BUF bs,                   /*!< pointer to bitstream */
                       CJointStereoData *pJointStereoData,  /*!< pointer to joint stereo side info */
                       Word16 windowGroups,                 /*!< number of window groups */
                       Word16 scaleFactorBandsTransmitted   /*!< number of transmitted scalefactor bands */
                       ) 
{
  Word16 group,band;
  Word16 accu;

  pJointStereoData->MsMaskPresent = (Word16) ReadBits(bs,2);

  /* Clear MS mask */
  for (band=0; band<scaleFactorBandsTransmitted; band++)
  {
    pJointStereoData->MsUsed[band] = 0;                                                            move16();
  }
  
  accu = sub( pJointStereoData->MsMaskPresent, 1);

  test(); test(); 
  if ( accu == 0 ) {
    for (group=0; group<windowGroups; group++)
    {
      for (band=0; band<scaleFactorBandsTransmitted; band++)
      {
        pJointStereoData->MsUsed[band] |= shl( (Word16)ReadBits(bs,1) , group );                   logic16();move16();
      }
    }
  }
  else if ( accu > 0 ) {
    for (band=0; band<scaleFactorBandsTransmitted; band++)
    {
      pJointStereoData->MsUsed[band] = 255 ;  /* set all flags to 1 */                             move16();
    }
  }
}

/*!
  \brief Applies MS stereo

  The function applies MS stereo.

  \return  none
*/

void CJointStereo_ApplyMS(CAacDecoderChannelInfo *pAacDecoderChannelInfo[2],   /*!< aac channel info */
                          const Word16 *pScaleFactorBandOffsets,               /*!< pointer to scalefactor band offsets */
                          Word16 *pWindowGroupLength,                          /*!< pointer to window group length array */
                          Word16 windowGroups,                                 /*!< number of window groups */
                          Word16 scaleFactorBandsTransmitted)                  /*!< number of transmitted scalefactor bands */
{
  Word16 window, group, groupwin, index;

  CJointStereoData *pJointStereoData = pAacDecoderChannelInfo[0]->pJointStereoData;
  move16();

  window=0; move16();
  for (group=0; group<windowGroups; group++)
  {
    Word16 groupMask = shl(1,group);
    move16(); /*pWindowGroupLength[group]*/
    for (groupwin=0; groupwin<pWindowGroupLength[group]; groupwin++, window++)
    {
      Word16 band;

      Word32 *LeftSpectrum  = &pAacDecoderChannelInfo[0]->pSpectralCoefficient[window*128];
      Word32 *RightSpectrum = &pAacDecoderChannelInfo[1]->pSpectralCoefficient[window*128];

      Word16 *leftScale  = &pAacDecoderChannelInfo[0]->pSfbScale[window*MaximumScaleFactorBandsShort];
      Word16 *rightScale = &pAacDecoderChannelInfo[1]->pSfbScale[window*MaximumScaleFactorBandsShort];
           
                                                                                                   move16(); move16();
                                                                                                   move16(); move16();
      for (band=0; band<scaleFactorBandsTransmitted; band++)
      {
                                                                                                   logic16(); test();
        if (pJointStereoData->MsUsed[band] & groupMask)
        {
          Word16 accu;
          Word16 lScale = leftScale[band];
          Word16 rScale = rightScale[band];
          Word16 commonScale;

                                                                                                   move16();
                                                                                                   move16();

          accu = sub(lScale,rScale);
                                                                                                   test();
          if ( accu > 0 ) {
            commonScale = lScale;                                                                  move16();
          }
          else {
            commonScale = rScale;                                                                  move16();
          }

          commonScale = add(commonScale,1);
          leftScale[band]  = commonScale;                                                          move16();                                                    
          rightScale[band] = commonScale;                                                          move16();

          move16(); /*pScaleFactorBandOffsets[band+1]*/
          for (index=pScaleFactorBandOffsets[band]; index<pScaleFactorBandOffsets[band+1]; index++)
          {

            Word32 LeftCoefficient  = L_shr(LeftSpectrum[index],  sub(commonScale,lScale));
            Word32 RightCoefficient = L_shr(RightSpectrum[index], sub(commonScale,rScale));

            LeftSpectrum[index]  = L_add( LeftCoefficient, RightCoefficient );                     move32();
            RightSpectrum[index] = L_sub( LeftCoefficient, RightCoefficient );                     move32();

          }
        }
      }
    }
  }
}

void CJointStereo_ApplyIS(CAacDecoderChannelInfo *pAacDecoderChannelInfo[2], /*!< aac channel info */
                          const Word16 *pScaleFactorBandOffsets,             /*!< pointer to scalefactor band offsets */
                          Word16 *pWindowGroupLength,                        /*!< pointer to window group length array */
                          Word16 windowGroups,                               /*!< number of window groups */
                          Word16 scaleFactorBandsTransmitted,                /*!< number of transmitted scalefactor bands */
                          Word16 CommonWindow)                               /*!< common window bit */
{
  Word16 window, group, groupwin, index;

  CJointStereoData *pJointStereoData = pAacDecoderChannelInfo[0]->pJointStereoData;
  move16();

  window=0; move16();
  for (group=0; group<windowGroups; group++)
  {
    Word8  *CodeBook    = &pAacDecoderChannelInfo[1]->pCodeBook[group*MaximumScaleFactorBandsShort];
    Word16 *ScaleFactor = &pAacDecoderChannelInfo[1]->pScaleFactor[group*MaximumScaleFactorBandsShort];
    move16(); move16(); 
    move16(); /*pWindowGroupLength[group]*/
    for (groupwin=0; groupwin<pWindowGroupLength[group]; groupwin++, window++)
    {
      Word16 band;

      Word32 *LeftSpectrum  = &pAacDecoderChannelInfo[0]->pSpectralCoefficient[window*128];
      Word32 *RightSpectrum = &pAacDecoderChannelInfo[1]->pSpectralCoefficient[window*128];
      Word16 *leftScale  = &pAacDecoderChannelInfo[0]->pSfbScale[window*MaximumScaleFactorBandsShort];
      Word16 *rightScale = &pAacDecoderChannelInfo[1]->pSfbScale[window*MaximumScaleFactorBandsShort];
                                                                                                   move16(); move16();
                                                                                                   move16(); move16();

      for (band=0; band<scaleFactorBandsTransmitted; band++)
      {
        logic16(); test(); logic16(); test(); 
        if ((CodeBook [band] == INTENSITY_HCB) || (CodeBook [band] == INTENSITY_HCB2))
        {
          Word16 iSfbFactor, scfExp, scfMod;
          Word32 scale;
#if 0
          Word16 scale_h, scale_l;
#endif
          add(ScaleFactor[band],100);
          iSfbFactor = ScaleFactor[band]+100;
          scfExp = shr(negate(iSfbFactor), 2);
          scfMod = (negate(iSfbFactor)) & 3;                                                       logic16();
          scale  = specExpMantTableComb[scfMod][0]; move32();
          
          rightScale[band] = add(add(leftScale[band], scfExp), 1); move16();

          test(); test(); logic32(); 
          if (CommonWindow && (pJointStereoData->MsUsed[band] & (L_shl(1, group))))
          {
            test(); logic16();
            if (CodeBook[band] == INTENSITY_HCB) /* _NOT_ in-phase */
            {
              scale = L_negate(scale);
            }
          }
          else
          {
            test(); logic16();
            if (CodeBook[band] == INTENSITY_HCB2) /* out-of-phase */
            {
              scale = L_negate(scale);
            }
          }

#if 0
          L_Extract(scale, &scale_h, &scale_l);
#endif
          move16(); /*pScaleFactorBandOffsets[band+1]*/
          for (index=pScaleFactorBandOffsets[band]; index<pScaleFactorBandOffsets[band+1]; index++)
          {
#if 0
            Word16 LeftSpectrum_h, LeftSpectrum_l;

            L_Extract(LeftSpectrum[index], &LeftSpectrum_h, &LeftSpectrum_l);

            RightSpectrum[index] = Mpy_32(scale_h, scale_l, LeftSpectrum_h, LeftSpectrum_l); move32();
#else
            RightSpectrum[index] = fixmul(scale, LeftSpectrum[index]);
#endif
          }
        }
      }
    }
  }
}
