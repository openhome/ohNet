/*
   decoder main
 */

#include <assert.h>
#include <string.h>
#include "intrinsics.h"
#include "count.h"

#include "aac_rom.h"
#include "aac_ram.h"
#include "aacdecoder.h"
#include "FFR_bitbuffer.h"
#include "conceal.h"

#include "aacpluscheck.h"

struct AAC_DECODER_INSTANCE {
  Flag frameOK;
  Word32 bitCount;
  Word32 byteAlignBits;
  HANDLE_BIT_BUF pBs;
  SBRBITSTREAM *pStreamSbr;
  CStreamInfo *pStreamInfo;
  CDataStreamElement *pDataStreamElement;
  CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels];
  CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo[Channels];
  CConcealmentInfo *hConcealmentInfo;
};


struct AAC_DECODER_INSTANCE AacDecoderInstance;


static Word8 sbrPayloadBuffer[4][MAXSBRBYTES]; /*!< 2 SBR elements for the current frame and another 2 for the previous */


#include "conceal.h"

void CPns_InitPns(CAacDecoderChannelInfo *pAacDecoderChannelInfo);
void CPns_InitInterChannelData(CAacDecoderChannelInfo *pAacDecoderChannelInfo);



/*!
  \brief Initialization of AacDecoderChannelInfo

  \return Decoder handle; In case of errors NULL
*/
AACDECODER CAacDecoderOpen(HANDLE_BIT_BUF pBs,          /*!< pointer to bitbuffer structure */
                           SBRBITSTREAM *pStreamSbr,    /*!< pointer to SBR bitstream */
                           Word32 samplingRate
                           )
{
  Word16 i,ch;

  /* initialize pointer to bit buffer structure */
  AacDecoderInstance.pBs = pBs;                                                                     move16();

  /* initialize pointer to sbr bitstream structure */
  AacDecoderInstance.pStreamSbr = pStreamSbr;                                                       move16();

  /* initialize bit counter for syncroutine */
  AacDecoderInstance.bitCount = 0;                                                                  move32();

  /* initialize data stream */
  CDataStreamElementOpen(&AacDecoderInstance.pDataStreamElement);

  /* initialize stream info */
  CStreamInfoOpen(&AacDecoderInstance.pStreamInfo);

  /* initialize CAacDecoderChannelInfo */
  for (ch=0; ch<Channels; ch++)
  {
    /* initialize pointer to CAacDecoderStaticChannelInfo for each channel */
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch] = &AacDecoderStaticChannelInfo[ch];         move16();

    /* initialize overlap & add for each channel */
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->OverlapAddData.WindowShape = 0;            move16();
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->OverlapAddData.WindowSequence = 0;         move16();
                                                                                                    move16();
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->OverlapAddData.pOverlapBuffer = &OverlapBuffer[ch*OverlapBufferSize];

    for (i=0; i<512; i++) {
      AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->OverlapAddData.pOverlapBuffer[i] = 0;    move16();
    }

    /* initialize window shapes for each channel */
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->pLongWindow[0] = OnlyLongWindowSine;       move16();
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->pShortWindow[0] = OnlyShortWindowSine;     move16();
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->pLongWindow[1] = OnlyLongWindowKBD;        move16();
    AacDecoderInstance.pAacDecoderStaticChannelInfo[ch]->pShortWindow[1] = OnlyShortWindowKBD;      move16();
  }

  AacDecoderInstance.hConcealmentInfo = CConcealment_Init(Channels);
                                                                                                    test();
  if( AacDecoderInstance.hConcealmentInfo == NULL) {
    return NULL;
  }

  /*
    Setup buffers for SBR payload
  */
  for (i=0; i<2; i++)  /* i=0: for current frame,  i=1: for previous frame */
  {
    /* SBR payload for the current and for the previous frame, with 2 elements for each */
    AacDecoderInstance.pStreamSbr[i].sbrElement[0].pData = (Word8*) sbrPayloadBuffer[2*i];          move16();
    AacDecoderInstance.pStreamSbr[i].sbrElement[1].pData = (Word8*) sbrPayloadBuffer[2*i+1];        move16();

    AacDecoderInstance.pStreamSbr[i].sbrElement[0].elementID = ID_SCE;                              move16();
    AacDecoderInstance.pStreamSbr[i].sbrElement[1].elementID = ID_SCE;                              move16();
    AacDecoderInstance.pStreamSbr[i].sbrElement[0].sizePayload = 0;                                 move16();
    AacDecoderInstance.pStreamSbr[i].sbrElement[1].sizePayload = 0;                                 move16();
    AacDecoderInstance.pStreamSbr[i].nrElements = 0;                                                move16();
  }


  {
    Word32 numEntries = sizeof(SamplingRateInfoTable)/sizeof(SamplingRateInfo);                     move32();

    for (i=0; i<numEntries; i++) {
                                                                                                    test();
      if (samplingRate == SamplingRateInfoTable[i].SamplingFrequency)
        break;
    }

                                                                                                    test();
    if (i == numEntries) {
      return NULL;
    }

    AacDecoderInstance.pStreamInfo->Profile = 1;                                                    move16();
    AacDecoderInstance.pStreamInfo->SamplingRateIndex = (Word8)i;                                   move16();
    AacDecoderInstance.pStreamInfo->SamplingRate = samplingRate;                                    move32();
  }

  return &AacDecoderInstance;
}




