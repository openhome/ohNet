/*
   channel info
 */

#include "channel.h"
#include "ffr.h"
#include "intrinsics.h"
#include "stereo.h"
#include "count.h"
#include "tns.h"
#include <string.h>



void CTns_Apply(CAacDecoderChannelInfo *pAacDecoderChannelInfo, Word16 maxSfb);


/*!
  \brief Read individual channel stream from bitstream

  \return  none
*/
Word16 ReadICS(HANDLE_BIT_BUF bs,                              /*!< pointer to bitstream */
               CAacDecoderChannelInfo *pAacDecoderChannelInfo) /*!< pointer to aac decoder channel info */
{
  Word16 ErrorStatus = AAC_DEC_OK;                                                                                               move16();
  
  /* reads one individual_channel_stream */
  pAacDecoderChannelInfo->RawDataInfo.GlobalGain = (Word16)ReadBits(bs,8);
                                                                                                                                 test();
  if (!IsValid(&pAacDecoderChannelInfo->IcsInfo))                                                                                 
  {                                                                                                                              test();
    if ((ErrorStatus = IcsRead(bs,&pAacDecoderChannelInfo->IcsInfo)))                                                        
      return ErrorStatus;
  }
                                                                                                                                 test();
  if (IsLongBlock(&pAacDecoderChannelInfo->IcsInfo))                                                                            
  {                                                                                                                              test();
    if ((ErrorStatus = CLongBlock_Read(bs,pAacDecoderChannelInfo,pAacDecoderChannelInfo->RawDataInfo.GlobalGain)))              
      return ErrorStatus;
  }
  else
  {
    CShortBlock_Init(pAacDecoderChannelInfo);                                                                                    test();
    if ((ErrorStatus = CShortBlock_Read(bs,pAacDecoderChannelInfo,pAacDecoderChannelInfo->RawDataInfo.GlobalGain)))
      return ErrorStatus;
  }
  return ErrorStatus;
}




/*!
  \brief Read single channel element from bitstream

  \return  element instance tag
*/
Word16
CSingleChannelElement_Read(HANDLE_BIT_BUF bs,                                 /*!< pointer to bitstream */
                           CAacDecoderChannelInfo *pAacDecoderChannelInfo[2], /*!< pointer to aac decoder channel info */
                           CStreamInfo *pStreamInfo,                          /*!< pointer to stream info */
                           Word16 *pElementInstanceTag                        /*!< pointer to elementInstanceTag */
                           )
{
  Word16 ErrorStatus = AAC_DEC_OK;                                                                                               move16();

  IcsReset(&pAacDecoderChannelInfo[L]->IcsInfo,pStreamInfo);

  pAacDecoderChannelInfo[L]->RawDataInfo.ElementInstanceTag = (Word16)ReadBits(bs,4);

                                                                                                                                 test();
  if (( ErrorStatus = ReadICS(bs,pAacDecoderChannelInfo[L])))
    return ErrorStatus;

  *pElementInstanceTag = pAacDecoderChannelInfo[L]->RawDataInfo.ElementInstanceTag; move16();

  /* Check if too many bits have been read */                                                                                    test();
  if (bs->cntBits < 0) {
    ErrorStatus = AAC_DEC_DECODE_FRAME_ERROR;                                                                                    move16();
  }

  return ErrorStatus;
}

