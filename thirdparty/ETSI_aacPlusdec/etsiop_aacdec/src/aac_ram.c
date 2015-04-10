/*
   memory layout
 */

#include "aac_ram.h"
#include "sbr_ram.h"


/*! Get size of object in Word32s, rounded to next higher number */
#define SIZEOF_INT(x) ((sizeof(x)+sizeof(Word32)-1) / sizeof(Word32))


/*!
  \name StaticAacData
*/

/*! The structure CAacDecoderStaticChannelInfo contains the static sideinfo which is needed
    for the decoding of one aac channel. <br>
    Dimension: #AacDecoderChannels                                                      */
CAacDecoderStaticChannelInfo AacDecoderStaticChannelInfo[Channels];

/*! The structure CStreamInfo contains the streaming information. */
CStreamInfo StreamInfo;


/*! Overlap buffer */
Word16 OverlapBuffer[Channels*OverlapBufferSize];

CPnsStaticInterChannelData PnsStaticInterChannelData;

CConcealmentInfo ConcealmentInfoInstance;


/*!
  \name DynamicAacData
*/

/*! aacPLUSDecoder Workbuffer */
Word32 WorkBufferCore[Channels*MaximumBinsLong];

#ifdef LP_SBR_ONLY
CAacDecoderChannelInfo AacDecoderChannelInfo[Channels];

CAacDecoderChannelInfo *pAacDecoderChannelInfoInit[Channels] =
{
  &AacDecoderChannelInfo[0],
  &AacDecoderChannelInfo[1]
};

CAacDecoderDynamicData AacDecoderDynamicData[Channels];

CAacDecoderDynamicCommonData AacDecoderDynamicCommonData;

CAacDecoderDynamicData *pAacDecoderDynamicDataInit[Channels] =
{
  &AacDecoderDynamicData[0],
  &AacDecoderDynamicData[1]  
};

CAacDecoderDynamicCommonData *pAacDecoderDynamicCommonDataInit = &AacDecoderDynamicCommonData;
#else
extern Word32 WorkBuffer1[Channels*MaximumBinsLong];

CAacDecoderChannelInfo *pAacDecoderChannelInfoInit[Channels] =
{
  (CAacDecoderChannelInfo *) &WorkBuffer1[0*SIZEOF_INT(CAacDecoderChannelInfo)],
  (CAacDecoderChannelInfo *) &WorkBuffer1[1*SIZEOF_INT(CAacDecoderChannelInfo)]
};

CAacDecoderDynamicData *pAacDecoderDynamicDataInit[Channels] =
{
  (CAacDecoderDynamicData *) &WorkBuffer1[2*SIZEOF_INT(CAacDecoderChannelInfo)],
  (CAacDecoderDynamicData *) &WorkBuffer1[2*SIZEOF_INT(CAacDecoderChannelInfo)+SIZEOF_INT(CAacDecoderDynamicData)]
};

CAacDecoderDynamicCommonData *pAacDecoderDynamicCommonDataInit =
  (CAacDecoderDynamicCommonData *) &WorkBuffer1[2*SIZEOF_INT(CAacDecoderChannelInfo)+2*SIZEOF_INT(CAacDecoderDynamicData)];
#endif


CDataStreamElement DataStreamElement;