/*!
  \brief     Delay SBR bitstream

  \return none */
static
void DelaySbrBitstr(SBRBITSTREAM *hSbrBS)  /*!< SBR bitstream handle */
{
  SBRBITSTREAM bs_tmp;

  /* Swap current and previous bitstream info */
  bs_tmp    = hSbrBS[0];                                                                            move16();
  hSbrBS[0] = hSbrBS[1];                                                                            move16();
  hSbrBS[1] = bs_tmp;                                                                               move16();
}


/*!
  \brief Decodes one aac frame for adts/adif 

  \return  none
*/
Word16 CAacDecoder_DecodeFrame(AACDECODER self,            /*!< pointer to aacdecoder structure */
                               Word16    *frameSize,       /*!< pointer to frame size */
                               Word32    *sampleRate,      /*!< pointer to sample rate */
                               Word8     *channelMode,     /*!< mode: 0=mono, 1=stereo */
                               Word16    *numChannels,     /*!< pointer to number of channels */
                               Word16    *pTimeData,       /*!< pointer to time data */
                               Flag       frameOK          /*!< Flag indicating if data ok */
                               )
{
  Word16 type;
  Word16 ch;
  Word16 ErrorStatus = frameOK;
  Word16 element_instance_tag;
  static Word32 BlockNumber = 0;
  HANDLE_BIT_BUF bs;
  Word16 previous_element;

  extern Word32 WorkBuffer1[Channels*MaximumBinsLong];
  assert(((sizeof(CAacDecoderChannelInfo)+sizeof(CAacDecoderDynamicData))*Channels + sizeof(CAacDecoderDynamicCommonData)) <= sizeof(WorkBuffer1));

  move16(); move16();


  type        = 0;                                                                                  move16();
  bs          = self->pBs;                                                                          move16();
  self->frameOK = 1;                                                                                move16();

  /* initialize pointer to CAacDecoderChannelInfo for each channel */
  for (ch=0; ch<Channels; ch++)
  {
    self->pAacDecoderChannelInfo[ch] = pAacDecoderChannelInfoInit[ch];                              move16();
    self->pAacDecoderChannelInfo[ch]->pCodeBook = pAacDecoderDynamicDataInit[ch]->aCodeBook;        move16();
    self->pAacDecoderChannelInfo[ch]->pSfbScale = pAacDecoderDynamicDataInit[ch]->aSfbScale;        move16();
    self->pAacDecoderChannelInfo[ch]->pSpecScale = pAacDecoderDynamicDataInit[ch]->aSpecScale;      move16();
    self->pAacDecoderChannelInfo[ch]->pScaleFactor = pAacDecoderDynamicDataInit[ch]->aScaleFactor;  move16();
    self->pAacDecoderChannelInfo[ch]->pSpectralCoefficient = &WorkBufferCore[ch*MaximumBinsLong];   move16();
                                                                                                    move16();
    self->pAacDecoderChannelInfo[ch]->pJointStereoData = &pAacDecoderDynamicCommonDataInit->JointStereoData;
                                                                                                    move16();
    self->pAacDecoderChannelInfo[ch]->pPnsInterChannelData        = &pAacDecoderDynamicCommonDataInit->PnsInterChannelData;
    self->pAacDecoderChannelInfo[ch]->pPnsStaticInterChannelData  = &PnsStaticInterChannelData;     move16();
  }


  self->pStreamInfo->Channels = 0;                                                                  move16();

  for (ch=0; ch < Channels; ch++) {
    CPns_InitPns(self->pAacDecoderChannelInfo[ch]);
  }

  CPns_InitInterChannelData(self->pAacDecoderChannelInfo[0]);

  ByteAlign(bs,&self->byteAlignBits);
  

  /* patch to allow correct determination which (sbr-) fill element belongs to
     which sce or cpe. certainly requires some additional 'fine tuning'... */
  previous_element = ID_END;                                                                        move16();

  self->pStreamSbr->nrElements = 0;                                                                 move16();

  while ( (type != ID_END) && self->frameOK )
  {
                                                                                                    test(); logic16();
    type = (Word8)ReadBits(bs,3);

                                                                                                    test();
    if (bs->cntBits < 0) {
      self->frameOK = 0;                                                                            move16();
    }

    switch (type)
    {
      case ID_SCE:
                                                                                                    test(); test();
      
        if (self->frameOK) {
          if (self->pStreamInfo->Channels > 1) {
              ErrorStatus = AAC_DEC_TOO_MANY_CHANNELS;
              break;
          }

                                                                                                    test();
          if ((ErrorStatus = CSingleChannelElement_Read(bs,
                                                        self->pAacDecoderChannelInfo,
                                                        self->pStreamInfo,
                                                        &element_instance_tag)) ) {
            self->frameOK = 0;  /* trigger concealment */                                           move16();
            self->pStreamInfo->Channels = add(self->pStreamInfo->Channels, 1);                      move16();
            break;
          }
          else {
            CSingleChannelElement_Decode(self->pAacDecoderChannelInfo);
            self->pStreamInfo->Channels = add(self->pStreamInfo->Channels, 1);                      move16();
          }
        }

        break;
      
      case ID_CPE:
                                                                                                    test(); test();
       
        if (self->frameOK) {
          if (self->pStreamInfo->Channels > 0) {
              ErrorStatus = AAC_DEC_TOO_MANY_CHANNELS;
              break;
          }
                                                                                                    test();
          if ((ErrorStatus = CChannelPairElement_Read(bs,
                                                      self->pAacDecoderChannelInfo,
                                                      self->pStreamInfo,
                                                      &element_instance_tag))) {
            self->frameOK = 0;  /* trigger concealment */                                           move16();
            self->pStreamInfo->Channels = add(self->pStreamInfo->Channels, 2);                      move16();
            break;
          }
          else {
            CChannelPairElement_Decode(self->pAacDecoderChannelInfo);
            self->pStreamInfo->Channels = add(self->pStreamInfo->Channels, 2);                      move16();
          }

        }
        break;
      
      case ID_CCE:
                                                                                                    test();
        ErrorStatus = AAC_DEC_UNIMPLEMENTED_CCE;                                                    move16();
        self->frameOK = 0;                                                                          move16();
        break;

      case ID_LFE:
                                                                                                    test();
        ErrorStatus = AAC_DEC_UNIMPLEMENTED_LFE;                                                    move16();
        self->frameOK = 0;                                                                          move16();
        break;
      
      case ID_DSE:
                                                                                                    test();
        CDataStreamElement_Read(bs,self->pDataStreamElement,&self->byteAlignBits);
        break;
      
      case ID_PCE:
                                                                                                    test();
        ErrorStatus = AAC_DEC_UNIMPLEMENTED_PCE;                                                    move16();
        self->frameOK = 0;                                                                          move16();
        break;
      
      case ID_FIL:
                                                                                                    test();
                                                                                                    test();
	if(aacPlusCheckForPayload(bs, self->pStreamSbr, previous_element))
    	  aacPlusGetPayload(bs, &self->pStreamSbr->sbrElement[self->pStreamSbr->nrElements-1]);
      break;
      
      case ID_END:
                                                                                                    test();
        break;
    }

    previous_element = type;                                                                        move16();
  }


  self->frameOK = self->frameOK && frameOK;                                                         logic16(); move16();

  /*
    Inverse transform
  */
  for (ch=0; ch<self->pStreamInfo->Channels; ch++) {

    /*

      call to concealment delay unit, windows seqeuence, window shape and spectrum will be modified
    */
    CConcealment_Apply(self->hConcealmentInfo,
                       self->pAacDecoderChannelInfo[ch]->pSpectralCoefficient,
                       self->pAacDecoderChannelInfo[ch]->pSpecScale,
                       &self->pAacDecoderChannelInfo[ch]->IcsInfo,
                       ch,
                       self->frameOK);

                                                                                                    test();
    if (IsLongBlock(&self->pAacDecoderChannelInfo[ch]->IcsInfo))
      CLongBlock_FrequencyToTime(self->pAacDecoderStaticChannelInfo[ch],
                                 self->pAacDecoderChannelInfo[ch],
                                 &pTimeData[ch*2048],
                                 1);
    else
      CShortBlock_FrequencyToTime(self->pAacDecoderStaticChannelInfo[ch],
                                  self->pAacDecoderChannelInfo[ch],
                                  &pTimeData[ch*2048],
                                  1);
  }

  DelaySbrBitstr(self->pStreamSbr);


  ByteAlign(bs,&self->byteAlignBits);

  *frameSize = self->pStreamInfo->SamplesPerFrame;                                                  move16();
  *sampleRate = self->pStreamInfo->SamplingRate;                                                    move32();
  *numChannels = self->pStreamInfo->Channels;                                                       move16();
                                                                                                    test();
  if (*numChannels == 1) { 
    *channelMode = 0;                                                                               move16();
  }
  else {
                                                                                                    test();
    if (*numChannels == 2) {
      *channelMode = 1;                                                                             move16();
    }
    else {
      *channelMode = 2;                                                                             move16();
    }
  }

                                                                                                    test();
  if (BlockNumber == 0) {
    BlockNumber = L_add(BlockNumber, 1);
    return 0;  /* Supress mute 'error' at the beginning */
  }
  else {
    BlockNumber = L_add(BlockNumber, 1);
    return ErrorStatus;
  }
}