/*!
  \brief Read channel pair element from bitstream

  \return  element instance tag
*/
Word16
CChannelPairElement_Read(HANDLE_BIT_BUF bs,                                 /*!< pointer to bitstream */
                         CAacDecoderChannelInfo *pAacDecoderChannelInfo[2], /*!< pointer to aac decoder channel info */
                         CStreamInfo *pStreamInfo,                          /*!< pointer to stream info */
                         Word16 *pElementInstanceTag                        /*!< pointer to elementInstanceTag */
                         )
{
  Word16 ErrorStatus = AAC_DEC_OK;                                                                                                move16();

  pAacDecoderChannelInfo[L]->RawDataInfo.ElementInstanceTag = (Word16)ReadBits(bs,4);
  IcsReset(&pAacDecoderChannelInfo[L]->IcsInfo,pStreamInfo);
  IcsReset(&pAacDecoderChannelInfo[R]->IcsInfo,pStreamInfo);

  pAacDecoderChannelInfo[L]->RawDataInfo.CommonWindow = (Word16)ReadBits(bs,1);

                                                                                                                                  test();
  if (pAacDecoderChannelInfo[L]->RawDataInfo.CommonWindow)
  {                                                                                                                               test();
    if ((ErrorStatus = IcsRead(bs,&pAacDecoderChannelInfo[L]->IcsInfo)))
      return ErrorStatus;

    pAacDecoderChannelInfo[R]->IcsInfo = pAacDecoderChannelInfo[L]->IcsInfo; move16();

    CJointStereo_Read(bs,
                      pAacDecoderChannelInfo[L]->pJointStereoData,
                      GetWindowGroups(&pAacDecoderChannelInfo[L]->IcsInfo),
                      pAacDecoderChannelInfo[L]->IcsInfo.MaxSfBands);
  }


                                                                                                                                 test();
  if ((ErrorStatus = ReadICS(bs,pAacDecoderChannelInfo[L])))
    return ErrorStatus;
                                                                                                                                 test();
  if ((ErrorStatus = ReadICS(bs,pAacDecoderChannelInfo[R])))
    return ErrorStatus;

  *pElementInstanceTag = pAacDecoderChannelInfo[L]->RawDataInfo.ElementInstanceTag;                                              move16();

  /* Check if too many bits have been read */                                                                                    test();
  if (bs->cntBits < 0) {
    ErrorStatus = AAC_DEC_DECODE_FRAME_ERROR;                                                                                    move16();
  }

  return ErrorStatus;
}


/*!
  \brief  Calculate common scale for all scalefactor bands of each window

*/
static void calcSpecScale(CAacDecoderChannelInfo *pAacDecoderChannelInfo  /*!< pointer to aac decoder channel info */
                   )
{
  Word16 band;
  Word16 *pSfbScale = pAacDecoderChannelInfo->pSfbScale;                                                                         
  Word16 extraScale = 0;                                                                                                         move16();move16();
  test();
  if ( TnsPresent(&pAacDecoderChannelInfo->TnsData) ) {
    extraScale = add(extraScale,TNS_SCALE);  /* avoids overflows later */
  }
                                                                                                                                 test();
  if (IsLongBlock(&pAacDecoderChannelInfo->IcsInfo)) {
    Word16 maxScale = 0;    /* Start value for maximum search */                                                                 move16();
    move16(); /*GetScaleFactorBandsTotal*/
    for (band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++) {
      maxScale = S_max(maxScale, pSfbScale[band]);
    }
    pAacDecoderChannelInfo->pSpecScale[0] = add(maxScale,extraScale);                                                            move16();
  }
  else {
    Word16 window = 0;                                                                                                           
    Word16 group, groupwin;                                                                                                      move16();
    move16(); /*GetWindowGroups*/
    move16(); /*GetScaleFactorBandsTotal*/
    for (group=0; group < GetWindowGroups(&pAacDecoderChannelInfo->IcsInfo); group++) {
      move16(); /*GetWindowGroupLength*/
      for (groupwin=0; groupwin < GetWindowGroupLength(&pAacDecoderChannelInfo->IcsInfo,group); groupwin++, window++) {
        Word16 maxScale = 0;    /* Start value for maximum search */                                                             move16();
        for (band=0; band < GetScaleFactorBandsTotal(&pAacDecoderChannelInfo->IcsInfo); band++) {
          maxScale = S_max(maxScale, pSfbScale[window*MaximumScaleFactorBandsShort+band]);
        }
        pAacDecoderChannelInfo->pSpecScale[window] = add(maxScale, extraScale);                                                  move16();
      }
    }
  }
}

/*!
  \brief Decode single channel element

  \return  none
*/
void CSingleChannelElement_Decode(CAacDecoderChannelInfo *pAacDecoderChannelInfo[]    /*!< pointer to aac decoder channel info */
                                  )
{
  calcSpecScale(pAacDecoderChannelInfo[L]);
                                                                                                                                 test();
  if (IsLongBlock(&pAacDecoderChannelInfo[L]->IcsInfo))
    CLongBlock_ScaleSpectralData(pAacDecoderChannelInfo[L]);
  else
    CShortBlock_ScaleSpectralData(pAacDecoderChannelInfo[L]);

  CPns_Apply(pAacDecoderChannelInfo, 0);
  CTns_Apply(pAacDecoderChannelInfo[L], pAacDecoderChannelInfo[L]->IcsInfo.MaxSfBands);
}


/*!
  \brief Decode channel pair element

  \return  none
*/
void CChannelPairElement_Decode(CAacDecoderChannelInfo *pAacDecoderChannelInfo[]     /*!< pointer to aac decoder channel info */
                                )
{
  Word16 channel;


  /*
    apply ms
  */                                                                                                                             test();
  if (pAacDecoderChannelInfo[L]->RawDataInfo.CommonWindow) {

    if (pAacDecoderChannelInfo[L]->PnsData.PnsActive || pAacDecoderChannelInfo[R]->PnsData.PnsActive) {                          logic16(); test();
      MapMidSideMaskToPnsCorrelation(pAacDecoderChannelInfo);
    }
    CJointStereo_ApplyMS(pAacDecoderChannelInfo,
                         GetScaleFactorBandOffsets(&pAacDecoderChannelInfo[L]->IcsInfo),
                         GetWindowGroupLengthTable(&pAacDecoderChannelInfo[L]->IcsInfo),
                         GetWindowGroups(&pAacDecoderChannelInfo[L]->IcsInfo),
                         pAacDecoderChannelInfo[L]->IcsInfo.MaxSfBands);
  }

  CJointStereo_ApplyIS(pAacDecoderChannelInfo,
                       GetScaleFactorBandOffsets(&pAacDecoderChannelInfo[L]->IcsInfo),
                       GetWindowGroupLengthTable(&pAacDecoderChannelInfo[L]->IcsInfo),
                       GetWindowGroups(&pAacDecoderChannelInfo[L]->IcsInfo),
                       pAacDecoderChannelInfo[L]->IcsInfo.MaxSfBands,
                       pAacDecoderChannelInfo[L]->RawDataInfo.CommonWindow);

  /*
    Scaling
  */
  for (channel=0; channel < Channels; channel++) {

    calcSpecScale(pAacDecoderChannelInfo[channel]);
                                                                                                                                 test();
    if (IsLongBlock(&pAacDecoderChannelInfo[channel]->IcsInfo))
      CLongBlock_ScaleSpectralData(pAacDecoderChannelInfo[channel]);
    else
      CShortBlock_ScaleSpectralData(pAacDecoderChannelInfo[channel]);
  }


  for (channel=0; channel < Channels; channel++)
  {
    CPns_Apply(pAacDecoderChannelInfo, channel);
    CTns_Apply(pAacDecoderChannelInfo[channel], pAacDecoderChannelInfo[channel]->IcsInfo.MaxSfBands);
  }
}

void MapMidSideMaskToPnsCorrelation (CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels])
{
  Word16 group, band, groupmask;

  for (group = 0; group < pAacDecoderChannelInfo[L]->IcsInfo.WindowGroups; group++) {
    groupmask = shl(1, group);
    for (band = 0; band < pAacDecoderChannelInfo[L]->IcsInfo.MaxSfBands; band++) {
      if (pAacDecoderChannelInfo[L]->pJointStereoData->MsUsed[band] & groupmask) { /* channels are correlated */                 logic16(); test();
        CPns_SetCorrelation(pAacDecoderChannelInfo[L], group, band);
        if (CPns_IsPnsUsed(pAacDecoderChannelInfo[L], group, band) &&
            CPns_IsPnsUsed(pAacDecoderChannelInfo[R], group, band)) {
          pAacDecoderChannelInfo[L]->pJointStereoData->MsUsed[band] ^= groupmask;
        }
      }
    }
  }
}
